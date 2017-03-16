#include <gtk/gtk.h>
#include <glib.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <cairo.h>
#include <gdk/gdkcairo.h>
#include "Mundo.h"
#include "Tela.h"
using namespace std;

Tela* tela;
/*coisas a fazer:
metodos de zoom
metodos janela de adicao
*/

extern "C"{

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
	tela->abrePopup();
}

}

int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);
	tela = new Tela();
	return 0;
}
