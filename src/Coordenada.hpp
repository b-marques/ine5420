/*
 * Coordenada.h
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#ifndef COORDENADA_HPP_
#define COORDENADA_HPP_

class Coordenada {
private:
	double x, y;
public:
	Coordenada();
	explicit Coordenada(double x, double y);
	double getX() const;
	double getY() const;
	//double getZ();
	void setX(double x);
	void setY(double y);
	//void setZ(double z);
	virtual ~Coordenada();
	bool xMaiorQue(const Coordenada& c2);
	bool yMaiorQue(const Coordenada& c2);
	bool xMenorQue(const Coordenada& c2);
	bool yMenorQue(const Coordenada& c2);
	Coordenada operator+(const Coordenada& c2);
	Coordenada operator-(const Coordenada& c2);
	Coordenada operator*(const Coordenada& c2);
	Coordenada operator/(const double divisor);
};

#endif /* COORDENADA_HPP_ */
