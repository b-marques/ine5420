/*
 * Mundo.h
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#ifndef MUNDO_HPP_
#define MUNDO_HPP_
#include "Coordenada.hpp"
#include "Figura.hpp"
#include "tipoMoveEnum.hpp"

class Mundo {
private:
	ListaEnc<Figura*> *figuras;
	Coordenada deslocamento, zoom, centroDesenho, centroMundo, zoomAcumulado, origemMundoTela;
	double larguraArea, alturaArea, giroTelaAcumulado;
	void inicializaFigura(Figura *f);
public:
	Mundo(double larguraArea, double alturaArea);
	void desloca(double passo, TipoMovimento sentido);
	ListaEnc<Figura*>* getFiguras();
	Coordenada getDeslocamento();
	Coordenada getZoom();
	Coordenada getCentroDesenho();
	Coordenada getCentroMundo();
	void adicionaFigura(Figura *f);
	Figura* adicionaPonto(string nome, ListaEnc<Coordenada>& coord);
	Figura* adicionaReta(string nome, ListaEnc<Coordenada>& coord);
	Figura* adicionaPoligono(string nome, ListaEnc<Coordenada>& coord);
	Figura* adicionaBezier(string nome, ListaEnc<Coordenada>& controle);
	Figura* adicionaBspline(string nome, ListaEnc<Coordenada>& controle);
	void transladaFigura(int posicaoLista, Coordenada desloc);
	void escalonaFigura(int posicaoLista, Coordenada escala);
	void rotacionaFiguraCentroMundo(Coordenada eixo1, int posicaoLista, double anguloGraus);
	void rotacionaFiguraProprioCentro(Coordenada eixo1, int posicaoLista, double anguloGraus);
	void rotacionaFigura(Coordenada eixo0, Coordenada eixo1, int posicaoLista,
			double anguloGraus);
	void maisZoom(double passo);
	void menosZoom(double passo);
	void daZoomFiguras();
	void deslocaFiguras();
	void giraTela(double angulo);
	void mudaTamanhoDesenho(int largura, int altura);
	virtual ~Mundo();
};

#endif /* MUNDO_HPP_ */
