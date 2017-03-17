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
janela para adicionar figuras
metodos janela de adicao
metodo virtual com string da figura(reta, poligono, etc)
Adicionar texto ao terminal apos adicao
*/

extern "C"{

gboolean configura(GtkWidget *widget, GdkEventConfigure *event,
		gpointer data) {
	return tela->criaSurface(widget);
}

gboolean redraw(GtkWidget *widget, cairo_t *cr, gpointer data) {
	return tela->reconfigura(widget, cr);
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
	tela->escreveTerminal("OI");
}

}


int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);
	tela = new Tela();
	gtk_main();
	return 0;
}
