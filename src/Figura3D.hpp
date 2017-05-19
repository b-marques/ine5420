/*
 * Figura3D.hpp
 *
 *  Created on: 4 de mai de 2017
 *      Author: johann
 */

#ifndef FIGURA3D_HPP_
#define FIGURA3D_HPP_

#include "Poligono.hpp"

class Figura3D: public Figura {
private:
	ListaEnc<Poligono*> superficies;
public:
	Figura3D(string nome, ListaEnc<Poligono*>& superficies);
	void translada(Coordenada& desloc, Coordenada& zoomAcumumlado,
			double giroTelaAcumulado);
	void escalona(Coordenada& escala);
	void rotacionaFiguraProprioCentro(Coordenada& origemMundoTela, Coordenada& eixo1, double anguloGraus,
			Coordenada& zoomAcumulado, double giroTelaAcumulado,
			Coordenada& centroDesenho);
	void rotaciona(Coordenada& origemMundoTela, Coordenada& eixo0, Coordenada& eixo1, double anguloGraus,
			Coordenada& zoomAcumulado, double giroTelaAcumulado,
			Coordenada& centroDesenho);
	void daZoom(Coordenada& zoom, Coordenada& centroDesenho);
	void deslocaNaTela(Coordenada& desloc);
	void rotacionaTela(Coordenada& centroDesenho, double angulo);
	ListaEnc<ListaEnc<Coordenada>*>* getCoordTelaClip(double xEsq,
			double xDir, double yCima, double yBaixo, int tipoClip, bool projOrtogonal,
			double focoProj, const Coordenada& centroDesenho);
	ListaEnc<Coordenada>& getSuperficie(int idSuper);
	const ListaEnc<Coordenada>* getSuperficieTela(int idSuper, bool projOrtogonal, double focoProj, const Coordenada& centroDesenho);
	int numSuperficies();
	virtual ~Figura3D();
};

#endif /* FIGURA3D_HPP_ */
