/*
 * Poligono.cpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#include "Poligono.h"
#include "Coordenada.h"
Poligono::Poligono(string nome, vector<double> xvec, vector<double> yvec) : Figura(nome){
	double x, y;
	for (int i = 0; i < (int) xvec.size(); i++) {
		x = xvec.at(i);
		y = yvec.at(i);
		this->coordenadas.adiciona(Coordenada(x, y));
	}
}

Poligono::~Poligono() {
	// TODO Auto-generated destructor stub
}

