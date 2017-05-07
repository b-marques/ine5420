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


enum TipoFigura {PONTO, RETA, POLIGONO, BEZIER, BSPLINE, FIGURA3D};

class Figura {
protected:
	ListaEnc<Coordenada> coordenadas;
	ListaEnc<Coordenada> coordenadasTela;
	Coordenada centro, centroRelTela;
	string nome;
	TipoFigura tipo;
	void transform(const Coordenada& eixo, double grau, const Coordenada& escalonamento,
			const Coordenada& deslocamento);
	void transformTela(const Coordenada& eixo, double grau, const Coordenada& escalonamento,
			const Coordenada& deslocamento);
public:
	Figura(string nome, TipoFigura tipo);
	Figura(string nome, ListaEnc<Coordenada>& coord, TipoFigura tipo);
	ListaEnc<Coordenada>& getCoord();
	ListaEnc<Coordenada>& getCoordTela();
	virtual ListaEnc<ListaEnc<Coordenada>*>* getCoordTelaClip(double xEsq,
			double xDir, double yCima, double yBaixo, int tipoClip) = 0;
	string getNome();
	Coordenada calculaCentro(ListaEnc<Coordenada>& coords);
	virtual void translada(Coordenada& desloc, Coordenada& zoomAcumumlado,
			double giroTelaAcumulado);
	virtual void escalona(Coordenada& escala);
	virtual void rotacionaFiguraProprioCentro(Coordenada& origemMundoTela, Coordenada& eixo1, double anguloGraus,
			Coordenada& zoomAcumulado, double giroTelaAcumulado,
			Coordenada& centroDesenho);
	virtual void rotaciona(Coordenada& origemMundoTela, Coordenada& eixo0, Coordenada& eixo1, double anguloGraus,
			Coordenada& zoomAcumulado, double giroTelaAcumulado,
			Coordenada& centroDesenho);
	virtual void daZoom(Coordenada& zoom, Coordenada& centroDesenho);
	virtual void deslocaNaTela(Coordenada& desloc);
	virtual void rotacionaTela(Coordenada& centroDesenho, double angulo);
	TipoFigura getTipo();
	Coordenada getCentro();
	void recemAdicionada(Coordenada origemMundoTela, Coordenada& zoom, Coordenada& centroDesenho, double giroTela);
	virtual ~Figura();
};

#endif /* FIGURA_HPP_ */
