#include <list>
#include <gtk/gtk.h>
#include <glib.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
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

void move(GtkWidget *widget, GdkEvent *event, gpointer user_data){
	tela->move(event);
}

void addCord(GtkWidget *button, gpointer user_data) {
	tela->addCord();
}

void adicionaFigura(GtkWidget *button, gpointer user_data){
	tela->adicionar(button);
}

void abrirAdicionaFigura(GtkWidget *button, gpointer user_data){
	tela->abrirTelaAdicionar();
}

}

int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);
	tela = new Tela();
	gtk_main();
	return 0;
}
