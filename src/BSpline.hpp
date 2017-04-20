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
	virtual ~BSpline();
};

#endif /* BSPLINE_HPP_ */
