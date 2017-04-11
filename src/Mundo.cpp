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
	deslocamento = Coordenada(0, 0, 0);
	zoom = Coordenada(1, 1, 1);
	zoomAcumulado = Coordenada(1, 1, 1);
	centroDesenho = Coordenada(larguraArea / 2, alturaArea / 2, 0);
	figuras = new ListaEnc<Figura*>();
	centroMundo = Coordenada(0, 0, 0);
	giroTelaAcumulado = 0;
}

void Mundo::desloca(double passo, TipoMovimento sentido) {
	//Coordenada deltaDesloc;
	double dx = passo * larguraArea / 100;
	double dy = passo * alturaArea / 100;
	switch (sentido) {
	case CIMA:
		deslocamento = Coordenada(0, -dy);
		break;
	case BAIXO:
		deslocamento = Coordenada(0, +dy);
		break;
	case DIREITA:
		deslocamento = Coordenada(-dx, 0);
		break;
	case ESQUERDA:
		deslocamento = Coordenada(+dx, 0);
		break;
	default:
		break;
	}
	deslocaFiguras();
	//deslocamento = deslocamento + deltaDesloc;
	//centroDesenho = centroDesenho - deltaDesloc;
	//centroDesenho = centroDesenho - deslocamento;
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

Coordenada Mundo::getCentroMundo() {
	return centroMundo;
}

void Mundo::adicionaFigura(Figura* f) {
	figuras->adiciona(f);
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
	zoom.setX(dx);
	zoom.setY(dy);
	daZoomFiguras();
}

void Mundo::menosZoom(double passo) {
	double dx = 1 + (passo / 100);
	double dy = 1 + (passo / 100);
	zoom.setX(1/dx);
	zoom.setY(1/dy);
	daZoomFiguras();
}

void Mundo::transladaFigura(int posicaoLista, Coordenada desloc) {
	Figura* f = figuras->retornaDado(posicaoLista);
	f->translada(desloc, zoomAcumulado, giroTelaAcumulado);
}

void Mundo::escalonaFigura(int posicaoLista, Coordenada escala) {
	Figura* f = figuras->retornaDado(posicaoLista);
	f->escalona(escala);
}

void Mundo::rotacionaFiguraCentroMundo(int posicaoLista, double anguloGraus) {
	rotacionaFigura(posicaoLista, centroMundo, anguloGraus);
}

void Mundo::rotacionaFiguraProprioCentro(int posicaoLista, double anguloGraus) {
	Figura *f = figuras->retornaDado(posicaoLista);
	f->rotacionaFiguraProprioCentro(anguloGraus, zoomAcumulado, giroTelaAcumulado, centroDesenho);
}

void Mundo::rotacionaFigura(int posicaoLista, Coordenada centroRotacao,
		double anguloGraus) {
	Figura* f = figuras->retornaDado(posicaoLista);
	f->rotaciona(centroRotacao, anguloGraus, zoomAcumulado, giroTelaAcumulado, centroDesenho);
}

void Mundo::daZoomFiguras() {
	Figura* f;
	zoomAcumulado = zoom * zoomAcumulado;
	for (int i = 0; i < figuras->tamanho(); ++i) {
		f = figuras->retornaDado(i);
		f->daZoom(zoom, centroDesenho);
	}
}

void Mundo::deslocaFiguras() {
	Figura* f;
	for (int i = 0; i < figuras->tamanho(); ++i) {
		f = figuras->retornaDado(i);
		f->deslocaNaTela(deslocamento);
	}
}

Mundo::~Mundo() {
	delete figuras;
}

ListaEnc<Figura*>* Mundo::getFiguras() {
	return figuras;
}

void Mundo::giraTela(double angulo) {
	Figura* f;
	giroTelaAcumulado += angulo;
	for (int i = 0; i < figuras->tamanho(); ++i) {
		f = figuras->retornaDado(i);
		f->rotacionaTela(centroDesenho, angulo);
	}
}

void Mundo::mudaTamanhoDesenho(int largura, int altura) {
	this->larguraArea = largura;
	this->alturaArea = altura;
	centroDesenho = Coordenada (larguraArea/2, alturaArea/2, 0);
}
