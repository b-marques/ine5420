/*
 * Tela.cpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#include "Tela.h"
#include <math.h>
Tela::Tela() {
	GtkWidget *window_widget;
	GtkBuilder *gtkBuilder = gtk_builder_new();
	gtk_builder_add_from_file(gtkBuilder, "window.glade", NULL);
	window_widget = GTK_WIDGET(
			gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "main_window"));
	drawArea = GTK_WIDGET(
			gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "drawing_area"));
	superficieDraw = gdk_window_create_similar_surface(gtk_widget_get_window(drawArea),
			CAIRO_CONTENT_COLOR, gtk_widget_get_allocated_width(drawArea),
			gtk_widget_get_allocated_height(drawArea));
	gtk_builder_connect_signals(gtkBuilder, NULL);
	gtk_widget_show_all(window_widget);
	gtk_main();
}

void Tela::desenhaPonto(ListaEnc<Coordenada> coordLista, Coordenada deslocamento) {
	cairo_t* cr = cairo_create(superficieDraw);
	Coordenada coord = coordLista.retiraDoInicio() + deslocamento;
	cairo_move_to(cr, coord.getX(), coord.getY());
	cairo_arc(cr, coord.getX(), coord.getY(), 1.0, 0.0, 2.0 * M_PI);
	cairo_fill_preserve(cr);
}

void Tela::desenhaFiguraMultiplasCoordenadas(ListaEnc<Coordenada> coordLista, Coordenada deslocamento) {
	cairo_t* cr = cairo_create(superficieDraw);
	Coordenada coord1, coord2;
	coord1 = coordLista.retiraDoInicio() + deslocamento;
	cairo_set_line_width(cr, 0.5);
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_move_to(cr, coord1.getX(), coord1.getY());
	for (int ponto = 0; ponto < coordLista.tamanho() - 1; ponto++) {
		coord2 = coordLista.retiraDoInicio() + deslocamento;
		cairo_line_to(cr, coord2.getX(), coord2.getY());
		cairo_move_to(cr, coord2.getX(), coord2.getY());
		cairo_stroke(cr);
	}
	cairo_close_path(cr);
	gtk_widget_queue_draw(drawArea);
}

void Tela::adicionaFigura(string nome, TipoFigura tipo) {
	Coordenada desNulo;
	switch (tipo) {
		case PONTO:
			mundo.adicionaPonto(nome, coordTemp);
			desenhaPonto(coordTemp, desNulo);
			break;
		case RETA:
			mundo.adicionaReta(nome, coordTemp);
			desenhaFiguraMultiplasCoordenadas(coordTemp, desNulo);
			break;
		case POLIGONO:
			mundo.adicionaPonto(nome, coordTemp);
			desenhaFiguraMultiplasCoordenadas(coordTemp, desNulo);
			break;
		default:
			break;
	}
	limpaListaCoord();
}

void Tela::limpaListaCoord() {
	coordTemp = ListaEnc<Coordenada>();
}

void Tela::limpaDesenho() {
	cairo_t *cr = cairo_create(superficieDraw);
	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_paint(cr);
	cairo_destroy(cr);
}

Coordenada Tela::cordenadaModulo() {
	double dx, dy, passo;
	GtkEntry* caixaTxt = GTK_ENTRY(gtk_builder_get_object(gtk_builder_new(),"window.glade"));
	passo = atof(gtk_entry_get_text(caixaTxt));
	dx = passo * gtk_widget_get_allocated_width(drawArea) / 100;
	dy = passo * gtk_widget_get_allocated_height(drawArea) / 100;
	return Coordenada(dx, dy);
}

void Tela::moveCima() {
	Coordenada deslocamento = cordenadaModulo();
	deslocamento.setX(0);
	deslocamento.setY(deslocamento.getY());
	mundo.desloca(deslocamento);
	redesenhaTudo();
}

void Tela::moveBaixo() {
	Coordenada deslocamento = cordenadaModulo();
	deslocamento.setX(0);
	deslocamento.setY(-deslocamento.getY());
	mundo.desloca(deslocamento);
	redesenhaTudo();
}

void Tela::moveDireita() {
	Coordenada deslocamento = cordenadaModulo();
	deslocamento.setX(-deslocamento.getX());
	deslocamento.setY(0);
	mundo.desloca(deslocamento);
	redesenhaTudo();
}

void Tela::moveEsquerda() {
	Coordenada deslocamento = cordenadaModulo();
	deslocamento.setX(deslocamento.getX());
	deslocamento.setY(0);
	mundo.desloca(deslocamento);
	redesenhaTudo();
}

Tela::~Tela() {
}


void Tela::focaDrawArea() {
	gtk_widget_grab_focus(drawArea);
}

void Tela::move(GdkEvent* event) {
	switch (event->key.keyval) {
		case GDK_KEY_uparrow:
			moveCima();
			break;
		case GDK_KEY_downarrow:
			moveBaixo();
			break;
		case GDK_KEY_rightarrow:
			moveDireita();
			break;
		case GDK_KEY_leftarrow:
			moveEsquerda();
			break;
		default:
			break;
	}
}

void Tela::redesenhaTudo() {
	ListaEnc<Figura*> figLista = mundo.getFiguras();
	Coordenada deslocamento = mundo.getDeslocamento();
	limpaDesenho();
	for (int i = 0; i < figLista.tamanho(); i++) {
		redesenhaFigura(figLista.retornaDado(i), deslocamento);
	}
	gtk_widget_queue_draw(drawArea);

}

void Tela::redesenhaFigura(Figura* f, Coordenada deslocamento) {
	if(f->getCoord().tamanho() > 1)
		desenhaFiguraMultiplasCoordenadas(f->getCoord(), deslocamento);
	else
		desenhaPonto(f->getCoord(), deslocamento);
}
