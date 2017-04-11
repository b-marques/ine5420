/*
 * Coordenada.h
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#ifndef COORDENADA_HPP_
#define COORDENADA_HPP_
#include <string>
using namespace std;

class Coordenada {
private:
	double x, y, z, w;
public:
	Coordenada();
	Coordenada(double x, double y);
	Coordenada(double x, double y, double z);
	double getX() const;
	double getY() const;
	double getZ() const;
	void setX(double x);
	void setY(double y);
	void setZ(double z);
	virtual ~Coordenada();
	bool xMaiorQue(const Coordenada& c2);
	bool yMaiorQue(const Coordenada& c2);
	bool xMenorQue(const Coordenada& c2);
	bool yMenorQue(const Coordenada& c2);
	string toString();
	Coordenada operator+(const Coordenada& c2);
	Coordenada operator-(const Coordenada& c2);
	Coordenada operator*(const Coordenada& c2);
	Coordenada operator/(const Coordenada& c2);
	Coordenada operator/(const double divisor);
	bool operator==(const Coordenada& c2);
};

#endif /* COORDENADA_HPP_ */
