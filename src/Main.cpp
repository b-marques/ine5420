#include <list>
#include <gtk/gtk.h>
#include <glib.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <cairo.h>
#include <gdk/gdkcairo.h>
#include "Mundo.hpp"
#include "Tela.h"
#include "Reta.h"
using namespace std;

Tela* tela;

/*coisas a fazer:
NOME OBJETO ADICIONADO NA TREE VIEW
janela para adicionar figuras
metodos janela de adicao
*/

extern "C"{

gboolean configura(GtkWidget *widget, GdkEventConfigure *event,
		gpointer data) {
	return tela->criaSurface(widget);
}

gboolean redraw(GtkWidget *widget, cairo_t *cr, gpointer data) {
	return tela->redraw(widget, cr);
}

void focaDrawArea(GtkWidget *button, gpointer user_data) {
	tela->focaDrawArea();
}

void maisZoom(GtkWidget *button, gpointer user_data){
	tela->maisZoom();
}

void menosZoom(GtkWidget *button, gpointer user_data){
	tela->menosZoom();
}

void move(GtkWidget *widget, GdkEvent *event,
		gpointer user_data){
	tela->move(event);
}

void adicionaFigura(GtkWidget *button, gpointer user_data){
	//tela->abrePopup();
	ListaEnc<Coordenada> cords;
	cords.adiciona(Coordenada(0, 0));
	cords.adiciona(Coordenada(300, 250));
	cords.adiciona(Coordenada(300, 0));
	tela->setCoordTemp(cords);
	tela->adicionaFigura("TRIANGULO", POLIGONO);
	cords.destroiLista();
	cords.adiciona(Coordenada(500, 275));
	tela->setCoordTemp(cords);
	tela->adicionaFigura("PONTO", PONTO);

}

}


int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);
	tela = new Tela();
	gtk_main();
	return 0;
}
