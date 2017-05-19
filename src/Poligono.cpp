/*
 * Poligono.cpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#include "Poligono.hpp"
#include "defineCohenSutherland.hpp"
Poligono::Poligono(string nome, ListaEnc<Coordenada>& coord) :
		Figura(nome, coord, POLIGONO) {
}

Poligono::~Poligono() {
	// TODO Auto-generated destructor stub
}

ListaEnc<ListaEnc<Coordenada> *>* Poligono::getCoordTelaClip(double xEsq,
		double xDir, double yCima, double yBaixo, int tipoClip, bool projOrtogonal,
		double focoProj, const Coordenada& centroDesenho) {
	Coordenada entrante, doPoligono, daWindow;
	bool poligonoPronto;
	ListaEnc<Coordenada> *poligono, *entrantes, *temp;
	const ListaEnc<Coordenada> *coordsProjTela = this->getCoordTela(projOrtogonal, focoProj, centroDesenho);
	ListaEnc<ListaEnc<Coordenada>*> *listaPoligonos = new ListaEnc<
			ListaEnc<Coordenada>*>();
	ListaEspecialWindow *window = new ListaEspecialWindow(xEsq, xDir, yCima,
			yBaixo);
	poligono = new ListaEnc<Coordenada>();
	entrantes = new ListaEnc<Coordenada>();
	geraListasWeiler(window, poligono, entrantes, coordsProjTela, xEsq, xDir, yCima, yBaixo);
	window->retiraInfEsqDuplicado();

	if(entrantes->tamanho() == 0){
		if(getCode(coordsProjTela->retornaDado(0), xEsq, xDir, yCima, yBaixo)){
			delete listaPoligonos;
			listaPoligonos = nullptr;
		} else {
			temp = new ListaEnc<Coordenada>();
			*temp = *coordsProjTela;
			listaPoligonos->adiciona(temp);
		}
	}
	for (; entrantes->tamanho() > 0;) {
		poligonoPronto = false;
		temp = new ListaEnc<Coordenada>();
		entrante = entrantes->retiraDoInicio();
		temp->adiciona(entrante);
		daWindow = entrante;
		while (!poligonoPronto) {
			for (int j = poligono->posicao(daWindow) + 1; !poligonoPronto; j++) {
				doPoligono = poligono->retornaDado(j % poligono->tamanho());
				if (doPoligono.artificial) {
					if(entrantes->contem(doPoligono))
						entrantes->retiraEspecifico(doPoligono);
					if (temp->contem(doPoligono))
						poligonoPronto = true;
					else {
						temp->adiciona(doPoligono);
						break;
					}

				}
				temp->adiciona(doPoligono);
			}
			for (int k = window->posicao(doPoligono) + 1; !poligonoPronto; k++) {
				daWindow = window->retornaDado(k % window->tamanho());
				if (daWindow.artificial) {
					if(entrantes->contem(daWindow))
						entrantes->retiraEspecifico(daWindow);
					if (temp->contem(daWindow))
						poligonoPronto = true;
					else {
						temp->adiciona(daWindow);
						break;
					}
				}
				temp->adiciona(daWindow);
			}
		}
		listaPoligonos->adiciona(temp);
	}
	delete poligono;
	delete window;
	delete entrantes;
	if(!projOrtogonal)
		delete coordsProjTela;
	return listaPoligonos;
}

void Poligono::geraListasWeiler(ListaEspecialWindow* window,
		ListaEnc<Coordenada>* poligono, ListaEnc<Coordenada>* entrantes,
		const ListaEnc<Coordenada>* coordsProjTela,
		double xEsq, double xDir, double yCima, double yBaixo) {
	bool* mudancas;
	Coordenada p1, p2;
	ListaEnc<Coordenada> *coordsTela = new ListaEnc<Coordenada>();
	*coordsTela = *coordsProjTela;
	coordsTela->adiciona(coordsProjTela->retornaDado(0));
	for (int i = 0; i < coordsTela->tamanho() - 1; i++) {
		p1 = coordsTela->retornaDado(i);
		p2 = coordsTela->retornaDado(i + 1);
		poligono->adiciona(p1);
		mudancas = entradaESaidaEForaTela(p1, p2, xEsq, xDir, yCima, yBaixo);
		if (!mudancas[2]) {
			if (mudancas[0] && mudancas[1]) {
				p1.artificial = true;
				p2.artificial = true;
				poligono->adiciona(p1);
				poligono->adiciona(p2);
				entrantes->adiciona(p1);
				window->addCoordArtificial(p1);
				window->addCoordArtificial(p2);
			} else if (!mudancas[0] && mudancas[1]) {
				p2.artificial = true;
				poligono->adiciona(p2);
				window->addCoordArtificial(p2);
			} else if (mudancas[0] && !mudancas[1]) {
				p1.artificial = true;
				poligono->adiciona(p1);
				window->addCoordArtificial(p1);
				entrantes->adiciona(p1);
			}
		}
		delete mudancas;
	}
	delete coordsTela;
}

bool* Poligono::entradaESaidaEForaTela(Coordenada& p1, Coordenada& p2,
		double xEsq, double xDir, double yCima, double yBaixo) {
	int RC1, RC2;
	bool p1mudou = false, p2mudou = false, foraTela = false;
	double deltaX, x, y, m;
	while (1) {
		RC1 = getCode(p1, xEsq, xDir, yCima, yBaixo);
		RC2 = getCode(p2, xEsq, xDir, yCima, yBaixo);
		if (!(RC1 | RC2)) {
			break;
		} else if (RC1 & RC2) {
			foraTela = true;
			p1mudou = false;
			p2mudou = false;
			break;
		} else if (RC1 != RC2) {
			int fora = RC1 ? RC1 : RC2;
			deltaX = (p1.getX() - p2.getX());
			m = (p1.getY() - p2.getY()) / deltaX;
			if (fora & TOPO) {
				x = deltaX ? p1.getX() + (yCima - p1.getY()) / m : p1.getX();
				y = yCima;
			} else if (fora & FUNDO) {
				x = deltaX ? p1.getX() + (yBaixo - p1.getY()) / m : p1.getX();
				y = yBaixo;
			} else if (fora & ESQ) {
				x = xEsq;
				y = p1.getY() + m * (xEsq - p1.getX());
			} else if (fora & DIR) {
				x = xDir;
				y = p1.getY() + m * (xDir - p1.getX());
			}
			if (fora == RC1) {
				p1 = Coordenada(x, y, 0);
				p1mudou = true;
			} else {
				p2 = Coordenada(x, y, 0);
				p2mudou = true;
			}
		}
	}
	bool *retorno = new bool[3];
	retorno[0] = p1mudou;
	retorno[1] = p2mudou;
	retorno[2] = foraTela;
	return retorno;
}

int Poligono::getCode(const Coordenada& coord, double xEsq, double xDir, double yCima,
		double yBaixo) {
	return (coord.getX() < xEsq) | (coord.getX() > xDir) << 1
			| (coord.getY() < yBaixo) << 2 | (coord.getY() > yCima) << 3;
}
