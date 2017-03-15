/*
 * Mundo.cpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#include "Mundo.h"
#include "Reta.h"
Mundo::Mundo() {
	this->deslocamento = Coordenada(0, 0);
	figuras = new ListaEnc<Figura*>();
}

void Mundo::desloca(double dx, double dy) {
	deslocamento.setX(deslocamento.getX() + dx);
	deslocamento.setY(deslocamento.getY() + dy);
}

Mundo::~Mundo() {
	delete figuras;
}

ListaEnc<Figura*>* Mundo::getFiguras() {
	return figuras;
}

void Mundo::adicionaReta(string nome, double xi, double yi, double xf,
		double yf) {
	Reta *r = new Reta(nome, xi, yi, xf, yf);
	figuras->adiciona(r);
}
