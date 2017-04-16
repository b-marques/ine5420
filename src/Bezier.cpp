/*
 * Bezier.cpp
 *
 *  Created on: 15 de abr de 2017
 *      Author: johann
 */

#include "Bezier.hpp"
#include "defineCohenSutherland.hpp"
#define nPassos 800
Bezier::Bezier(string nome, ListaEnc<Coordenada>& controle) :
		Figura(nome, BEZIER) {
	geraCurva(controle);
}

void Bezier::geraCurva(ListaEnc<Coordenada>& controle) {
	double t, x, y, t2, t3, m1, m2, m3, m4;
	Coordenada p1, p2, p3, p4, coordCurva;
	for (int c = 0; c < controle.tamanho() - 1; c += 3) {
		p1 = controle.retornaDado(c);
		p2 = controle.retornaDado(c + 1);
		p3 = controle.retornaDado(c + 2);
		p4 = controle.retornaDado(c + 3);
		for (double i = 0; i < nPassos; i++) {
			t = i / nPassos;
			t2 = pow(t, 2);
			t3 = pow(t, 3);
			m1 = -t3 + 3 * t2 - 3 * t + 1;
			m2 = 3 * t3 - 6 * t2 + 3 * t;
			m3 = -3 * t3 + 3 * t2;
			m4 = t3;
			x = p1.getX() * m1 + p2.getX() * m2 + p3.getX() * m3
					+ p4.getX() * m4;
			y = p1.getY() * m1 + p2.getY() * m2 + p3.getY() * m3
					+ p4.getY() * m4;
			coordCurva = Coordenada(x, y);
			coordenadas.adiciona(coordCurva);
			coordenadasTela.adiciona(coordCurva);

		}
	}
	calculaCentro(coordenadas);
	calculaCentro(coordenadasTela);
}

ListaEnc<ListaEnc<Coordenada> *>* Bezier::getCoordTelaClip(double xEsq,
		double xDir, double yCima, double yBaixo, int tipoClip) {
	int RC1, RC2;
	double m, x, y, deltaX;
	ListaEnc<ListaEnc<Coordenada>*>* lista;
	ListaEnc<Coordenada> *listaCoords;
	listaCoords = new ListaEnc<Coordenada>();
	for (int i = 0; i < coordenadasTela.tamanho() - 1; ++i) {
		Coordenada p1 = coordenadasTela.retornaDado(i);
		Coordenada p2 = coordenadasTela.retornaDado(i + 1);
		while (1) {
			RC1 = getCode(p1, xEsq, xDir, yCima, yBaixo);
			RC2 = getCode(p2, xEsq, xDir, yCima, yBaixo);
			if (!(RC1 | RC2)) {
				listaCoords->adiciona(p1);
				listaCoords->adiciona(p2);
				break;
			} else if (RC1 & RC2) {
				break;
			} else if (RC1 != RC2) {
				int fora = RC1 ? RC1 : RC2;
				deltaX = (p1.getX() - p2.getX());
				m = (p1.getY() - p2.getY()) / deltaX;
				if (fora & TOPO) {
					x = deltaX ?
							p1.getX() + (yCima - p1.getY()) / m : p1.getX();
					y = yCima;
				} else if (fora & FUNDO) {
					x = deltaX ?
							p1.getX() + (yBaixo - p1.getY()) / m : p1.getX();
					y = yBaixo;
				} else if (fora & ESQ) {
					x = xEsq;
					y = p1.getY() + m * (xEsq - p1.getX());
				} else if (fora & DIR) {
					x = xDir;
					y = p1.getY() + m * (xDir - p1.getX());
				}
				if (fora == RC1)
					p1 = Coordenada(x, y, 0);
				else
					p2 = Coordenada(x, y, 0);
			}
		}

	}
	if(listaCoords->tamanho() > 0){
		lista = new ListaEnc<ListaEnc<Coordenada>*>();
		lista->adiciona(listaCoords);
	} else {
		delete listaCoords;
		lista = nullptr;
	}
	return lista;
}

int Bezier::getCode(Coordenada& coord, double xEsq, double xDir, double yCima,
		double yBaixo) {
	return (coord.getX() < xEsq) | (coord.getX() > xDir) << 1
			| (coord.getY() < yBaixo) << 2 | (coord.getY() > yCima) << 3;
}

Bezier::~Bezier() {

}

