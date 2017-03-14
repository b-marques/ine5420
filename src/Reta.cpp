/*
 * Reta.cpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#include "Reta.h"

Reta::Reta(string nome, double xi, double yi, double xf, double yf) :
		Figura(nome) {
	this->coordenadas.adiciona(Coordenada(xi, yi));
	this->coordenadas.adiciona(Coordenada(xf, yf));
}

Reta::~Reta() {
	// TODO Auto-generated destructor stub
}

