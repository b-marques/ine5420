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
	void desloca(Coordenada somaDeslocador);
	ListaEnc<Figura*> getFiguras();
	Coordenada getDeslocamento();
	void adicionaPonto(string nome, ListaEnc<Coordenada> coord);
	void adicionaReta(string nome, ListaEnc<Coordenada> coord);
	void adicionaPoligono(string nome, ListaEnc<Coordenada> coord);
	virtual ~Mundo();
};

#endif /* MUNDO_H_ */
