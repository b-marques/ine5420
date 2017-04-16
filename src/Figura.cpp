/*
 * Figura.cpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#include "Figura.hpp"

#include <math.h>
Figura::Figura(string nome, TipoFigura tipo) {
	this->nome = nome;
	this->tipo = tipo;
}

Figura::Figura(string nome, ListaEnc<Coordenada>& coord, TipoFigura tipo) {
	this->nome = nome;
	this->coordenadas = coord;
	this->coordenadasTela = coord;
	this->tipo = tipo;
	centro = calculaCentro(coordenadas);
	centroRelTela = centro;
}

ListaEnc<Coordenada>& Figura::getCoord() {
	return coordenadas;
}

string Figura::getNome() {
	return nome;
}

Coordenada Figura::calculaCentro(ListaEnc<Coordenada>& coords) {
	Coordenada centroFigura = Coordenada(0, 0);
	int nCoords;
	for (nCoords = 0; nCoords < coords.tamanho(); nCoords++) {
		centroFigura = centroFigura + coords.retornaDado(nCoords);
	}
	return centroFigura / nCoords;
}

void Figura::translada(Coordenada desloc, Coordenada zoomAcumumlado,
		double giroTelaAcumulado) {
	transform(centro, 0, Coordenada(1, 1), desloc);
	Coordenada deslocCorrigido = Matriz::matrizTransformacao(desloc,
			Coordenada(0, 0), giroTelaAcumulado, Coordenada(1, 1),
			Coordenada(0, 0));
	transformTela(centroRelTela, 0, Coordenada(1, 1),
			deslocCorrigido * zoomAcumumlado);
}

void Figura::escalona(Coordenada escala) {
	transform(centro, 0, escala, Coordenada(0, 0));
	transformTela(centroRelTela, 0, escala, Coordenada(0, 0));
}

void Figura::rotacionaFiguraProprioCentro(double anguloGraus,
		Coordenada zoomAcumulado, double giroTelaAcumulado,
		Coordenada centroDesenho) {
	rotaciona(centro, anguloGraus, zoomAcumulado, giroTelaAcumulado,
			centroDesenho);
}

void Figura::rotaciona(Coordenada centroRotacao, double anguloGraus,
		Coordenada zoomAcumulado, double giroTelaAcumulado,
		Coordenada centroDesenho) {
	Coordenada centroFigGirado = Matriz::matrizTransformacao(centro,
			centroDesenho, giroTelaAcumulado, zoomAcumulado, Coordenada(0, 0));
	Coordenada centroRotacaoTela = Matriz::matrizTransformacao(centroRotacao,
			centroDesenho, giroTelaAcumulado, zoomAcumulado, centroRelTela - centroFigGirado);
	transform(centroRotacao, anguloGraus, Coordenada(1, 1), Coordenada(0, 0));
	transformTela(centroRotacaoTela, anguloGraus, Coordenada(1, 1),
			Coordenada(0, 0));
}

void Figura::daZoom(Coordenada zoom, Coordenada centroDesenho) {
	Coordenada coord = Coordenada(0, 0);
	transformTela(centroDesenho, 0, zoom, coord);
}

void Figura::deslocaNaTela(Coordenada desloc) {
	transformTela(Coordenada(0, 0), 0, Coordenada(1, 1), desloc);
}

void Figura::rotacionaTela(Coordenada centroDesenho, double angulo) {
	transformTela(centroDesenho, angulo, Coordenada(1, 1, 1),
			Coordenada(0, 0, 0));
}

void Figura::transform(Coordenada eixo, double grau, Coordenada escalonamento,
		Coordenada deslocamento) {
	Coordenada coord;
	for (int i = 0; i < coordenadas.tamanho(); i++) {
		coord = coordenadas.retiraDoInicio();
		coord = Matriz::matrizTransformacao(coord, eixo, grau, escalonamento,
				deslocamento);
		coordenadas.adiciona(coord);
	}
	centro = calculaCentro(coordenadas);
}

void Figura::transformTela(Coordenada eixo, double grau,
		Coordenada escalonamento, Coordenada deslocamento) {
	Coordenada coord;
	for (int i = 0; i < coordenadasTela.tamanho(); i++) {
		coord = coordenadasTela.retiraDoInicio();
		coord = Matriz::matrizTransformacao(coord, eixo, grau, escalonamento,
				deslocamento);
		coordenadasTela.adiciona(coord);
	}
	centroRelTela = calculaCentro(coordenadasTela);
}

Coordenada Figura::getCentro() {
	return this->centro;
}

ListaEnc<Coordenada>& Figura::getCoordTela() {
	return coordenadasTela;
}

Figura::~Figura() {
	// TODO Auto-generated destructor stub
}

TipoFigura Figura::getTipo() {
	return this->getTipo();
}
