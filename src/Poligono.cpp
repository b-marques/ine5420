/*
 * Poligono.cpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#include "Poligono.h"
#include "Coordenada.h"
Poligono::Poligono(string nome, ListaEnc<Coordenada> coord) :
		Figura(nome, coord) {
}

Poligono::~Poligono() {
	// TODO Auto-generated destructor stub
}

