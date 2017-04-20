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
#include <string>

#include "DescritorObj.hpp"
#include "Mundo.hpp"
#include "Desenhador.hpp"

class Tela {
private:
	Mundo *mundo;
	GtkWidget *drawArea;
	Desenhador *desenhador;
	ListaEnc<Coordenada> coordTemp;
	GtkBuilder *gtkBuilder;
	GtkWidget* adicionarWindow;
	DescritorObj* descritor;

	void redesenhaTudo();
	void moveCima();
	void moveBaixo();
	void moveDireita();
	void moveEsquerda();
	void redesenhaFigura(Figura *f);
	string getEntryText(string nomeEntry);
	double getPasso();
	string getNomeFigAdd();
	void escreveListaObjetos(string nome);
	int posicaoFigSelecionada();
	string coordenadasTxt(const ListaEnc<Coordenada>& coords);
	Coordenada FatorOuDeslocamento();
	int tipoRotacao();
	double getSpinButtonValue(string nomeBotao);
	void limpaListaObjetos();
	int tipoClipping();
	void redesenhaFiguraClip(Figura* f, int tipoClip, int xDirVP,
			int yCimaVP);
public:
	void escreveTerminal(string texto);
	Tela();
	void adicionaFigura(string nome, TipoFigura tipo);
	void focaDrawArea();
	void maisZoom();
	void menosZoom();
	void move(GdkEvent *event);
	void limpaListaCoord();
	gboolean redraw(GtkWidget *widget, cairo_t *cr);
	gboolean criaSurface(GtkWidget *widget);
	void setCoordTemp(ListaEnc<Coordenada>& coordTemp);
	ListaEnc<Coordenada> getCoordTemp();
	void abrirTelaAdicionar();
	virtual ~Tela();
	void adicionarPonto();
	void adicionarReta();
	void adicionarPoligono();
	void adicionarBezier();
	void adicionarBspline();
	void addCord();
	void clearCord();
	void escalonaFigura();
	void transladaFigura();
	void rotacionaFigura();
	void salvaMundo();
	void abreMundo();
	void giraTelaHora();
	void giraTelaAntiHora();
	void tamanhoDrawMudou(GdkRectangle *novoTam);
};

#endif /* TELA_HPP_ */
