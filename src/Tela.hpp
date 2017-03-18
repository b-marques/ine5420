/*
 * Tela.h
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#ifndef TELA_HPP_
#define TELA_HPP_
#include <gtk/gtk.h>
#include <glib.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Mundo.hpp"
#include "tipofiguraenum.hpp"

class Tela {
private:
	Mundo *mundo;
	cairo_surface_t* surface;
	GtkWidget *drawArea;
	ListaEnc<Coordenada> coordTemp;
	GtkBuilder *gtkBuilder;
	GtkWidget* adicionarWindow;
	void redesenhaTudo();
	void limpaListaCoord();
	void moveCima();
	void moveBaixo();
	void moveDireita();
	void moveEsquerda();
	void redesenhaFigura(Figura *f);
	double getPasso();
	void transViewPort(Coordenada& coord);
	void limpaDesenho();
	string coordenadasTxt(const ListaEnc<Coordenada>& coords);
	Coordenada corrigeCoord(Coordenada coord);
public:
	void escreveTerminal(string texto);
	Tela();
	void abrePopup();
	void adicionaFigura(string nome, TipoFigura tipo);
	void desenhaPonto(ListaEnc<Coordenada>& coord);
	void desenhaFiguraMultiplasCoordenadas(ListaEnc<Coordenada>& coord);
	void focaDrawArea();
	void maisZoom();
	void menosZoom();
	void move(GdkEvent *event);
	gboolean redraw(GtkWidget *widget, cairo_t *cr);
	gboolean criaSurface(GtkWidget *widget);
	void setCoordTemp(ListaEnc<Coordenada>& coordTemp); //TEMPORARIO
	ListaEnc<Coordenada> getCoordTemp();
	void abrirTelaAdicionar();
	virtual ~Tela();
	void adicionar(GtkWidget *widget);
	void addCord();
};

#endif /* TELA_HPP_ */