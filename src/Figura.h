/*
 * Figura.h
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#ifndef FIGURA_H_
#define FIGURA_H_
#include "ListaEnc.hpp"
#include "Coordenada.h"
#include <string>
#include <vector>
using namespace std;

class Figura {
protected:
	ListaEnc<Coordenada> coordenadas;
	string nome;
public:
	Figura(string nome, ListaEnc<Coordenada> coord);
	ListaEnc<Coordenada> getCoord();
	void corrigeCoordNavegacao(double dx, double dy);
	virtual ~Figura();
};

#endif /* FIGURA_H_ */
