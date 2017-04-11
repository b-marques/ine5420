/*
 * Poligono.h
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#ifndef POLIGONO_HPP_
#define POLIGONO_HPP_
#include <vector>

#include "Figura.hpp"
class Poligono: public Figura {
public:
	Poligono(string nome, ListaEnc<Coordenada>& coord);
	ListaEnc<ListaEnc<Coordenada>*>* getCoordTelaClip(double xEsq, double xDir,
			double yCima, double yBaixo, int tipoClip);
	virtual ~Poligono();
};

#endif /* POLIGONO_HPP_ */
