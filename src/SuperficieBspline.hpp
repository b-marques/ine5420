/*
 * SuperficieBspline.h
 *
 *  Created on: 17 de jun de 2017
 *      Author: johann
 */

#ifndef SUPERFICIEBSPLINE_HPP_
#define SUPERFICIEBSPLINE_HPP_
#include "SuperficieBicubica.hpp"

class SuperficieBspline : public SuperficieBicubica{
private:
	void geraSuperficie(ListaEnc<Coordenada>& controle);
	double calculaCoordSuperficie(double* a, double s, double s2, double s3,
			double t, double t2, double t3);
public:
	SuperficieBspline(string nome, ListaEnc<Coordenada>& controle);
	virtual ~SuperficieBspline();
};

#endif /* SUPERFICIEBSPLINE_HPP_ */
