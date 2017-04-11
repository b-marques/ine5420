/*
 * Poligono.cpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#include "Poligono.hpp"

#include "Coordenada.hpp"
Poligono::Poligono(string nome, ListaEnc<Coordenada>& coord) :
		Figura(nome, coord) {
}

Poligono::~Poligono() {
	// TODO Auto-generated destructor stub
}

ListaEnc<Coordenada>& Poligono::getCoordTelaClip() {
	return coordenadasTela;
}
