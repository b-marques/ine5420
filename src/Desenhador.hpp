/*
 * Desenhador.hpp
 *
 *  Created on: 11 de abr de 2017
 *      Author: johann
 */

#ifndef DESENHADOR_HPP_
#define DESENHADOR_HPP_
#include <gtk/gtk.h>
#include <glib.h>
#include "Figura.hpp"

class Desenhador {
private:
	cairo_surface_t* surface;
	GtkWidget *drawArea;
public:
	Desenhador(GtkWidget *drawArea);
	gboolean criaSurface(GtkWidget *drawArea);
	gboolean redraw(cairo_t* cr);
	void desenhaPonto(ListaEnc<Coordenada>& coordLista);
	void desenhaViewPort();
	void desenhaPoligonoReta(ListaEnc<Coordenada>& coordLista);
	void limpaDesenho();
	Coordenada transViewPort(Coordenada coord);
	virtual ~Desenhador();
};

#endif /* DESENHADOR_HPP_ */
