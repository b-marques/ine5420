/*
 * Reta.h
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#ifndef RETA_H_
#define RETA_H_
#include "Figura.h"

class Reta: public Figura {
public:
	Reta(string nome, double xi, double yi, double xf, double yf);
	virtual ~Reta();
};

#endif /* RETA_H_ */
