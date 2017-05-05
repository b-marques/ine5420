/*
 * Figura3D.cpp
 *
 *  Created on: 4 de mai de 2017
 *      Author: johann
 */

#include "Figura3D.hpp"

Figura3D::Figura3D(string nome, ListaEnc<Poligono*>& superficies) : Figura(nome, FIGURA3D) {
	this->superficies = superficies;
}

void Figura3D::translada(Coordenada& desloc, Coordenada& zoomAcumumlado,
		double giroTelaAcumulado) {
	for (int i = 0; i < superficies.tamanho(); i++) {
		superficies.retornaDado(i)->translada(desloc, zoomAcumumlado, giroTelaAcumulado);
	}
}

void Figura3D::escalona(Coordenada& escala) {
	for (int i = 0; i < superficies.tamanho(); i++) {
		superficies.retornaDado(i)->escalona(escala);
	}
}

void Figura3D::rotacionaFiguraProprioCentro(Coordenada& origemMundoTela,
		Coordenada& eixo1, double anguloGraus, Coordenada& zoomAcumulado,
		double giroTelaAcumulado, Coordenada& centroDesenho) {
	Poligono *p;
	for (int i = 0; i < superficies.tamanho(); i++) {
		p = superficies.retornaDado(i);
		p->rotacionaFiguraProprioCentro(origemMundoTela, eixo1, anguloGraus, zoomAcumulado, giroTelaAcumulado, centroDesenho);
	}
}

void Figura3D::rotaciona(Coordenada& origemMundoTela, Coordenada& eixo0,
		Coordenada& eixo1, double anguloGraus, Coordenada& zoomAcumulado,
		double giroTelaAcumulado, Coordenada& centroDesenho) {
	Poligono *p;
	for (int i = 0; i < superficies.tamanho(); i++) {
		p = superficies.retornaDado(i);
		p->rotaciona(origemMundoTela, eixo0, eixo1, anguloGraus, zoomAcumulado, giroTelaAcumulado, centroDesenho);
	}
}

void Figura3D::daZoom(Coordenada& zoom, Coordenada& centroDesenho) {
	for (int i = 0; i < superficies.tamanho(); i++) {
		superficies.retornaDado(i)->daZoom(zoom, centroDesenho);
	}
}

void Figura3D::deslocaNaTela(Coordenada& desloc) {
	for (int i = 0; i < superficies.tamanho(); i++) {
		superficies.retornaDado(i)->deslocaNaTela(desloc);
	}
}

void Figura3D::rotacionaTela(Coordenada& centroDesenho, double angulo) {
	for (int i = 0; i < superficies.tamanho(); i++) {
		superficies.retornaDado(i)->rotacionaTela(centroDesenho, angulo);
	}
}

ListaEnc<ListaEnc<Coordenada> *>* Figura3D::getCoordTelaClip(double xEsq,
		double xDir, double yCima, double yBaixo, int tipoClip) {
	ListaEnc<ListaEnc<Coordenada> *>* poligonosClipados = new ListaEnc<ListaEnc<Coordenada> *>();
	ListaEnc<ListaEnc<Coordenada> *>* superficieClip;
	Poligono *p;
	for (int i = 0; i < superficies.tamanho(); i++) {
		p = superficies.retornaDado(i);
		superficieClip = p->getCoordTelaClip(xEsq, xDir, yCima, yBaixo, tipoClip);
		if(superficieClip != nullptr)
			for (int j = 0; j < superficieClip->tamanho(); j++) {
				poligonosClipados->adiciona(superficieClip->retiraDoInicio());
			}
		delete superficieClip;
	}
	if(poligonosClipados->tamanho() > 0){
		return poligonosClipados;
	}
	delete poligonosClipados;
	return nullptr;
}

ListaEnc<Coordenada>& Figura3D::getSuperficie(int idSuper) {
	return superficies.retornaDado(idSuper)->getCoordTela();
}

int Figura3D::numSuperficies() {
	return superficies.tamanho();
}

Figura3D::~Figura3D() {
	for (int i = 0; i < superficies.tamanho(); i++) {
		delete superficies.retiraDoInicio();
	}
}

