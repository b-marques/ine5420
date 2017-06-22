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
	Curva(TipoFigura tipo);
	ListaEnc<ListaEnc<Coordenada>*>* getCoordTelaClip(double xEsq,
			double xDir, double yCima, double yBaixo, int tipoClip, bool projOrtogonal,
			double focoProj, const Coordenada& centroDesenho);
	ListaEnc<Coordenada>& getControle();
	virtual ~Curva();
};

#endif /* CURVA_HPP_ */
