/*
 * Figura.cpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#include "Figura.hpp"
#include <limits>
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

void Figura::translada(Coordenada& desloc, Coordenada& zoomAcumumlado,
		double giroTelaAcumulado) {
	Coordenada aux;
	for (int i = 0; i < coordenadas.tamanho(); i++) {
		aux = coordenadas.retiraDoInicio();
		aux += desloc;
		coordenadas.adiciona(aux);
	}
	centro = calculaCentro(coordenadas);
	Coordenada deslocCorrigido = Matriz::matrizTransformacao(desloc,
			Coordenada(0, 0), giroTelaAcumulado, Coordenada(1, 1),
			Coordenada(0, 0));
	transformTela(centroRelTela, 0, Coordenada(1, 1),
			deslocCorrigido * zoomAcumumlado);
}

void Figura::escalona(Coordenada& escala) {
	Coordenada aux;
	for (int i = 0; i < coordenadas.tamanho(); i++){
		aux = coordenadas.retiraDoInicio();
		Matriz::escalona3d(aux, escala, centro);
		coordenadas.adiciona(aux);
	}
	transformTela(centroRelTela, 0, escala, Coordenada(0, 0));
}

void Figura::rotacionaFiguraProprioCentro(Coordenada& origemMundoTela, Coordenada& eixo1, double anguloGraus,
		Coordenada& zoomAcumulado, double giroTelaAcumulado,
		Coordenada& centroDesenho) {
	rotaciona(origemMundoTela, centro, eixo1, anguloGraus, zoomAcumulado, giroTelaAcumulado,
			centroDesenho);
}

void Figura::rotaciona(Coordenada& origemMundoTela, Coordenada& eixo0, Coordenada& eixo1, double anguloGraus,
		Coordenada& zoomAcumulado, double giroTelaAcumulado,
		Coordenada& centroDesenho) {
	Coordenada aux;
	double anguloRad, dZY, dZX, sinA, cosA, sinB, cosB, sinSig, cosSig;
	anguloRad = anguloGraus * M_PI / 180.0;
	dZY = sqrt(pow(eixo1.getY() - eixo0.getY(), 2) + pow(eixo1.getZ() - eixo0.getZ(), 2));
	dZX = sqrt(pow(eixo1.getX() - eixo0.getX(), 2) + pow(eixo1.getZ() - eixo0.getZ(), 2));
	if(dZY>0){
		sinA = (eixo1.getY() - eixo0.getY()) / dZY;
		cosA = (eixo1.getZ() - eixo0.getZ()) / dZY;
	} else {
		sinA = 0;
		cosA = 1;
	}
	if(dZX>0){
		sinB = (eixo1.getX() - eixo0.getX()) / dZX;
		cosB = (eixo1.getZ() - eixo0.getZ()) / dZX;
	} else {
		sinB = 0;
		cosB = 1;
	}
	sinSig = sin(anguloRad);
	cosSig = cos(anguloRad);

	for (int i = 0; i < coordenadas.tamanho(); i++) {
		aux = coordenadas.retiraDoInicio();
		Matriz::rotaciona3d(aux, eixo0, sinA, cosA, sinB, cosB, sinSig, cosSig);
		coordenadas.adiciona(aux);
	}
	centro = calculaCentro(coordenadas);
	coordenadasTela = coordenadas;
	recemAdicionada(origemMundoTela, zoomAcumulado, centroDesenho, giroTelaAcumulado);
}

void Figura::daZoom(Coordenada& zoom, Coordenada& centroDesenho) {
	Coordenada coord = Coordenada(0, 0);
	transformTela(centroDesenho, 0, zoom, coord);
}

void Figura::deslocaNaTela(Coordenada& desloc) {
	transformTela(Coordenada(0, 0), 0, Coordenada(1, 1), desloc);
}

void Figura::rotacionaTela(Coordenada& centroDesenho, double angulo) {
	transformTela(centroDesenho, angulo, Coordenada(1, 1, 1),
			Coordenada(0, 0, 0));
}

void Figura::transform(const Coordenada& eixo, double grau, const Coordenada& escalonamento,
		const Coordenada& deslocamento) {
	Coordenada coord;
	for (int i = 0; i < coordenadas.tamanho(); i++) {
		coord = coordenadas.retiraDoInicio();
		coord = Matriz::matrizTransformacao(coord, eixo, grau, escalonamento,
				deslocamento);
		coordenadas.adiciona(coord);
	}
	centro = calculaCentro(coordenadas);
}

void Figura::transformTela(const Coordenada& eixo, double grau, const Coordenada& escalonamento,
		const Coordenada& deslocamento) {
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

const ListaEnc<Coordenada>* Figura::getCoordTela(bool projOrtogonal, double focoProj, const Coordenada& centroDesenho) {
	if(projOrtogonal)
		return &coordenadasTela;
	else {
		Coordenada COP = centroDesenho, aux;
		ListaEnc<Coordenada>* coordsProj = new ListaEnc<Coordenada>();
		double zSobreFoco, xp, yp;
		for (int i = 0; i < coordenadasTela.tamanho(); i++) {
			aux = coordenadasTela.retornaDado(i);
			aux -= COP;
			zSobreFoco = (aux.getZ()) / focoProj;
			if(zSobreFoco != 0){
				xp = aux.getX() / zSobreFoco;
				yp = aux.getY() / zSobreFoco;
			} else {
				xp = aux.getX() > 0 ? numeric_limits<double>::max() : -numeric_limits<double>::max();
				yp = aux.getY() > 0 ? numeric_limits<double>::max() : -numeric_limits<double>::max();
			}
			aux.setX(xp);
			aux.setY(yp);
			aux.setZ(focoProj);
			aux += COP;
			coordsProj->adiciona(aux);
		}
		return coordsProj;
	}
}

Figura::~Figura() {
	// TODO Auto-generated destructor stub
}

TipoFigura Figura::getTipo() {
	return this->tipo;
}

void Figura::recemAdicionada(Coordenada origemMundoTela, Coordenada& zoom,
		Coordenada& centroDesenho, double giroTela) {
	origemMundoTela = Matriz::matrizTransformacao(origemMundoTela,
			centroDesenho, -giroTela, Coordenada(1, 1) / zoom,
			Coordenada(0, 0));
	deslocaNaTela (origemMundoTela);
	daZoom(zoom, centroDesenho);
	rotacionaTela(centroDesenho, giroTela);
}
