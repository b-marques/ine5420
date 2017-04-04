#include <list>
#include <gtk/gtk.h>
#include <glib.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <math.h>

#include "../src/Mundo.hpp"
#include "../src/Reta.hpp"
#include "../src/Tela.hpp"
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

void adicionarPonto(GtkWidget *button, gpointer user_data){
	tela->adicionarPonto();
}

void adicionarReta(GtkWidget *button, gpointer user_data){
	tela->adicionarReta();
}

void adicionarPoligono(GtkWidget *button, gpointer user_data){
	tela->adicionarPoligono();
}

void abrirAdicionaFigura(GtkWidget *button, gpointer user_data){
	tela->abrirTelaAdicionar();
}

void escalonar(GtkWidget *button, gpointer user_data){
	tela->escalonaFigura();
}

void transladar(GtkWidget *button, gpointer user_data){
	tela->transladaFigura();
}

void rotacionar(GtkWidget *button, gpointer user_data){
	tela->rotacionaFigura();
}

void abrirArquivoMundo(GtkWidget *button, gpointer user_data){
	tela->abreMundo();
}

void salvarArquivoMundo(GtkWidget *button, gpointer user_data){
	tela->salvaMundo();
}

void giraHora(GtkWidget *button, gpointer user_data){
	tela->giraTelaHora();
}

void giraAntiHora(GtkWidget *button, gpointer user_data){
	tela->giraTelaAntiHora();
}
}

int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);
	tela = new Tela();
	gtk_main();
	return 0;
}
