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

	if (coords->tamanho() > 1)
		linhasVert = "l ";
	else
		linhasVert = "p ";
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
	arq.open(nomeArquivo.c_str());
	if (arq.is_open()) {
		getline(arq, linhaInicial);
		while (!arq.eof()) {
			f = leObjeto(arq, linhaInicial);
			mundo->adicionaFigura(f);
			getline(arq, linhaInicial);
		}
		arq.close();
	}
}

Figura* DescritorObj::leObjeto(ifstream& arquivo, string& linhaInicial) {
	string linha, nome;
	ListaEnc<Coordenada> coords;
	Coordenada coord;
	linha = linhaInicial;
	linha.erase(0, 2);
	nome = linha;
	getline(arquivo, linha);
	while (!linha.compare(0, 1, "v")) {
		coord = leCoord(linha);
		coords.adiciona(coord);
		getline(arquivo, linha);
	}
	if (!linha.compare(0, 1, "l")) {
		if (coords.tamanho() > 2)
			return new Poligono(nome, coords);
		return new Reta(nome, coords);
	} else {
		return new Ponto(nome, coords);
	}
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

DescritorObj::~DescritorObj() {
	// TODO Auto-generated destructor stub
}

