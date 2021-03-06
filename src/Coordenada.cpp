/*
 * Coordenada.cpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#include "Coordenada.hpp"
#include <limits>
#include <cmath>
Coordenada::Coordenada() {
	x = 0;
	y = 0;
	z = 0;
	w = 0;
	artificial = false;
}

Coordenada::Coordenada(double x, double y) {
	this->x = x;
	this->y = y;
	this->z = 0;
	this->w = 0;
	artificial = false;
}

Coordenada::Coordenada(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = 0;
	artificial = false;
}

double Coordenada::getX() const {
	return x;
}

double Coordenada::getZ() const {
	return z;
}

double Coordenada::getY() const {
	return y;
}

void Coordenada::setX(double x) {
	this->x = x;
}

void Coordenada::setY(double y) {
	this->y = y;
}

void Coordenada::setZ(double z) {
	this->z = z;
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
	double xs, ys, zs;
	xs = this->x + c2.x;
	ys = this->y + c2.y;
	zs = this->z + c2.z;
	soma = Coordenada(xs, ys, zs);
	return soma;
}

Coordenada Coordenada::operator -(const Coordenada& c2) {
	Coordenada sub;
	double xs, ys, zs;
	xs = this->x - c2.x;
	ys = this->y - c2.y;
	zs = this->z - c2.z;
	sub = Coordenada(xs, ys, zs);
	return sub;
}

Coordenada Coordenada::operator*(const Coordenada& c2) {
	Coordenada mult;
	double xs, ys, zs;
	xs = this->x * c2.x;
	ys = this->y * c2.y;
	zs = this->z * c2.z;
	mult = Coordenada(xs, ys, zs);
	return mult;
}

string Coordenada::toString() {
	return "( " + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + ")";
}

Coordenada Coordenada::operator /(const Coordenada& c2) {
	Coordenada div;
	double xs, ys, zs;
	xs = this->x / c2.x;
	ys = this->y / c2.y;
	zs = this->z / c2.z;
	div = Coordenada(xs, ys, zs);
	return div;
}

Coordenada Coordenada::operator /(const double divisor) {
	return Coordenada(x / divisor, y / divisor, z / divisor);
}

bool Coordenada::xIguais(const Coordenada& c2) {
	return x == c2.getX();
}

bool Coordenada::yIguais(const Coordenada& c2) {
	return y == c2.getY();
}

bool Coordenada::operator ==(const Coordenada& c2) const{
	double epsilon = numeric_limits<double>::epsilon();
	return abs(this->x - c2.getX()) < epsilon&&
			abs(this->y - c2.getY()) < epsilon &&
			abs(this->z - c2.getZ()) < epsilon;
}

void Coordenada::operator +=(const Coordenada& c2) {
	this->x += c2.x;
	this->y += c2.y;
	this->z += c2.z;
}

void Coordenada::operator -=(const Coordenada& c2) {
	this->x -= c2.x;
	this->y -= c2.y;
	this->z -= c2.z;
}

Coordenada Coordenada::operator *(const double mult) {
	double x, y, z;
	x = this->x*mult;
	y = this->y*mult;
	z = this->z*mult;
	return Coordenada(x, y, z);
}
