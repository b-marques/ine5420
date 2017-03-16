/*
 * Tela.h
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#ifndef TELA_H_
#define TELA_H_
#include "Mundo.h"
#include <gtk/gtk.h>
#include <glib.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <cairo.h>
#include <gdk/gdkcairo.h>
#include "tipofiguraenum.hpp"

class Tela {
private:
	Mundo mundo;
	cairo_surface_t* superficieDraw;
	GtkWidget *drawArea;
	ListaEnc<Coordenada> coordTemp;

	void limpaListaCoord();
	void moveCima();
	void moveBaixo();
	void moveDireita();
	void moveEsquerda();
	void redesenhaTudo();
	void redesenhaFigura(Figura *f, Coordenada deslocamento);
	void limpaDesenho();
	Coordenada cordenadaModulo();
public:
	Tela();
	void abrePopup();
	void adicionaFigura(string nome, TipoFigura tipo);
	void desenhaPonto(ListaEnc<Coordenada> coord, Coordenada deslocamento);
	void desenhaFiguraMultiplasCoordenadas(ListaEnc<Coordenada> coord, Coordenada deslocamento);
	void focaDrawArea();
	void maisZoom();
	void menosZoom();
	void move(GdkEvent *event);
	virtual ~Tela();
};

#endif /* TELA_H_ */
