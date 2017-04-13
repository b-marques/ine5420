/*
 * ListaEspecialWindow.cpp
 *
 *  Created on: 12 de abr de 2017
 *      Author: johann
 */

#include "ListaEspecialWindow.hpp"

ListaEspecialWindow::ListaEspecialWindow(double xEsq, double xDir, double yCima,
		double yBaixo) :
		ListaEnc<Coordenada>() {
	infEsq = Coordenada(xEsq, yBaixo);
	supEsq = Coordenada(xEsq, yCima);
	supDir = Coordenada(xDir, yCima);
	infDir = Coordenada(xDir, yBaixo);
	this->adiciona(infEsq);
	this->adiciona(supEsq);
	this->adiciona(supDir);
	this->adiciona(infDir);
	this->adiciona(infEsq);
}

ListaEspecialWindow::~ListaEspecialWindow() {
	// TODO Auto-generated destructor stub
}

void ListaEspecialWindow::addCoordArtificial(Coordenada artf) {
	Elemento<Coordenada> *headAux = head;
	Coordenada info;
	int linhaCoord, pos, linhaWind = 0;
	if (listaVazia()) {
		adicionaNoInicio(artf);
	} else {
		linhaCoord = linhaCoordenadaArtificial(artf);
		for (pos = 0; linhaWind < linhaCoord; pos++) {
			info = headAux->getInfo();
			if(!info.artificial)
				linhaWind++;
			headAux = headAux->getProximo();
		}
		switch (linhaCoord) {
			case 1:
				addNaLinha1(artf, headAux, pos);
				break;
			case 2:
				addNaLinha2(artf, headAux, pos);
				break;
			case 3:
				addNaLinha3(artf, headAux, pos);
				break;
			default:
				addNaLinha4(artf, headAux, pos);
				break;
		}
	}
}

int ListaEspecialWindow::linhaCoordenadaArtificial(Coordenada coord) {
	if(infEsq.xIguais(coord))
		return 1;
	else if(supEsq.yIguais(coord))
		return 2;
	else if(supDir.xIguais(coord))
		return 3;
	else
		return 4;
}

void ListaEspecialWindow::addNaLinha1(Coordenada artf, Elemento<Coordenada>* headAux,
		int posInicial) {
	Coordenada info;
	for (; posInicial < size; posInicial++) {
		info = headAux->getInfo();
		if (((artf.yMenorQue(info)) || (artf.yIguais(info)))) {
			adicionaNaPosicao(artf, posInicial);
			break;
		}
		headAux = headAux->getProximo();
}
}

void ListaEspecialWindow::addNaLinha2(Coordenada artf,
		Elemento<Coordenada>* headAux, int posInicial) {
	Coordenada info;
	for (; posInicial < size; posInicial++) {
		info = headAux->getInfo();
		if ((artf.xMenorQue(info)) || artf.xIguais(info)) {
			adicionaNaPosicao(artf, posInicial);
			break;
		}
		headAux = headAux->getProximo();
}
}

void ListaEspecialWindow::addNaLinha3(Coordenada artf,
		Elemento<Coordenada>* headAux, int posInicial) {
	Coordenada info;
	for (; posInicial < size; posInicial++) {
		info = headAux->getInfo();
		if (artf.yMaiorQue(info)) {
			adicionaNaPosicao(artf, posInicial);
			break;
		}
		headAux = headAux->getProximo();
}
}

void ListaEspecialWindow::addNaLinha4(Coordenada artf,
		Elemento<Coordenada>* headAux, int posInicial) {
	Coordenada info;
	for (; posInicial < size; posInicial++) {
		info = headAux->getInfo();
		if (artf.xMaiorQue(info)) {
			adicionaNaPosicao(artf, posInicial);
			break;
		}
		headAux = headAux->getProximo();
}
}

void ListaEspecialWindow::retiraInfEsqDuplicado() {
	retira();
}
