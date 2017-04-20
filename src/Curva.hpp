/*
 * Curva.hpp
 *
 *  Created on: 20 de abr de 2017
 *      Author: johann
 */

#ifndef CURVA_HPP_
#define CURVA_HPP_

#include "Figura.hpp"

class Curva: public Figura {
protected:
	ListaEnc<Coordenada> controle;
	int getCode(Coordenada& coord, double xEsq, double xDir, double yCima,
			double yBaixo);
public:
	Curva(string nome, TipoFigura tipo, ListaEnc<Coordenada>& controle);
	ListaEnc<ListaEnc<Coordenada>*>* getCoordTelaClip(double xEsq,
				double xDir, double yCima, double yBaixo, int tipoClip);
	ListaEnc<Coordenada>& getControle();
	virtual ~Curva();
};

#endif /* CURVA_HPP_ */
