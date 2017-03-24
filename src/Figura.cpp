/*
 * Figura.cpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#include "Figura.hpp"
#include <math.h>
Figura::Figura(string nome, ListaEnc<Coordenada>& coord) {
	this->nome = nome;
	this->coordenadas = coord;
	calculaCentro();
}

ListaEnc<Coordenada>& Figura::getCoord() {
	return coordenadas;
}

string Figura::getNome() {
	return nome;
}

void Figura::calculaCentro() {
	Coordenada centroFigura = Coordenada(0, 0);
	int nCoords;
	for (nCoords = 0; nCoords < coordenadas.tamanho(); nCoords++) {
		centroFigura = centroFigura + coordenadas.retornaDado(nCoords);
	}
	this->centro = centroFigura / nCoords;
}

void Figura::translada(Coordenada desloc) {
	transform(centro, 0, Coordenada(1, 1), desloc);
}

void Figura::escalona(Coordenada escala) {
	transform(centro, 0, escala, Coordenada(0, 0));
}

void Figura::rotacionaFiguraProprioCentro(double anguloGraus) {
	rotaciona(centro, anguloGraus);
}

void Figura::rotaciona(Coordenada centroRotacao, double anguloGraus) {
		transform(centroRotacao, anguloGraus, Coordenada(1, 1), Coordenada(0, 0));
}

void Figura::transform(Coordenada eixo, double grau, Coordenada escalonamento, Coordenada deslocamento){
	Coordenada coord;
	for (int i = 0; i < coordenadas.tamanho(); i++) {
		coord = coordenadas.retiraDoInicio();
		coord = Matriz::matrizTransformacao(coord, eixo, grau, escalonamento, deslocamento);
		coordenadas.adiciona(coord);
	}
	calculaCentro();
}

Coordenada Figura::getCentro() {
	return this->centro;
}


Figura::~Figura() {
	// TODO Auto-generated destructor stub
}

