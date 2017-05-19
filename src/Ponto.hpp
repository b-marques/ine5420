/*
 * Ponto.h
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#ifndef PONTO_HPP_
#define PONTO_HPP_
#include "Figura.hpp"

class Ponto: public Figura {
public:
	Ponto(string nome, ListaEnc<Coordenada>& coord);
	ListaEnc<ListaEnc<Coordenada>*>* getCoordTelaClip(double xEsq,
			double xDir, double yCima, double yBaixo, int tipoClip, bool projOrtogonal,
			double focoProj, const Coordenada& centroDesenho);
	virtual ~Ponto();
};

#endif /* PONTO_HPP_ */
