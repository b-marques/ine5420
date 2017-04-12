/*
 * Reta.cpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#include "Reta.hpp"
#define TOPO 8
#define FUNDO 4
#define DIR 2
#define ESQ 1
Reta::Reta(string nomeReta, ListaEnc<Coordenada>& coordReta) :
		Figura(nomeReta, coordReta) {
}

ListaEnc<ListaEnc<Coordenada>*>* Reta::clipCs(double xEsq, double xDir,
		double yCima, double yBaixo) {
	int RC1, RC2;
	double m, x, y, deltaX;
	ListaEnc<ListaEnc<Coordenada>*>* lista;
	ListaEnc<Coordenada> *listaCoords;
	Coordenada p1 = coordenadasTela.retornaDado(0);
	Coordenada p2 = coordenadasTela.retornaDado(1);
	while (1) {
		RC1 = getCode(p1, xEsq, xDir, yCima, yBaixo);
		RC2 = getCode(p2, xEsq, xDir, yCima, yBaixo);
		if (!(RC1 | RC2)) {
			break;
		} else if (RC1 & RC2) {
			return nullptr;
		} else if (RC1 != RC2){
			int fora = RC1 ? RC1 : RC2;
			deltaX = (p1.getX() - p2.getX());
			m = (p1.getY() - p2.getY()) / deltaX;
			if (fora & TOPO) {
				x = deltaX ? p1.getX() + (yCima - p1.getY())/m : p1.getX();
				y = yCima;
			} else if (fora & FUNDO) {
				x = deltaX ? p1.getX() + (yBaixo - p1.getY())/m : p1.getX();
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
	if(p1 == p2)
		return nullptr;
	lista = new ListaEnc<ListaEnc<Coordenada>*>();
	listaCoords = new ListaEnc<Coordenada>();
	listaCoords->adiciona(p1);
	listaCoords->adiciona(p2);
	lista->adiciona(listaCoords);
	return lista;
}

ListaEnc<ListaEnc<Coordenada> *>* Reta::getCoordTelaClip(double xEsq,
		double xDir, double yCima, double yBaixo, int tipoClip) {
	if(tipoClip == 1)
		return clipCs(xEsq, xDir, yCima, yBaixo);
	else
		return nullptr;

}

int Reta::getCode(Coordenada& coord, double xEsq, double xDir, double yCima,
		double yBaixo) {
	return (coord.getX() < xEsq) | (coord.getX() > xDir) << 1
			| (coord.getY() < yBaixo) << 2 | (coord.getY() > yCima) << 3;
}

ListaEnc<ListaEnc<Coordenada> *>* Reta::clipLb(double xEsq, double xDir,
		double yCima, double yBaixo) {
	return nullptr;
}

Reta::~Reta() {
// TODO Auto-generated destructor stub
}

