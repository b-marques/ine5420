/*
 * Bezier.cpp
 *
 *  Created on: 15 de abr de 2017
 *      Author: johann
 */

#include "Bezier.hpp"
#define nPassos 100
Bezier::Bezier(string nome, ListaEnc<Coordenada>& controle) :
		Curva(nome, BEZIER, controle) {
	this->controle = controle;
	geraCurva(controle);
}

void Bezier::geraCurva(ListaEnc<Coordenada>& controle) {
	double i, x, y, t2, t3, m1, m2, m3, m4;
	Coordenada p1, p2, p3, p4, coordCurva;
	i = (double) 1 / nPassos;
	for (int c = 0; c < controle.tamanho() - 1; c += 3) {
		p1 = controle.retornaDado(c);
		p2 = controle.retornaDado(c + 1);
		p3 = controle.retornaDado(c + 2);
		p4 = controle.retornaDado(c + 3);
		for (double t = 0; t <= 1; t += i) {
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

Bezier::~Bezier() {

}

