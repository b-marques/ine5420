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
#include "Matriz.hpp"

using namespace std;

class Figura {
protected:
	ListaEnc<Coordenada> coordenadas;
	Coordenada centro;
	string nome;
	void transform(Coordenada eixo, double grau, Coordenada escalonamento, Coordenada deslocamento);
public:
	Figura(string nome, ListaEnc<Coordenada>& coord);
	ListaEnc<Coordenada>& getCoord();
	string getNome();
	void calculaCentro();
	void translada(Coordenada desloc);
	void escalona(Coordenada escala);
	void rotacionaFiguraProprioCentro(double anguloGraus);
	void rotaciona(Coordenada centroRotacao, double anguloGraus);
	Coordenada getCentro();
	virtual ~Figura();
};

#endif /* FIGURA_HPP_ */
