/*
 * Bezier.hpp
 *
 *  Created on: 15 de abr de 2017
 *      Author: johann
 */

#ifndef BEZIER_HPP_
#define BEZIER_HPP_
#include "Curva.hpp"
class Bezier : public Curva {
private:
	int getCode(Coordenada& coord, double xEsq, double xDir, double yCima,
			double yBaixo);
	ListaEnc<Coordenada> controle;
	void geraCurva(ListaEnc<Coordenada>& controle);
public:
	Bezier(string nome, ListaEnc<Coordenada>& controle);
	Bezier(ListaEnc<Coordenada>& coords);
	virtual ~Bezier();
};

#endif /* BEZIER_HPP_ */
