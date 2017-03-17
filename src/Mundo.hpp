/*
 * Mundo.h
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#ifndef MUNDO_HPP_
#define MUNDO_HPP_
#include "Figura.hpp"
#include "tipoMoveEnum.hpp"
class Mundo {
private:
	ListaEnc<Figura*> *figuras;
	Coordenada deslocamento, zoom;
public:
	Mundo();
	void desloca(double passo, double larguraArea, double alturaArea, TipoMovimento sentido);
	ListaEnc<Figura*>* getFiguras();
	Coordenada getDeslocamento();
	Coordenada getZoom();
	void adicionaPonto(string nome, ListaEnc<Coordenada>& coord);
	void adicionaReta(string nome, ListaEnc<Coordenada>& coord);
	void adicionaPoligono(string nome, ListaEnc<Coordenada>& coord);
	void maisZoom(double passo);
	void menosZoom(double passo);
	virtual ~Mundo();
};

#endif /* MUNDO_HPP_ */
