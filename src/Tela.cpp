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
	gtkBuilder = gtk_builder_new();
	gtk_builder_add_from_file(gtkBuilder, "window.glade", NULL);
	window_widget = GTK_WIDGET(
			gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "main_window"));
	drawArea = GTK_WIDGET(
			gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "drawing_area"));
	surface = NULL;
	gtk_builder_connect_signals(gtkBuilder, NULL);
	gtk_widget_show_all(window_widget);
}

void Tela::desenhaPonto(ListaEnc<Coordenada>& coordLista) {
	cairo_t* cr = cairo_create(surface);
	Coordenada coord = (coordLista.retiraDoInicio() + mundo.getDeslocamento());
	transViewPort(coord);
	cairo_move_to(cr, coord.getX(), coord.getY());
	cairo_arc(cr, coord.getX(), coord.getY(), 1.0, 0.0, 2.0 * M_PI);
	cairo_fill_preserve(cr);
}

void Tela::desenhaFiguraMultiplasCoordenadas(ListaEnc<Coordenada>& coordLista) {
	cairo_t* cr = cairo_create(surface);
	Coordenada coord1, coord2, deslocamento = mundo.getDeslocamento(), zoom =
			mundo.getZoom();
	coord1 = (coordLista.retornaDado(0) + deslocamento) * zoom;
	transViewPort(coord1);
	cairo_set_line_width(cr, 0.5);
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_move_to(cr, coord1.getX(), coord1.getY());
	for (int ponto = 1; ponto < coordLista.tamanho(); ponto++) {
		coord2 = (coordLista.retornaDado(ponto) + deslocamento)
				* zoom;
		transViewPort(coord2);
		cairo_line_to(cr, coord2.getX(), coord2.getY());
		cairo_stroke(cr);
		cairo_move_to(cr, coord2.getX(), coord2.getY());
	}
	cairo_close_path(cr);
	gtk_widget_queue_draw(drawArea);
}

void Tela::adicionaFigura(string nome, TipoFigura tipo) {
	switch (tipo) {
	case PONTO:
		mundo.adicionaPonto(nome, coordTemp);
		desenhaPonto(coordTemp);
		break;
	case RETA:
		mundo.adicionaReta(nome, coordTemp);
		desenhaFiguraMultiplasCoordenadas(coordTemp);
		break;
	case POLIGONO:
		mundo.adicionaPonto(nome, coordTemp);
		desenhaFiguraMultiplasCoordenadas(coordTemp);
		break;
	default:
		break;
	}
	limpaListaCoord();
}

void Tela::limpaListaCoord() {
	ListaEnc<Coordenada> novaLista;
	coordTemp = novaLista;
}

void Tela::limpaDesenho() {
	cairo_t *cr = cairo_create(surface);
	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_paint(cr);
	cairo_destroy(cr);
}

double Tela::getPasso() {
	double passo;
	GtkEntry* caixaTxt = GTK_ENTRY(
			gtk_builder_get_object(gtkBuilder, "entryPasso"));
	passo = atof(gtk_entry_get_text(caixaTxt));
	return passo;
}

void Tela::moveCima() {
	double passo = getPasso();
	double larguraDraw = gtk_widget_get_allocated_width(drawArea);
	double alturaDraw = gtk_widget_get_allocated_height(drawArea);
	mundo.desloca(passo, larguraDraw, alturaDraw, CIMA);
	redesenhaTudo();
}

void Tela::moveBaixo() {
	double passo = getPasso();
	double larguraDraw = gtk_widget_get_allocated_width(drawArea);
	double alturaDraw = gtk_widget_get_allocated_height(drawArea);
	mundo.desloca(passo, larguraDraw, alturaDraw, BAIXO);
	redesenhaTudo();
}

void Tela::moveDireita() {
	double passo = getPasso();
	double larguraDraw = gtk_widget_get_allocated_width(drawArea);
	double alturaDraw = gtk_widget_get_allocated_height(drawArea);
	mundo.desloca(passo, larguraDraw, alturaDraw, DIREITA);
	redesenhaTudo();
}

void Tela::moveEsquerda() {
	double passo = getPasso();
	double larguraDraw = gtk_widget_get_allocated_width(drawArea);
	double alturaDraw = gtk_widget_get_allocated_height(drawArea);
	mundo.desloca(passo, larguraDraw, alturaDraw, ESQUERDA);
	redesenhaTudo();
}

void Tela::maisZoom() {
	double passo = getPasso();
	mundo.maisZoom(passo);
	redesenhaTudo();
}

void Tela::menosZoom() {
	double passo = getPasso();
	mundo.menosZoom(passo);
	redesenhaTudo();
}

void Tela::transViewPort(Coordenada& coord) {
	double alturaDraw = gtk_widget_get_allocated_height(drawArea);
	coord.setY(-coord.getY() + alturaDraw);
}

void Tela::setCoordTemp(ListaEnc<Coordenada>& coord) {
	coordTemp = coord;
}

Tela::~Tela() {
}

void Tela::focaDrawArea() {
	gtk_widget_grab_focus(drawArea);
}

void Tela::move(GdkEvent* event) {
	switch (event->key.keyval) {
	case GDK_KEY_Up:
		moveCima();
		break;
	case GDK_KEY_Down:
		moveBaixo();
		break;
	case GDK_KEY_Right:
		moveDireita();
		break;
	case GDK_KEY_Left:
		moveEsquerda();
		break;
	default:
		break;
	}
}

void Tela::redesenhaTudo() {
	ListaEnc<Figura*>* figLista = mundo.getFiguras();
	limpaDesenho();
	for (int i = 0; i < figLista->tamanho(); i++) {
		redesenhaFigura(figLista->retornaDado(i));
	}
}

void Tela::redesenhaFigura(Figura* f) {
	ListaEnc<Coordenada> coordsFig;
	coordsFig = f->getCoord();
	if (coordsFig.tamanho() > 1)
		desenhaFiguraMultiplasCoordenadas(coordsFig);
	else
		desenhaPonto(coordsFig);
}

gboolean Tela::reconfigura(GtkWidget* widget, cairo_t* cr) {
	cairo_set_source_surface(cr, surface, 0, 0);
	cairo_paint(cr);
	return FALSE;
}

gboolean Tela::criaSurface(GtkWidget *widget) {
	if (surface)
		cairo_surface_destroy(surface);

	surface = gdk_window_create_similar_surface(gtk_widget_get_window(widget),
			CAIRO_CONTENT_COLOR, gtk_widget_get_allocated_width(widget),
			gtk_widget_get_allocated_height(widget));
	limpaDesenho();
	return TRUE;
}

