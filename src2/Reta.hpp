/*
 * Reta.h
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#ifndef RETA_HPP_
#define RETA_HPP_
#include "Figura.hpp"
#include <list>

class Reta: public Figura {
public:

	Reta(string nome, ListaEnc<Coordenada>& coord);
	virtual ~Reta();
};

#endif /* RETA_HPP_ */