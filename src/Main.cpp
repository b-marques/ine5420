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
	GtkBuilder* gtkBuilder = gtk_builder_new();
	ListaEnc<Coordenada> cords = tela->getCoordTemp();
	GtkWidget *coord_x = GTK_WIDGET(gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "coord_x_polig"));
	GtkWidget *coord_y = GTK_WIDGET(gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "coord_y_polig"));
	int x = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(coord_x));
	int y = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(coord_y));
	cords.adiciona(Coordenada(x,y));
	tela->setCoordTemp(cords);
}

void adicionaFigura(GtkWidget *button, gpointer user_data){
	const gchar* buttonNameTemp = gtk_button_get_label(GTK_BUTTON(button));
	std::string buttonName = std::string(buttonNameTemp);
	GtkBuilder* gtkBuilder = gtk_builder_new();
	ListaEnc<Coordenada> cords;


	if (!buttonName.compare("Adicionar Ponto")) {
		cout << buttonName << endl;
		GtkWidget *coord_x = GTK_WIDGET(gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "coord_x_point"));
		GtkWidget *coord_y = GTK_WIDGET(gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "coord_y_point"));
		double x = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(coord_x));
		double y = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(coord_y));
		cords.adiciona(Coordenada(x,y));
		tela->setCoordTemp(cords);
		tela->adicionaFigura("PONTO", PONTO);
		

	} else if (!buttonName.compare("Adicionar Reta")) {
		cout << buttonName << endl;
		GtkWidget *coord_x1 = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "coord_x_line1"));
		GtkWidget *coord_y1 = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "coord_y_line1"));
		GtkWidget *coord_x2 = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "coord_x_line2"));
		GtkWidget *coord_y2 = GTK_WIDGET(gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "coord_y_line2"));
		int x1 = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(coord_x1));
		int y1 = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(coord_y1));
		int x2 = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(coord_x2));
		int y2 = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(coord_y2));
		cords.adiciona(Coordenada(x1,y1));
		cords.adiciona(Coordenada(x2,y2));
		tela->setCoordTemp(cords);
		tela->adicionaFigura("RETA", RETA);

	} else if (!buttonName.compare("Adicionar Poligono")) {
		cout << buttonName << endl;
		tela->adicionaFigura("POLIGONO", POLIGONO);
	}
	
	// cords.adiciona(Coordenada(0, 0));
	// cords.adiciona(Coordenada(300, 250));
	// cords.adiciona(Coordenada(300, 0));
	// tela->setCoordTemp(cords);
	// tela->adicionaFigura("TRIANGULO", POLIGONO);

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
