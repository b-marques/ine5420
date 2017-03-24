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

void Figura::rotacionaFiguraProprioCentro(
		double anguloGraus) {
	Coordenada centroFigura = Coordenada(0, 0);
	int nCoords;
	for (nCoords = 0; nCoords < coordenadas.tamanho(); nCoords++) {
		centroFigura = centroFigura + coordenadas.retornaDado(nCoords);
	}
	centroFigura = centroFigura / nCoords;
	rotaciona(centroFigura, anguloGraus);
	calculaCentro();
}

void Figura::rotaciona(Coordenada centroRotacao,
		double anguloGraus) {
	Coordenada coordRelativa, coord;
	double anguloRad = anguloGraus / 180 * M_PI;
	double cosAngulo = cos(anguloRad), senAngulo = sin(anguloRad);
	for (int i = 0; i < coordenadas.tamanho(); i++) {
		coord = coordenadas.retiraDoInicio();
		coordRelativa = coord - centroRotacao;
		coord = Coordenada(
				coordRelativa.getX() * cosAngulo
						- coordRelativa.getY() * senAngulo,
				coordRelativa.getX() * senAngulo
						+ coordRelativa.getY() * cosAngulo) + centroRotacao;
		coordenadas.adiciona(coord);
	}
	calculaCentro();
}

void Figura::translada(Coordenada desloc) {
	Coordenada coord;
	for (int i = 0; i < coordenadas.tamanho(); i++) {
		coord = coordenadas.retiraDoInicio();
		coord = coord + desloc;
		coordenadas.adiciona(coord);
	}
	calculaCentro();
}

void Figura::escalona(Coordenada escala) {
	Coordenada coord;
	for (int i = 0; i < coordenadas.tamanho(); i++) {
		coord = coordenadas.retiraDoInicio();
		coord = coord * escala;
		coordenadas.adiciona(coord);
	}
	calculaCentro();	
}

void Figura::transform(Coordenada eixo, double grau, double escalaX, double escalaY, Coordenada deslocamento){
	Coordenada coord;
	for (int i = 0; i < coordenadas.tamanho(); i++) {
		coord = coordenadas.retiraDoInicio();
		coord = Matriz::matrizTransformacao(coord, eixo, grau, escalaX, escalaY, deslocamento);
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

