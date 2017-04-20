/*
 * BSpline.hpp
 *
 *  Created on: 19 de abr de 2017
 *      Author: johann
 */

#ifndef BSPLINE_HPP_
#define BSPLINE_HPP_

#include "Figura.hpp"

class BSpline: public Figura {
private:
	ListaEnc<Coordenada> controle;
	void geraCurva(ListaEnc<Coordenada>& controle);
	void fwdDif(double n, double *dx, double *dy);
public:
	BSpline(string nome, ListaEnc<Coordenada>& controle);
	ListaEnc<ListaEnc<Coordenada>*>* getCoordTelaClip(double xEsq,
				double xDir, double yCima, double yBaixo, int tipoClip);
	int getCode(Coordenada& coord, double xEsq, double xDir, double yCima,
			double yBaixo);
	ListaEnc<Coordenada>& getControle();
	virtual ~BSpline();
};

#endif /* BSPLINE_HPP_ */
