/*
 * Ponto.cpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#include "../src/Ponto.hpp"

Ponto::Ponto(string nome, ListaEnc<Coordenada>& coord) :
		Figura(nome, coord) {
}

Ponto::~Ponto() {
	// TODO Auto-generated destructor stub
}

