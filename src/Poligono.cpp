/*
 * Poligono.cpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#include "Poligono.h"
#include "Coordenada.h"
Poligono::Poligono(string nome, double* x, double* y, int bufSize) : Figura(nome){
	for (int i = 0; i < bufSize; i++) {
		this->coordenadas.adiciona(Coordenada(x[i], y[i]));
	}
}

Poligono::~Poligono() {
	// TODO Auto-generated destructor stub
}

