/*
 * Mundo.h
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#ifndef MUNDO_HPP_
#define MUNDO_HPP_
#include "../src/Coordenada.hpp"
#include "../src/Figura.hpp"
#include "../src/tipoMoveEnum.hpp"

class Mundo {
private:
	ListaEnc<Figura*> *figuras;
	Coordenada deslocamento, zoom, centroDesenho, centroMundo, zoomAcumulado;
	double larguraArea, alturaArea, giroTelaAcumulado;
public:
	Mundo(double larguraArea, double alturaArea);
	void desloca(double passo, TipoMovimento sentido);
	ListaEnc<Figura*>* getFiguras();
	Coordenada getDeslocamento();
	Coordenada getZoom();
	Coordenada getCentroDesenho();
	Coordenada getCentroMundo();
	void adicionaFigura(Figura *f);
	void adicionaPonto(string nome, ListaEnc<Coordenada>& coord);
	void adicionaReta(string nome, ListaEnc<Coordenada>& coord);
	void adicionaPoligono(string nome, ListaEnc<Coordenada>& coord);
	void transladaFigura(int posicaoLista, Coordenada desloc);
	void escalonaFigura(int posicaoLista, Coordenada escala);
	void rotacionaFiguraCentroMundo(int posicaoLista, double anguloGraus);
	void rotacionaFiguraProprioCentro(int posicaoLista, double anguloGraus);
	void rotacionaFigura(int posicaoLista, Coordenada centroRotacao, double anguloGraus);
	void maisZoom(double passo);
	void menosZoom(double passo);
	void daZoomFiguras();
	void deslocaFiguras();
	void giraTela(double angulo);
	virtual ~Mundo();
};

#endif /* MUNDO_HPP_ */
