/*
 * Mundo.h
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#ifndef MUNDO_H_
#define MUNDO_H_
#include "Figura.h"
class Mundo {
private:
	ListaEnc<Figura*> *figuras;
	Coordenada deslocamento;
public:
	Mundo();
	void desloca(double dx, double dy);
	ListaEnc<Figura*>* getFiguras();
	void adicionaReta(string nome, double xi, double yi, double xf, double yf);
	virtual ~Mundo();
};

#endif /* MUNDO_H_ */
