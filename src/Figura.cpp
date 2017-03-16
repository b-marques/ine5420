/*
 * Figura.cpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#include "Figura.h"

Figura::Figura(string nome, ListaEnc<Coordenada> coord) {
	this->nome = nome;
	this->coordenadas = coord;
}

ListaEnc<Coordenada> Figura::getCoord() {
	return coordenadas;
}

/* Pensei numa solucao melhor do que mudar todas as coordenadas
 * de todas as figuras, entao esse metodo abaixo so da uma nocao
 * de resolucao. O ideal seria guardar o deslocamento do "MUNDO"
 * em relacao ao ponto inicial, para nao precisar mudar as coordenadas
 * de cada figura.
 */
void Figura::corrigeCoordNavegacao(double dx, double dy) {
	Coordenada coord;
	int size = coordenadas.tamanho();
	for (int pos = 0; pos < size; pos++) {
		coord = coordenadas.retiraDaPosicao(pos);
		coordenadas.adicionaNaPosicao(
				Coordenada(coord.getX() + dx, coord.getY() + dy), pos);
	}
}

Figura::~Figura() {
	// TODO Auto-generated destructor stub
}

