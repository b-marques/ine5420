/*
 * DescritorObj.cpp
 *
 *  Created on: 28 de mar de 2017
 *      Author: johann
 */

#include "DescritorObj.hpp"

#include <fstream>
#include "Poligono.hpp"
#include "Ponto.hpp"
#include "Reta.hpp"
#include "Bezier.hpp"
#include <algorithm>
DescritorObj::DescritorObj() {
	// TODO Auto-generated constructor stub

}

DescritorObj::DescritorObj(Mundo* mundo) {
	this->mundo = mundo;
}

void DescritorObj::salvaMundo(string nomeArquivo) {
	ofstream arq;
	string textoArq;
	int linha = 1;
	arq.open(nomeArquivo.c_str());
	ListaEnc<Figura*>* figs = mundo->getFiguras();
	Figura *f;
	if (arq.is_open()) {
		for (int i = 0; i < figs->tamanho(); i++) {
			f = figs->retornaDado(i);
			escreveFigura(textoArq, f, linha);
		}
		textoArq.erase(textoArq.size() - 1);
		arq << textoArq;
		arq.close();
	}
}

void DescritorObj::escreveFigura(string& texto, Figura* figura, int& linha) {
	texto += "o " + figura->getNome() + "\n";
	linha++;
	string linhasVert;
	ListaEnc<Coordenada>* coords = &figura->getCoord();
	Coordenada coord;

	if (figura->getTipo() == RETA || figura->getTipo() == POLIGONO)
		linhasVert = "l ";
	else if (figura->getTipo() == PONTO)
		linhasVert = "p ";
	else
		linhasVert = "curv";
	for (int i = 0; i < coords->tamanho(); ++i) {
		coord = coords->retornaDado(i);
		texto += "v " + to_string(coord.getX()) + " " + to_string(coord.getY())
				+ " " + to_string(coord.getZ()) + "\n";
		linhasVert += to_string(linha);
		linha++;
	}
	texto += linhasVert + "\n";
	linha++;
}

void DescritorObj::leMundo(string nomeArquivo) {
	ifstream arq;
	string linhaInicial;
	Figura* f;
	map<int, Coordenada>* coords;
	arq.open(nomeArquivo.c_str());
	if (arq.is_open()) {
		coords = leTodasCoords(arq);
		arq.clear();
		arq.seekg(0, ios::beg);
		getline(arq, linhaInicial);
		while (!arq.eof()) {
			f = leObjeto(arq, linhaInicial, coords);
			mundo->adicionaFigura(f);
			getline(arq, linhaInicial);
		}
		arq.close();
		delete coords;
	}
}

Figura* DescritorObj::leObjeto(ifstream& arquivo, string& linhaInicial,
		map<int, Coordenada> *coords) {
	string linha, nome;
	Figura *f = nullptr;
	ListaEnc<Coordenada> *listaCoords;
	Coordenada coord;
	linha = linhaInicial;
	if (!linha.compare(0, 1, "o")) {
		linha.erase(0, 2);
		nome = linha;
	}
	while (f == nullptr && getline(arquivo, linha)) {
		if (!linha.compare(0, 1, "l")) {
			listaCoords = listaCoordsFigura(linha, coords);
			if (listaCoords->tamanho() > 2)
				f = new Poligono(nome, *listaCoords);
			else
				f = new Reta(nome, *listaCoords);
		} else if (!linha.compare(0, 1, "p")) {
			listaCoords = listaCoordsFigura(linha, coords);
			f = new Ponto(nome, *listaCoords);
		} else if (!linha.compare(0, 4, "curv")) {
			listaCoords = listaCoordsFigura(linha, coords);
			f = new Bezier(nome, *listaCoords);
		}
	}
	delete listaCoords;
	return f;
}

map<int, Coordenada>* DescritorObj::leTodasCoords(ifstream& arquivo) {
	string linha;
	int linhaArq = 1;
	map<int, Coordenada> *coords = new map<int, Coordenada>();
	while (getline(arquivo, linha)) {
		if (!linha.compare(0, 1, "v")) {
			coords->insert(pair<int, Coordenada>(linhaArq, leCoord(linha)));
		}
		linhaArq++;
	}
	return coords;
}

Coordenada DescritorObj::leCoord(string& linha) {
	double x, y, z;
	linha.erase(0, 2);
	int size = linha.find(" ");
	x = atof(linha.substr(0, size).c_str());
	y = atof(linha.substr(size + 1, 2 * size).c_str());
	z = atof(linha.substr(2 * size + 1, 3 * size).c_str());
	return Coordenada(x, y, z);
}

ListaEnc<Coordenada>* DescritorObj::listaCoordsFigura(string linha,
		map<int, Coordenada>* coords) {
	int posEspaco;
	string nLinha;
	ListaEnc<Coordenada> *listaCoord = new ListaEnc<Coordenada>();
	linha.erase(0, linha.find(" "));
	linha.insert(linha.size(), " ");
	while (linha.size() > 1) {
		posEspaco = linha.find(" ");
		linha.erase(0, 1);
		nLinha = linha.substr(posEspaco, linha.find(" "));
		linha.erase(0, nLinha.size());
		listaCoord->adiciona(coords->at(atoi(nLinha.c_str())));
	}
	return listaCoord;
}

DescritorObj::~DescritorObj() {
	// TODO Auto-generated destructor stub
}

