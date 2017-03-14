/*
 * Poligono.h
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#ifndef POLIGONO_H_
#define POLIGONO_H_
#include "Figura.h"
class Poligono : public Figura{
public:
	Poligono(string nome, double* x, double* y, int bufSize);
	virtual ~Poligono();
};

#endif /* POLIGONO_H_ */
