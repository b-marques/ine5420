#include <iostream>
#include <gtk/gtk.h>
#include <glib.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <math.h>

#include "SuperficieBezier.hpp"
#include "Tela.hpp"
using namespace std;

Tela* tela;

extern "C" {

gboolean configura(GtkWidget *widget, GdkEventConfigure *event, gpointer data) {
	return tela->criaSurface(widget);
}

gboolean redraw(GtkWidget *widget, cairo_t *cr, gpointer data) {
	return tela->redraw(widget, cr);
}

void focaDrawArea(GtkWidget *button, gpointer user_data) {
	tela->focaDrawArea();
}

void maisZoom(GtkWidget *button, gpointer user_data) {
	tela->maisZoom();
}

void menosZoom(GtkWidget *button, gpointer user_data) {
	tela->menosZoom();
}

void move(GtkWidget *widget, GdkEvent *event, gpointer user_data) {
	tela->move(event);
}

void addCord(GtkWidget *button, gpointer user_data) {
	tela->addCord();
}

void clearCord(GtkWidget *button, gpointer user_data) {
	tela->limpaListaCoord();
}

void limparListaFace(GtkWidget *button, gpointer user_data) {
	tela->limpaListaCoord();
}
void adicionarPonto(GtkWidget *button, gpointer user_data) {
	tela->adicionarPonto();
}

void adicionarReta(GtkWidget *button, gpointer user_data) {
	tela->adicionarReta();
}

void adicionarPoligono(GtkWidget *button, gpointer user_data) {
	tela->adicionarPoligono();
}

void adicionarBezier(GtkWidget *button, gpointer user_data) {
	tela->adicionarBezier();
}

void adicionarBspline(GtkWidget *button, gpointer user_data) {
	tela->adicionarBspline();
}

void adicionarObjeto3d(GtkWidget *button, gpointer user_data) {
	tela->adicionarObjeto3d();
}

void adicionarFace(GtkWidget *button, gpointer user_data) {
	tela->addFace();
}

void abrirAdicionaFigura(GtkWidget *button, gpointer user_data) {
	tela->abrirTelaAdicionar();
}

void escalonar(GtkWidget *button, gpointer user_data) {
	tela->escalonaFigura();
}

void transladar(GtkWidget *button, gpointer user_data) {
	tela->transladaFigura();
}

void rotacionar(GtkWidget *button, gpointer user_data) {
	tela->rotacionaFigura();
}

void abrirArquivoMundo(GtkWidget *button, gpointer user_data) {
	tela->abreMundo();
}

void salvarArquivoMundo(GtkWidget *button, gpointer user_data) {
	tela->salvaMundo();
}

void giraHora(GtkWidget *button, gpointer user_data) {
	tela->giraTelaHora();
}

void giraAntiHora(GtkWidget *button, gpointer user_data) {
	tela->giraTelaAntiHora();
}

void resizeDraw(GtkWidget *widget, GdkRectangle *allocation,
		gpointer user_data) {
	tela->tamanhoDrawMudou(allocation);
}

void projOrtogonal(GtkToggleButton *togglebutton, gpointer user_data){
	tela->ativaProjOrtogonal();
}

void projPerspectiva(GtkToggleButton *togglebutton, gpointer user_data){
	tela->ativaProjPerspectiva();
}

void adicionarSuperBezier(GtkWidget *button, gpointer user_data){
	tela->adicionarSuperBezier();
}

void adicionarSuperBspline(GtkWidget *button, gpointer user_data){
	tela->adicionarSuperBspline();
}
}

int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);
	tela = new Tela();
	gtk_main();
	ListaEnc<Coordenada> c;

	c.adiciona(Coordenada(0, 0, 0));
	c.adiciona(Coordenada(5, 0, 0));
	c.adiciona(Coordenada(10, 0, 0));
	c.adiciona(Coordenada(15, 0, 0));

	c.adiciona(Coordenada(0, 5, 0));
	c.adiciona(Coordenada(5, 5, 20));
	c.adiciona(Coordenada(10, 5, 30));
	c.adiciona(Coordenada(15, 5, 0));

	c.adiciona(Coordenada(0, 10, 0));
	c.adiciona(Coordenada(5, 10, 20));
	c.adiciona(Coordenada(10, 10, 30));
	c.adiciona(Coordenada(15, 10, 0));

	c.adiciona(Coordenada(0, 15, 0));
	c.adiciona(Coordenada(5, 15, 0));
	c.adiciona(Coordenada(10, 15, 0));
	c.adiciona(Coordenada(15, 15, 0));

	SuperficieBezier* n = new SuperficieBezier("Superficie", c);


}
