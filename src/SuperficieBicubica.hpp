/*
 * Superficie.hpp
 *
 *  Created on: 17 de jun de 2017
 *      Author: johann
 */

#ifndef SUPERFICIEBICUBICA_HPP_
#define SUPERFICIEBICUBICA_HPP_
#include "Curva.hpp"

class SuperficieBicubica : public Figura{
protected:
	ListaEnc<Curva*> curvas;

public:
	SuperficieBicubica(string nome, TipoFigura tipo);
	virtual ~SuperficieBicubica();
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
	void recemAdicionada(Coordenada origemMundoTela, Coordenada& zoom, Coordenada& centroDesenho, double giroTela);
	ListaEnc<Coordenada>& getCurva(int idCurva);
	const ListaEnc<Coordenada>* getCurvaTela(int idSuper, bool projOrtogonal, double focoProj, const Coordenada& centroDesenho);
	int numCurvas();
	ListaEnc<ListaEnc<Coordenada>*>* getCoordTelaClip(double xEsq,
				double xDir, double yCima, double yBaixo, int tipoClip, bool projOrtogonal,
				double focoProj, const Coordenada& centroDesenho);
};

#endif /* SUPERFICIEBICUBICA_HPP_ */
