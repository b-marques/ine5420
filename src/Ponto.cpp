/*
 * Ponto.cpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#include "Ponto.hpp"

Ponto::Ponto(string nome, ListaEnc<Coordenada>& coord) :
		Figura(nome, coord, PONTO) {
}

Ponto::~Ponto() {
	// TODO Auto-generated destructor stub
}

ListaEnc<ListaEnc<Coordenada> *>* Ponto::getCoordTelaClip(double xEsq,
		double xDir, double yCima, double yBaixo, int tipoClip) {
	ListaEnc<ListaEnc<Coordenada>*>* lista;
	ListaEnc<Coordenada> *listaCoords;
	Coordenada p1 = coordenadasTela.retornaDado(0);
	lista = new ListaEnc<ListaEnc<Coordenada>*>();
	listaCoords = new ListaEnc<Coordenada>();
	listaCoords->adiciona(p1);
	lista->adiciona(listaCoords);
	return lista;
}
