/*
 * Figura.h
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#ifndef FIGURA_HPP_
#define FIGURA_HPP_
#include <string>

#include "Coordenada.hpp"
#include "ListaEnc.hpp"
#include "Matriz.hpp"

using namespace std;

class Figura {
protected:
	ListaEnc<Coordenada> coordenadas;
	ListaEnc<Coordenada> coordenadasTela;
	Coordenada centro, centroRelTela;
	string nome;
	void transform(Coordenada eixo, double grau, Coordenada escalonamento,
			Coordenada deslocamento);
	void transformTela(Coordenada eixo, double grau, Coordenada escalonamento,
			Coordenada deslocamento);
public:
	Figura(string nome, ListaEnc<Coordenada>& coord);
	ListaEnc<Coordenada>& getCoord();
	ListaEnc<Coordenada>& getCoordTela();
	string getNome();
	Coordenada calculaCentro(ListaEnc<Coordenada>& coords);
	void translada(Coordenada desloc, Coordenada zoomAcumumlado,
			double giroTelaAcumulado);
	void escalona(Coordenada escala);
	void rotacionaFiguraProprioCentro(double anguloGraus,
			Coordenada zoomAcumulado, double giroTelaAcumulado, Coordenada centroDesenho);
	void rotaciona(Coordenada centroRotacao, double anguloGraus,
			Coordenada zoomAcumulado, double giroTelaAcumulado, Coordenada centroDesenho);
	void daZoom(Coordenada zoom, Coordenada centroDesenho);
	void deslocaNaTela(Coordenada desloc);
	void rotacionaTela(Coordenada centroDesenho, double angulo);
	Coordenada getCentro();
	virtual ~Figura();
};

#endif /* FIGURA_HPP_ */
