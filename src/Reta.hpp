/*
 * Reta.h
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#ifndef RETA_HPP_
#define RETA_HPP_
#include "Figura.hpp"

class Reta: public Figura {
private:
	ListaEnc<ListaEnc<Coordenada>*>* clipCs(double xEsq, double xDir,
			double yCima, double yBaixo, const ListaEnc<Coordenada>* coordsTelaProj);
	ListaEnc<ListaEnc<Coordenada>*>* clipLb(double xEsq, double xDir,
			double yCima, double yBaixo, const ListaEnc<Coordenada>* coordsTelaProj);
	int getCode(Coordenada& coord, double xEsq, double xDir, double yCima,
			double yBaixo);
public:
	Reta(string nome, ListaEnc<Coordenada>& coord);
	ListaEnc<ListaEnc<Coordenada>*>* getCoordTelaClip(double xEsq,
			double xDir, double yCima, double yBaixo, int tipoClip, bool projOrtogonal,
			double focoProj, const Coordenada& centroDesenho);
	virtual ~Reta();
};

#endif /* RETA_HPP_ */
