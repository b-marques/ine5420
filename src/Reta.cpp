/*
 * Reta.cpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#include "Reta.hpp"

Reta::Reta(string nomeReta, ListaEnc<Coordenada>& coordReta) :
		Figura(nomeReta, coordReta) {
}

ListaEnc<Coordenada>& Reta::getCoordTelaClip() {
	return coordenadasTela;
}

Reta::~Reta() {
	// TODO Auto-generated destructor stub
}

