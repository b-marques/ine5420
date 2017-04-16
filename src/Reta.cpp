/*
 * Reta.cpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#include "Reta.hpp"
#include "defineCohenSutherland.hpp"
Reta::Reta(string nomeReta, ListaEnc<Coordenada>& coordReta) :
		Figura(nomeReta, coordReta, RETA) {
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
	if (tipoClip == 1)
		return clipCs(xEsq, xDir, yCima, yBaixo);
	else if (tipoClip == 2) {
		return clipLb(xEsq, xDir, yCima, yBaixo);
	} else {
		return nullptr;
	}
}

int Reta::getCode(Coordenada& coord, double xEsq, double xDir, double yCima,
		double yBaixo) {
	return (coord.getX() < xEsq) | (coord.getX() > xDir) << 1
			| (coord.getY() < yBaixo) << 2 | (coord.getY() > yCima) << 3;
}

ListaEnc<ListaEnc<Coordenada> *>* Reta::clipLb(double xEsq, double xDir,
		double yCima, double yBaixo) {

	ListaEnc<Coordenada>* coordenadasClipadas = new ListaEnc<Coordenada>();
	ListaEnc<ListaEnc<Coordenada>*>* lista = new ListaEnc<ListaEnc<Coordenada>*>();

	Coordenada ponto1 = coordenadasTela.retornaDado(0);
	Coordenada ponto2 = coordenadasTela.retornaDado(1);
	
	double t0 = 0.0;    double t1 = 1.0;
    double xdelta = ponto1.getX() - ponto2.getX();
    double ydelta = ponto1.getY() - ponto2.getY();

    double p[4],q[4],r[4];

	p[0] = -xdelta;    q[0] = -(xEsq-ponto1.getX());
    p[1] = xdelta;     q[1] =  (xDir-ponto1.getX());
    p[2] = -ydelta;    q[2] = -(yBaixo-ponto1.getY());
    p[3] = ydelta;     q[3] =  (yCima-ponto1.getY());


    for(int i=0; i<4; i++) {
        
        if(p[i]==0 && q<0) return nullptr;   // Paralela a window pelo lado de fora

        if(p[i]<0) {
        	r[i] = q[i]/p[i];
            if(r[i]>t1) return nullptr;
            else if(r[i]>t0) t0=r[i];
        } else if(p[i]>0) {
        	r[i] = q[i]/p[i];
            if(r[i]<t0) return nullptr;
            else if(r[i]<t1) t1=r[i];
        }
    }

    double newx1 = ponto1.getX() + t0*xdelta;
    double newy1 = ponto1.getY() + t0*ydelta;
    double newx2 = ponto1.getX() + t1*xdelta;
    double newy2 = ponto1.getY() + t1*ydelta;

    coordenadasClipadas->adiciona(Coordenada(newx1,newy1));
    coordenadasClipadas->adiciona(Coordenada(newx2, newy2));
    lista->adiciona(coordenadasClipadas);
  	return lista;
}

Reta::~Reta() {
// TODO Auto-generated destructor stub
}

