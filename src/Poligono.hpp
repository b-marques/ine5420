/*
 * Poligono.h
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#ifndef POLIGONO_HPP_
#define POLIGONO_HPP_
#include "ListaEspecialWindow.hpp"
#include "Figura.hpp"
class Poligono: public Figura {
private:
	int getCode(const Coordenada& coord, double xEsq, double xDir, double yCima,
			double yBaixo);
	bool* entradaESaidaEForaTela(Coordenada& p1, Coordenada& p2, double xEsq,
			double xDir, double yCima, double yBaixo);
	void windowGanhaIntersecoes(ListaEnc<Coordenada>* window,
			ListaEnc<Coordenada>* inter);
	void adicionaIntersLinhaWindow(ListaEnc<Coordenada>* newWindow,
			ListaEnc<Coordenada>* interLinhaOrd, Coordenada& w1,
			Coordenada& w2);
	bool intersecTemMesmoX(Coordenada& inter, Coordenada& w1, Coordenada& w2);
	bool intersecTemMesmoY(Coordenada& inter, Coordenada& w1, Coordenada& w2);
	void geraListasWeiler(ListaEspecialWindow* window,
			ListaEnc<Coordenada>* poligono, ListaEnc<Coordenada>* entrantes,
			const ListaEnc<Coordenada>* coordsProjTela,
			double xEsq, double xDir, double yCima, double yBaixo);
public:
	Poligono(string nome, ListaEnc<Coordenada>& coord);
	ListaEnc<ListaEnc<Coordenada>*>* getCoordTelaClip(double xEsq,
			double xDir, double yCima, double yBaixo, int tipoClip, bool projOrtogonal,
			double focoProj, const Coordenada& centroDesenho);
	virtual ~Poligono();
};

#endif /* POLIGONO_HPP_ */
