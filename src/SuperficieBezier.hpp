/*
 * SuperficieBezier.hpp
 *
 *  Created on: 25 de mai de 2017
 *      Author: johann
 */

#ifndef SUPERFICIEBEZIER_HPP_
#define SUPERFICIEBEZIER_HPP_
#include "Bezier.hpp"
#include "SuperficieBicubica.hpp"
class SuperficieBezier : public SuperficieBicubica{
private:
	void geraSuperficie(ListaEnc<Coordenada>& controle);
	double calculaCoordSuperficie(double* a, double s, double s2, double s3,
			double t, double t2, double t3);
public:
	SuperficieBezier(string nome, ListaEnc<Coordenada>& controle);
	virtual ~SuperficieBezier();
};

#endif /* SUPERFICIEBEZIER_HPP_ */
