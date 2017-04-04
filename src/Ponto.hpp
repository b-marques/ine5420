/*
 * Ponto.h
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#ifndef PONTO_HPP_
#define PONTO_HPP_
#include "../src/Figura.hpp"

class Ponto : public Figura{
public:
	Ponto(string nome, ListaEnc<Coordenada>& coord);
	virtual ~Ponto();
};

#endif /* PONTO_HPP_ */
