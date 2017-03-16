/*
 * Ponto.h
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#ifndef PONTO_H_
#define PONTO_H_
#include "Figura.h"

class Ponto : public Figura{
public:
	Ponto(string nome, ListaEnc<Coordenada> coord);
	virtual ~Ponto();
};

#endif /* PONTO_H_ */
