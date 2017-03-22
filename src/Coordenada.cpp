/*
 * Coordenada.cpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#include "Coordenada.hpp"

Coordenada::Coordenada() {
	x=0;
	y=0;
}

Coordenada::Coordenada(double x, double y) {
	this->x = x;
	this->y = y;
}

double Coordenada::getX() const{
	return x;
}

double Coordenada::getY() const{
	return y;
}

void Coordenada::setX(double x) {
	this->x = x;
}

void Coordenada::setY(double y) {
	this->y = y;
}




Coordenada::~Coordenada() {
	// TODO Auto-generated destructor stub
}

bool Coordenada::xMaiorQue(const Coordenada& c2) {
	return x > c2.getX();
}

bool Coordenada::yMaiorQue(const Coordenada& c2) {
	return y > c2.getY();
}

bool Coordenada::xMenorQue(const Coordenada& c2) {
	return x < c2.getX();
}

bool Coordenada::yMenorQue(const Coordenada& c2) {
	return y < c2.getY();
}

Coordenada Coordenada::operator+(const Coordenada& c2) {
	Coordenada soma;
	double xs, ys;
	xs = this->x + c2.x;
	ys = this->y + c2.y;
	soma = Coordenada(xs, ys);
	return soma;
}

Coordenada Coordenada::operator -(const Coordenada& c2) {
	Coordenada sub;
	double xs, ys;
	xs = this->x - c2.x;
	ys = this->y - c2.y;
	sub = Coordenada(xs, ys);
	return sub;
}

Coordenada Coordenada::operator*(const Coordenada& c2) {
	Coordenada mult;
	double xs, ys;
	xs = this->x * c2.x;
	ys = this->y * c2.y;
	mult = Coordenada(xs, ys);
	return mult;
}

Coordenada Coordenada::operator /(const double divisor) {
	return Coordenada(x/divisor, y/divisor);
}
