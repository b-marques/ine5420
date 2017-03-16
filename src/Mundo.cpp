/*
 * Mundo.cpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#include "Mundo.h"
#include "Reta.h"
#include "Ponto.h"
#include "Poligono.h"
Mundo::Mundo() {
	this->deslocamento = Coordenada(0, 0);
	figuras = new ListaEnc<Figura*>();
}

void Mundo::desloca(Coordenada somaDeslocador) {
	deslocamento = deslocamento + somaDeslocador;
}

Coordenada Mundo::getDeslocamento() {
	return deslocamento;
}

void Mundo::adicionaPonto(string nome, ListaEnc<Coordenada> coord) {
	Ponto* p = new Ponto(nome, coord);
	figuras->adiciona(p);
}

void Mundo::adicionaReta(string nome, ListaEnc<Coordenada> coord) {
	Reta* r = new Reta(nome, coord);
	figuras->adiciona(r);
}

void Mundo::adicionaPoligono(string nome, ListaEnc<Coordenada> coord) {
	Poligono* p = new Poligono(nome, coord);
	figuras->adiciona(p);
}

Mundo::~Mundo() {
	delete figuras;
}

ListaEnc<Figura*> Mundo::getFiguras() {
	return *figuras;
}

