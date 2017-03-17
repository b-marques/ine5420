/*
 * Figura.cpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#include "Figura.hpp"

Figura::Figura(string nome, ListaEnc<Coordenada>& coord) {
	this->nome = nome;
	this->coordenadas = coord;

}

ListaEnc<Coordenada>& Figura::getCoord() {
	return coordenadas;
}


Figura::~Figura() {
	// TODO Auto-generated destructor stub
}

