/*
 * Coordenada.cpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#include "Coordenada.h"

Coordenada::Coordenada() {
	x=0;
	y=0;
}

Coordenada::Coordenada(double x, double y) {
	this->x = x;
	this->y = y;
}

double Coordenada::getX() {
	return x;
}

double Coordenada::getY() {
	return y;
}

void Coordenada::setX(double x) {
	this->x = x;
}

void Coordenada::setY(double y) {
	this->y = y;
}



Coordenada Coordenada::operator+(const Coordenada& c2) {
	Coordenada soma;
	double xs, ys;
	xs = this->x + c2.x;
	ys = this->y + c2.y;
	soma = Coordenada(xs, ys);
	return soma;
}

Coordenada::~Coordenada() {
	// TODO Auto-generated destructor stub
}

