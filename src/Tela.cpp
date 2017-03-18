/*
 * Tela.cpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#include "Tela.h"
Tela::Tela() {
	GtkWidget *window_widget;
	gtkBuilder = gtk_builder_new();

	gtk_builder_add_from_file (gtkBuilder, "window.glade", NULL);
	window_widget = GTK_WIDGET(
			gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "main_window"));
	drawArea = GTK_WIDGET(
			gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "drawing_area"));
	surface = NULL;
	mundo = new Mundo(gtk_widget_get_allocated_width(drawArea),
			gtk_widget_get_allocated_height(drawArea));

	g_signal_connect_swapped(G_OBJECT(window_widget), "destroy",
                             G_CALLBACK(gtk_main_quit), NULL);
	gtk_builder_connect_signals(gtkBuilder, NULL);
	gtk_widget_show_all(window_widget);


}

void Tela::desenhaPonto(ListaEnc<Coordenada>& coordLista) {
	cairo_t* cr = cairo_create(surface);
	Coordenada coord = (coordLista.retiraDoInicio() + mundo->getDeslocamento());
	transViewPort(coord);
	cairo_move_to(cr, coord.getX(), coord.getY());
	cairo_arc(cr, coord.getX(), coord.getY(), 1.0, 0.0, 2.0 * M_PI);
	cairo_fill_preserve(cr);
}

void Tela::desenhaFiguraMultiplasCoordenadas(ListaEnc<Coordenada>& coordLista) {
	cairo_t* cr = cairo_create(surface);
	Coordenada coord1, coord2, deslocamento = mundo->getDeslocamento(), zoom =
			mundo->getZoom();
	coord1 = (coordLista.retornaDado(0) + deslocamento) * zoom;
	transViewPort(coord1);
	cairo_set_line_width(cr, 0.5);
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_move_to(cr, coord1.getX(), coord1.getY());
	for (int ponto = 1; ponto < coordLista.tamanho(); ponto++) {
		coord2 = (coordLista.retornaDado(ponto) + deslocamento) * zoom;
		transViewPort(coord2);
		cairo_line_to(cr, coord2.getX(), coord2.getY());
		cairo_move_to(cr, coord2.getX(), coord2.getY());
	}
	if (coordLista.tamanho() > 2)
		cairo_line_to(cr, coord1.getX(), coord1.getY());
	cairo_stroke(cr);
	gtk_widget_queue_draw(drawArea);
}

void Tela::adicionaFigura(string nome, TipoFigura tipo) {
	switch (tipo) {
	case PONTO:
		mundo->adicionaPonto(nome, coordTemp);
		desenhaPonto(coordTemp);
		break;
	case RETA:
		mundo->adicionaReta(nome, coordTemp);
		desenhaFiguraMultiplasCoordenadas(coordTemp);
		break;
	case POLIGONO:
		mundo->adicionaPoligono(nome, coordTemp);
		desenhaFiguraMultiplasCoordenadas(coordTemp);
		break;
	default:
		break;
	}
	escreveTerminal("Figura adicionada: " + nome + coordenadasTxt(coordTemp));
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
	mundo->desloca(passo, CIMA);
	redesenhaTudo();
}

void Tela::moveBaixo() {
	double passo = getPasso();
	mundo->desloca(passo, BAIXO);
	redesenhaTudo();
}

void Tela::moveDireita() {
	double passo = getPasso();
	mundo->desloca(passo, DIREITA);
	redesenhaTudo();
}

void Tela::moveEsquerda() {
	double passo = getPasso();
	mundo->desloca(passo, ESQUERDA);
	redesenhaTudo();
}

void Tela::maisZoom() {
	double passo = getPasso();
	mundo->maisZoom(passo);
	redesenhaTudo();
	escreveTerminal("Zoom in");
}

void Tela::menosZoom() {
	double passo = getPasso();
	mundo->menosZoom(passo);
	redesenhaTudo();
	escreveTerminal("Zoom out");
}

void Tela::transViewPort(Coordenada& coord) {
	double alturaDraw = gtk_widget_get_allocated_height(drawArea);
	coord.setY(-coord.getY() + alturaDraw);
}

void Tela::setCoordTemp(ListaEnc<Coordenada>& coord) {
	coordTemp = coord;
}

ListaEnc<Coordenada> Tela::getCoordTemp() {
	return coordTemp;
}

void Tela::escreveTerminal(string texto) {
	GtkTextView *terminal = GTK_TEXT_VIEW(
			gtk_builder_get_object(gtkBuilder, "terminal"));
	texto = texto + "\n";
	GtkTextBuffer *textoBuf = gtk_text_view_get_buffer(terminal);
	gtk_text_buffer_insert_at_cursor(textoBuf, texto.c_str(), texto.length());
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
	focaDrawArea();
}

void Tela::redesenhaTudo() {
	ListaEnc<Figura*>* figLista = mundo->getFiguras();
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

gboolean Tela::redraw(GtkWidget* widget, cairo_t* cr) {
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

string Tela::coordenadasTxt(const ListaEnc<Coordenada>& coords) {
	string texto = "\n";
	Coordenada coordAux;
	for (int i = 0; i < coords.tamanho(); ++i) {
		coordAux = coords.retornaDado(i);
		texto = texto + "( " + to_string(coordAux.getX()) + ", "
				+ to_string(coordAux.getY()) + ")\n";
	}
	return texto;
}

void Tela::abrirTelaAdicionar() {
	GtkWindow *adicionarWindow = GTK_WINDOW(gtk_builder_get_object(gtkBuilder, "add_object_window"));
	g_signal_connect (GTK_WIDGET(adicionarWindow), "delete_event", G_CALLBACK (gtk_widget_hide_on_delete), NULL);
	gtk_window_present(adicionarWindow);
}
