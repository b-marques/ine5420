/*
 * Ponto.cpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#include "Ponto.h"

Ponto::Ponto(string nome, double x, double y) : Figura(nome){
	this->coordenadas.adiciona(Coordenada(x, y));
}

Ponto::~Ponto() {
	// TODO Auto-generated destructor stub
}

