/*
 * Desenhador.cpp
 *
 *  Created on: 11 de abr de 2017
 *      Author: johann
 */

#include "Desenhador.hpp"
#include <math.h>
#include "ViewPortOffset.hpp"

Desenhador::Desenhador(GtkWidget *drawArea) {
	this->drawArea = drawArea;
	surface = NULL;
}

gboolean Desenhador::criaSurface(GtkWidget* widget) {
	if (surface)
		cairo_surface_destroy(surface);

	surface = gdk_window_create_similar_surface(gtk_widget_get_window(widget),
			CAIRO_CONTENT_COLOR, gtk_widget_get_allocated_width(widget),
			gtk_widget_get_allocated_height(widget));
	limpaDesenho();
	return TRUE;
}

gboolean Desenhador::redraw(cairo_t* cr) {
	cairo_set_source_surface(cr, surface, 0, 0);
	cairo_paint(cr);
	return FALSE;
}

void Desenhador::desenhaPonto(ListaEnc<Coordenada>& coordLista) {
	cairo_t* cr = cairo_create(surface);
	Coordenada coord = transViewPort(coordLista.retornaDado(0));
	cairo_move_to(cr, coord.getX(), coord.getY());
	cairo_arc(cr, coord.getX(), coord.getY(), 4.0, 0.0, 2.0 * M_PI);
	cairo_fill_preserve(cr);
	gtk_widget_queue_draw(drawArea);
}

void Desenhador::desenhaViewPort() {
	ListaEnc<Coordenada> coordsView;
	double height = gtk_widget_get_allocated_height(GTK_WIDGET(drawArea));
	double width = gtk_widget_get_allocated_width(GTK_WIDGET(drawArea));
	coordsView.adiciona(Coordenada(VPOffset, VPOffset));
	coordsView.adiciona(Coordenada(width - VPOffset, VPOffset));
	coordsView.adiciona(Coordenada(width - VPOffset, height - VPOffset));
	coordsView.adiciona(Coordenada(VPOffset, height - VPOffset));
	desenhaPoligonoRetaCurva(coordsView, true);
}

void Desenhador::desenhaPoligonoRetaCurva(ListaEnc<Coordenada>& coordLista, bool poligono) {
	cairo_t* cr = cairo_create(surface);
	Coordenada coord1, coord2;
	coord1 = transViewPort(coordLista.retornaDado(0));
	cairo_set_line_width(cr, 0.5);
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_move_to(cr, coord1.getX(), coord1.getY());
	for (int ponto = 1; ponto < coordLista.tamanho(); ponto++) {
		coord2 = transViewPort((coordLista.retornaDado(ponto)));
		cairo_line_to(cr, coord2.getX(), coord2.getY());
		cairo_move_to(cr, coord2.getX(), coord2.getY());
	}
	if (poligono)
		cairo_line_to(cr, coord1.getX(), coord1.getY());
	cairo_stroke(cr);
	gtk_widget_queue_draw(drawArea);
}

void Desenhador::limpaDesenho() {
	cairo_t *cr = cairo_create(surface);
	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_paint(cr);
	cairo_destroy(cr);
}

Coordenada Desenhador::transViewPort(Coordenada coord) {
	double alturaDraw = gtk_widget_get_allocated_height(drawArea);
	coord.setY(-coord.getY() + alturaDraw);
	return coord;
}

Desenhador::~Desenhador() {
	// TODO Auto-generated destructor stub
}

