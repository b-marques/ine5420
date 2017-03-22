/*
 * Figura.h
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#ifndef FIGURA_HPP_
#define FIGURA_HPP_
#include "ListaEnc.hpp"
#include <string>
#include "Coordenada.hpp"

using namespace std;

class Figura {
protected:
	ListaEnc<Coordenada> coordenadas;
	string nome;
public:
	Figura(string nome, ListaEnc<Coordenada>& coord);
	ListaEnc<Coordenada>& getCoord();
	string getNome();
	virtual ~Figura();
};

#endif /* FIGURA_HPP_ */
