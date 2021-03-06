/*
 * SuperficieBspline.cpp
 *
 *  Created on: 17 de jun de 2017
 *      Author: johann
 */

#include "SuperficieBspline.hpp"
#include "BSpline.hpp"
#define nt 20
#define ns 20
#define passoCurva 100

SuperficieBspline::SuperficieBspline(string nome, ListaEnc<Coordenada>& controle) : SuperficieBicubica(nome, SUPERBSPLINE) {
	geraSuperficie(controle);
}

void SuperficieBspline::geraSuperficie(ListaEnc<Coordenada>& controle) {
	double s, s2, s3, t, t2, t3, x[16], y[16], z[16], xResult, yResult,
	zResult;
	int numSupers;
	Coordenada coordControle;
	ListaEnc<Coordenada>* curva = new ListaEnc<Coordenada>();
	numSupers = (controle.tamanho() - 4)/12;
	for (int iteracao = 0; iteracao < numSupers; iteracao++) {
		for (int i = iteracao*12; i < 16+(12*iteracao); i++) {
			coordControle = controle.retornaDado(i);
			x[i] = coordControle.getX();
			y[i] = coordControle.getY();
			z[i] = coordControle.getZ();
		}

		for (double j = 0; j <= ns; j++) {
			s = j / ns;
			s2 = pow(s, 2);
			s3 = pow(s, 2);
			for (double i = 0; i <= passoCurva; i++) {
				t = i/passoCurva;
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
		for (double j = 0; j <= nt; j++) {
			t = j / nt;
			t2 = pow(t, 2);
			t3 = pow(t, 3);
			for (double i = 0; i <= passoCurva; i++) {
				s = i/passoCurva;
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
