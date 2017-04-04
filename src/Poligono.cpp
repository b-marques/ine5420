/*
 * Poligono.cpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#include "../src/Poligono.hpp"

#include "../src/Coordenada.hpp"
Poligono::Poligono(string nome, ListaEnc<Coordenada>& coord) :
		Figura(nome, coord) {
}

Poligono::~Poligono() {
	// TODO Auto-generated destructor stub
}

