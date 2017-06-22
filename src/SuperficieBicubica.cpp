/*
 * Superficie.cpp
 *
 *  Created on: 17 de jun de 2017
 *      Author: johann
 */

#include "SuperficieBicubica.hpp"

SuperficieBicubica::SuperficieBicubica(string nome, TipoFigura tipo) : Figura(nome, tipo){

}

SuperficieBicubica::~SuperficieBicubica() {
	for (int i = 0; i < curvas.tamanho(); i++) {
		delete curvas.retiraDoInicio();
	}
}

void SuperficieBicubica::translada(Coordenada& desloc,
		Coordenada& zoomAcumumlado, double giroTelaAcumulado) {
	for (int i = 0; i < curvas.tamanho(); i++) {
		curvas.retornaDado(i)->translada(desloc, zoomAcumumlado, giroTelaAcumulado);
	}
}

void SuperficieBicubica::escalona(Coordenada& escala) {
	for (int i = 0; i < curvas.tamanho(); i++) {
		curvas.retornaDado(i)->escalona(escala);
	}
}

void SuperficieBicubica::rotacionaFiguraProprioCentro(
		Coordenada& origemMundoTela, Coordenada& eixo1, double anguloGraus,
		Coordenada& zoomAcumulado, double giroTelaAcumulado,
		Coordenada& centroDesenho) {
	Curva *p;
	for (int i = 0; i < curvas.tamanho(); i++) {
		p = curvas.retornaDado(i);
		p->rotacionaFiguraProprioCentro(origemMundoTela, eixo1, anguloGraus, zoomAcumulado, giroTelaAcumulado, centroDesenho);
	}
}

void SuperficieBicubica::rotaciona(Coordenada& origemMundoTela,
		Coordenada& eixo0, Coordenada& eixo1, double anguloGraus,
		Coordenada& zoomAcumulado, double giroTelaAcumulado,
		Coordenada& centroDesenho) {
	Curva *p;
	for (int i = 0; i < curvas.tamanho(); i++) {
		p = curvas.retornaDado(i);
		p->rotaciona(origemMundoTela, eixo0, eixo1, anguloGraus, zoomAcumulado, giroTelaAcumulado, centroDesenho);
	}
}

void SuperficieBicubica::daZoom(Coordenada& zoom, Coordenada& centroDesenho) {
	for (int i = 0; i < curvas.tamanho(); i++) {
		curvas.retornaDado(i)->daZoom(zoom, centroDesenho);
	}
}

void SuperficieBicubica::deslocaNaTela(Coordenada& desloc) {
	for (int i = 0; i < curvas.tamanho(); i++) {
		curvas.retornaDado(i)->deslocaNaTela(desloc);
	}
}

void SuperficieBicubica::rotacionaTela(Coordenada& centroDesenho,
		double angulo) {
	for (int i = 0; i < curvas.tamanho(); i++) {
		curvas.retornaDado(i)->rotacionaTela(centroDesenho, angulo);
	}
}

ListaEnc<Coordenada>& SuperficieBicubica::getCurva(int idCurva) {
	return curvas.retornaDado(idCurva)->getCoord();
}

const ListaEnc<Coordenada>* SuperficieBicubica::getCurvaTela(int idSuper,
		bool projOrtogonal, double focoProj, const Coordenada& centroDesenho) {
	return curvas.retornaDado(idSuper)->getCoordTela(projOrtogonal, focoProj,centroDesenho);
}

int SuperficieBicubica::numCurvas() {
	return curvas.tamanho();
}

void SuperficieBicubica::recemAdicionada(Coordenada origemMundoTela,
		Coordenada& zoom, Coordenada& centroDesenho, double giroTela) {
	for (int i = 0; i < curvas.tamanho(); i++) {
		curvas.retornaDado(i)->recemAdicionada(origemMundoTela, zoom, centroDesenho, giroTela);
	}
}

ListaEnc<ListaEnc<Coordenada> *>* SuperficieBicubica::getCoordTelaClip(double xEsq,
		double xDir, double yCima, double yBaixo, int tipoClip,
		bool projOrtogonal, double focoProj, const Coordenada& centroDesenho) {
	ListaEnc<ListaEnc<Coordenada> *>* curvasClipadas = new ListaEnc<ListaEnc<Coordenada> *>();
	ListaEnc<ListaEnc<Coordenada> *>* curvaClip;
	Curva *p;
	for (int i = 0; i < curvas.tamanho(); i++) {
		p = curvas.retornaDado(i);
		curvaClip = p->getCoordTelaClip(xEsq, xDir, yCima, yBaixo, tipoClip, projOrtogonal, focoProj, centroDesenho);
		if(curvaClip != nullptr)
			for (int j = 0; j < curvaClip->tamanho(); j++) {
				curvasClipadas->adiciona(curvaClip->retiraDoInicio());
			}
		delete curvaClip;
	}
	if(curvasClipadas->tamanho() > 0){
		return curvasClipadas;
	}
	delete curvasClipadas;
	return nullptr;
}
