/*
 * Mundo.cpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#include "Mundo.hpp"
#include <math.h>
#include "Poligono.hpp"
#include "Ponto.hpp"
#include "Reta.hpp"

Mundo::Mundo(double larguraArea, double alturaArea) {
	this->larguraArea = larguraArea;
	this->alturaArea = alturaArea;
	deslocamento = Coordenada(0, 0);
	zoom = Coordenada(1, 1);
	centroDesenho = Coordenada(larguraArea / 2, alturaArea / 2);
	figuras = new ListaEnc<Figura*>();
}

void Mundo::desloca(double passo, TipoMovimento sentido) {
	Coordenada deltaDesloc;
	double dx = passo * larguraArea / 100;
	double dy = passo * alturaArea / 100;
	switch (sentido) {
	case CIMA:
		deltaDesloc = Coordenada(0, -dy);
		break;
	case BAIXO:
		deltaDesloc = Coordenada(0, +dy);
		break;
	case DIREITA:
		deltaDesloc = Coordenada(-dx, 0);
		break;
	case ESQUERDA:
		deltaDesloc = Coordenada(+dx, 0);
		break;
	default:
		break;
	}
	deslocamento = deslocamento + deltaDesloc;
	centroDesenho = centroDesenho - deltaDesloc;
}

Coordenada Mundo::getDeslocamento() {
	return deslocamento;
}

Coordenada Mundo::getZoom() {
	return zoom;
}

Coordenada Mundo::getCentroDesenho() {
	return centroDesenho;
}

void Mundo::adicionaPonto(string nome, ListaEnc<Coordenada>& coord) {
	Ponto* p = new Ponto(nome, coord);
	figuras->adiciona(p);
}

void Mundo::adicionaReta(string nome, ListaEnc<Coordenada>& coord) {
	Reta* r = new Reta(nome, coord);
	figuras->adiciona(r);
}

void Mundo::adicionaPoligono(string nome, ListaEnc<Coordenada>& coord) {
	Poligono* p = new Poligono(nome, coord);
	figuras->adiciona(p);
}

void Mundo::maisZoom(double passo) {
	double dx = 1 + (passo / 100);
	double dy = 1 + (passo / 100);
	zoom = zoom * Coordenada(dx, dy);
}

void Mundo::menosZoom(double passo) {
	double dx = 1 + (passo / 100);
	double dy = 1 + (passo / 100);
	zoom = zoom * Coordenada(1 / dx, 1 / dy);
}

void Mundo::transladaFigura(int posicaoLista, Coordenada desloc) {
	Figura* f = figuras->retornaDado(posicaoLista);
	f->translada(desloc);

}

void Mundo::escalonaFigura(int posicaoLista, Coordenada escala) {
	Figura* f = figuras->retornaDado(posicaoLista);
	f->escalona(escala);
}

void Mundo::rotacionaFiguraCentroTela(int posicaoLista, double anguloGraus) {
	rotacionaFigura(posicaoLista, centroDesenho, anguloGraus);
}

void Mundo::rotacionaFiguraProprioCentro(int posicaoLista, double anguloGraus) {
	Figura *f = figuras->retornaDado(posicaoLista);
	f->rotacionaFiguraProprioCentro(anguloGraus);
}

Mundo::~Mundo() {
	delete figuras;
}

ListaEnc<Figura*>* Mundo::getFiguras() {
	return figuras;
}

void Mundo::rotacionaFigura(int posicaoLista, Coordenada centroRotacao,
		double anguloGraus) {
	Figura* f = figuras->retornaDado(posicaoLista);
	f->rotaciona(centroRotacao, anguloGraus);
}
