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

ListaEnc<ListaEnc<Coordenada> *>* Poligono::getCoordTelaClip(double xEsq,
		double xDir, double yCima, double yBaixo, int tipoClip) {
	return nullptr;
}
