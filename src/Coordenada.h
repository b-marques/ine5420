/*
 * Coordenada.h
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#ifndef COORDENADA_H_
#define COORDENADA_H_

class Coordenada {
private:
	double x, y;
public:
	Coordenada();
	explicit Coordenada(double x, double y);
	double getX();
	double getY();
	//double getZ();
	void setX(double x);
	void setY(double y);
	//void setZ(double z);
	virtual ~Coordenada();
	Coordenada operator+(const Coordenada& c2);
};

#endif /* COORDENADA_H_ */
