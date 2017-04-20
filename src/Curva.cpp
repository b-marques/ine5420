/*
 * Curva.cpp
 *
 *  Created on: 20 de abr de 2017
 *      Author: johann
 */

#include "Curva.hpp"
#include "defineCohenSutherland.hpp"
Curva::Curva(string nome, TipoFigura tipo, ListaEnc<Coordenada>& controle) : Figura(nome, tipo){
	this->controle = controle;
}

int Curva::getCode(Coordenada& coord, double xEsq, double xDir, double yCima,
		double yBaixo) {
	return (coord.getX() < xEsq) | (coord.getX() > xDir) << 1
			| (coord.getY() < yBaixo) << 2 | (coord.getY() > yCima) << 3;
}

ListaEnc<ListaEnc<Coordenada> *>* Curva::getCoordTelaClip(double xEsq,
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

ListaEnc<Coordenada>& Curva::getControle() {
	return controle;
}

Curva::~Curva() {
	// TODO Auto-generated destructor stub
}

