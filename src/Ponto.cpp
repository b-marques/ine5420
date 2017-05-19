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
		double xDir, double yCima, double yBaixo, int tipoClip, bool projOrtogonal,
		double focoProj, const Coordenada& centroDesenho) {
	ListaEnc<ListaEnc<Coordenada>*>* lista;
	ListaEnc<Coordenada> *listaCoords;
	const ListaEnc<Coordenada> *coordsTela;
	coordsTela = getCoordTela(projOrtogonal, focoProj, centroDesenho);
	Coordenada p1 = coordsTela->retornaDado(0);
	lista = new ListaEnc<ListaEnc<Coordenada>*>();
	listaCoords = new ListaEnc<Coordenada>();
	listaCoords->adiciona(p1);
	lista->adiciona(listaCoords);
	if(!projOrtogonal)
		delete coordsTela;
	return lista;
}
