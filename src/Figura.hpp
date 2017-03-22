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
	void escalona(Coordenada escala);
	void translada(Coordenada desloc);
	void rotacionaFiguraProprioCentro(double anguloGraus);
	void rotaciona(Coordenada centroRotacao, double anguloGraus);
	virtual ~Figura();
};

#endif /* FIGURA_HPP_ */
