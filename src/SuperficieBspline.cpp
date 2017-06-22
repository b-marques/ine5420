/*
 * SuperficieBspline.cpp
 *
 *  Created on: 17 de jun de 2017
 *      Author: johann
 */

#include "SuperficieBspline.hpp"
#include "BSpline.hpp"
#define deltaT 0.05
#define deltaS 0.05
#define passoCurva 100

SuperficieBspline::SuperficieBspline(string nome, ListaEnc<Coordenada>& controle) : SuperficieBicubica(nome, SUPERBSPLINE) {
	geraSuperficie(controle);
}

void SuperficieBspline::geraSuperficie(ListaEnc<Coordenada>& controle) {
	double s, s2, s3, t, t2, t3, x[16], y[16], z[16], xResult, yResult,
	zResult;
	Coordenada coordControle;
	ListaEnc<Coordenada>* curva = new ListaEnc<Coordenada>();
	for (int i = 0; i < controle.tamanho(); i++) {
		coordControle = controle.retornaDado(i);
		x[i] = coordControle.getX();
		y[i] = coordControle.getY();
		z[i] = coordControle.getZ();
	}

	for (double s = 0; s <= 1.0; s += deltaS) {
		s2 = pow(s, 2);
		s3 = pow(s, 2);
		for (double i = 0; i <= passoCurva; i++) {
			t = (double) i/passoCurva;
			t2 = pow(t, 2);
			t3 = pow(t, 3);
			xResult = calculaCoordSuperficie(x, s, s2, s3, t, t2, t3);
			yResult = calculaCoordSuperficie(y, s, s2, s3, t, t2, t3);
			zResult = calculaCoordSuperficie(z, s, s2, s3, t, t2, t3);
			curva->adiciona(Coordenada(xResult, yResult, zResult));
		}
		curvas.adiciona(new BSpline(*curva));
		curva->destroiLista();
	}
	for (double t = 0; t <= 1.0; t += deltaT) {
		t2 = pow(t, 2);
		t3 = pow(t, 3);
		for (double i = 0; i <= passoCurva; i++) {
			s = (double) i/passoCurva;
			s2 = pow(s, 2);
			s3 = pow(s, 2);
			xResult = calculaCoordSuperficie(x, s, s2, s3, t, t2, t3);
			yResult = calculaCoordSuperficie(y, s, s2, s3, t, t2, t3);
			zResult = calculaCoordSuperficie(z, s, s2, s3, t, t2, t3);
			curva->adiciona(Coordenada(xResult, yResult, zResult));
		}
		curvas.adiciona(new BSpline(*curva));
		curva->destroiLista();
	}
	delete curva;
}

double SuperficieBspline::calculaCoordSuperficie(double* a, double s, double s2,
		double s3, double t, double t2, double t3) {
	double resultado;
	resultado = (1.0/36)*a[0]*(-3*s + 3*s2 - s3 + 1) + 4*a[1]*(-3*s + 3*s2 - s3 + 1)
			+ a[10]*(3*s + 3*s2 - 3*s3 + 1) +
			a[12]*s3 + 4*a[13]*s3 + a[14]*s3 + a[2]*(-3*s + 3*s2 - s3 + 1) +
	   a[4]*(-6*s2 + 3*s3 + 4) + 4*a[5]*(-6*s2 + 3*s3 + 4) + a[6]*(-6*s2 + 3*s3 + 4)
	   + a[8]*(3*s + 3*s2 - 3*s3 + 1) + 4*a[9]*(3*s + 3*s2 - 3*s3 + 1) + t*(-3*a[0]*
	  (-3*s + 3*s2 - s3 + 1) + 3*a[10]*(3*s + 3*s2 - 3*s3 + 1) - 3*a[12]*s3 + 3*a[14]*s3 +
	  3*a[2]*(-3*s + 3*s2 - s3 + 1) - 3*a[4]*(-6*s2 + 3*s3 + 4) + 3*a[6]*(-6*
	  s2 + 3*s3 + 4) - 3*a[8]*(3*s + 3*s2 - 3*s3 + 1)) + t2*(3*a[0]*(-3*s + 3*s2 -
	   s3 + 1) - 6*a[1]*(-3*s + 3*s2 - s3 + 1) + 3*a[10]*(3*s + 3*s2 - 3*s3 + 1) +
	   3*a[12]*s3 - 6*a[13]*s3 + 3*a[14]*s3 + 3*a[2]*(-3*s + 3*s2 - s3 + 1) + 3*a[4]*(-6
	  *s2 + 3*s3 + 4) - 6*a[5]*(-6*s2 + 3*s3 + 4) + 3*a[6]*(-6*s2 + 3*s3 + 4) + 3*
	  a[8]*(3*s + 3*s2 - 3*s3 + 1) - 6*a[9]*(3*s + 3*s2 - 3*s3 + 1)) + t3*(-a[0]*(-3
	  *s + 3*s2 - s3 + 1) + 3*a[1]*(-3*s + 3*s2 - s3 + 1) - 3*a[10]*(3*s + 3*s2 -
	  3*s3 + 1) + a[11]*(3*s + 3*s2 - 3*s3 + 1) - a[12]*s3 + 3*a[13]*s3 - 3*a[14]*s3 +
	   a[15]*s3 - 3*a[2]*(-3*s + 3*s2 - s3 + 1) + a[3]*(-3*s + 3*s2 - s3 + 1) - a[4]*(
	  -6*s2 + 3*s3 + 4) + 3*a[5]*(-6*s2 + 3*s3 + 4) - 3*a[6]*(-6*s2 + 3*s3 + 4) +
	  a[7]*(-6*s2 + 3*s3 + 4) - a[8]*(3*s + 3*s2 - 3*s3 + 1) + 3*a[9]*(3*s + 3*s2 -
	  3*s3 + 1));
	return resultado;
}

SuperficieBspline::~SuperficieBspline() {
}
