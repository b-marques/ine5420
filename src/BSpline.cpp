/*
 * BSpline.cpp
 *
 *  Created on: 19 de abr de 2017
 *      Author: johann
 */

#include "BSpline.hpp"
#include "defineCohenSutherland.hpp"
#include <math.h>
#define k 0.2
BSpline::BSpline(string nome, ListaEnc<Coordenada>& controle) : Figura(nome, BSPLINE) {
	this->controle = controle;
	geraCurva(controle);
}

void BSpline::geraCurva(ListaEnc<Coordenada>& controle) {
	double k2 = pow(k, 2), k3 = pow(k, 3), nPassos = 1/k;
	double cx[4], cy[4];
	double *dx = new double[4], *dy = new double[4];
	Coordenada p1, p2, p3, p4;
	for (int i = 0; i < controle.tamanho() - 3; i++) {
		p1 = controle.retornaDado(i);
		p2 = controle.retornaDado(i+1);
		p3 = controle.retornaDado(i+2);
		p4 = controle.retornaDado(i+3);
		// Cx = Mbs * Gx  // Cy = Mbs * Gy
		cx[0] = 1.0/6.0 * (-1*p1.getX() + 3*p2.getX() - 3*p3.getX() + 1*p4.getX());
		cx[1] = 1.0/6.0 * (3*p1.getX() - 6*p2.getX() + 3*p3.getX());
		cx[2] = 1.0/6.0 * (-3*p1.getX() + 3*p3.getX());
		cx[3] = 1.0/6.0 * (p1.getX() + 4*p2.getX() + p3.getX());

		cy[0] = 1.0/6.0 * (-1*p1.getY() + 3*p2.getY() - 3*p3.getY() + 1*p4.getY());
		cy[1] = 1.0/6.0 * (3*p1.getY() - 6*p2.getY() + 3*p3.getY());
		cy[2] = 1.0/6.0 * (-3*p1.getY() + 3*p3.getY());
		cy[3] = 1.0/6.0 * (p1.getY() + 4*p2.getY() + p3.getY());

		dx[0] = cx[3];
		dx[1] = k3*cx[0] + k2*cx[1] + k*cx[2];
		dx[2] = 6*k3*cx[0] + 2*k2*cx[1];
		dx[3] = 6*k3*cx[0];

		dy[0] = cy[3];
		dy[1] = k3*cy[0] + k2*cy[1] + k*cy[2];
		dy[2] = 6*k3*cy[0] + 2*k2*cy[1];
		dy[3] = 6*k3*cy[0];
		fwdDif(nPassos, dx, dy);
	}
	delete dx;
	delete dy;
}

void BSpline::fwdDif(double nPassos, double* dx, double* dy) {
	Coordenada add  = Coordenada(dx[0], dy[0]);
	coordenadas.adiciona(add);
	coordenadasTela.adiciona(add);
	for (int i = 1; i < nPassos; i++) {
		dx[0] = dx[0] + dx[1];
		dx[1] = dx[1] + dx[2];
		dx[2] = dx[2] + dx[3];

		dy[0] = dy[0] + dy[1];
		dy[1] = dy[1] + dy[2];
		dy[2] = dy[2] + dy[3];
		add = Coordenada(dx[0], dy[0]);
 		coordenadas.adiciona(add);
		coordenadasTela.adiciona(add);
	}
}

ListaEnc<ListaEnc<Coordenada> *>* BSpline::getCoordTelaClip(double xEsq,
		double xDir, double yCima, double yBaixo, int tipoClip) {
	int RC1, RC2, nVezes;
	bool p2mudou;
	double m, x, y, deltaX;
	Coordenada p1, p2;
	ListaEnc<ListaEnc<Coordenada>*>* lista;
	ListaEnc<Coordenada> *listaCoords;
	listaCoords = new ListaEnc<Coordenada>();
	lista = new ListaEnc<ListaEnc<Coordenada>*>();
	nVezes = coordenadasTela.tamanho() - 1;
	for (int i = 0; i < nVezes; i++) {
		p1 = coordenadasTela.retornaDado(i);
		p2 = coordenadasTela.retornaDado(i + 1);
		p2mudou = false;
		while (1) {
			RC1 = getCode(p1, xEsq, xDir, yCima, yBaixo);
			RC2 = getCode(p2, xEsq, xDir, yCima, yBaixo);
			if (!(RC1 | RC2)) {
				listaCoords->adiciona(p1);
				if(p2mudou)
					listaCoords->adiciona(p2);
				break;
			} else if (RC1 & RC2) {
				if(listaCoords->tamanho()>0){
					lista->adiciona(listaCoords);
					listaCoords = new ListaEnc<Coordenada>();
				}
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
				else{
					p2 = Coordenada(x, y, 0);
					p2mudou = true;
				}
			}
		}
	}
	if(!RC2 && !p2mudou)
		listaCoords->adiciona(p2);
	if(listaCoords->tamanho() > 0){
		lista->adiciona(listaCoords);
	} else {
		delete listaCoords;
		if(lista->tamanho() == 0){
			delete lista;
			lista = nullptr;
		}
	}
	return lista;
}

int BSpline::getCode(Coordenada& coord, double xEsq, double xDir, double yCima,
		double yBaixo) {
	return (coord.getX() < xEsq) | (coord.getX() > xDir) << 1
			| (coord.getY() < yBaixo) << 2 | (coord.getY() > yCima) << 3;
}

ListaEnc<Coordenada>& BSpline::getControle() {
	return controle;
}

BSpline::~BSpline() {
	// TODO Auto-generated destructor stub
}

