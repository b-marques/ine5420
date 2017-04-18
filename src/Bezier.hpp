/*
 * Bezier.hpp
 *
 *  Created on: 15 de abr de 2017
 *      Author: johann
 */

#ifndef BEZIER_HPP_
#define BEZIER_HPP_
#include "Figura.hpp"
class Bezier : public Figura{
private:
	int getCode(Coordenada& coord, double xEsq, double xDir, double yCima,
			double yBaixo);
	ListaEnc<Coordenada> controle;
public:
	Bezier(string nome, ListaEnc<Coordenada>& controle);
	void geraCurva(ListaEnc<Coordenada>& controle);
	ListaEnc<ListaEnc<Coordenada>*>* getCoordTelaClip(double xEsq, double xDir,
			double yCima, double yBaixo, int tipoClip);
	ListaEnc<Coordenada>& getControle();
	virtual ~Bezier();
};

#endif /* BEZIER_HPP_ */
