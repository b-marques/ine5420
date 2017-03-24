/*
 * Tela.cpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#include "Tela.hpp"
Tela::Tela() {
	GtkWidget *window_widget;
	gtkBuilder = gtk_builder_new();

	gtk_builder_add_from_file(gtkBuilder, "window.glade", NULL);
	window_widget = GTK_WIDGET(
			gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "main_window"));
	drawArea = GTK_WIDGET(
			gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "drawing_area"));
	surface = NULL;
	mundo = new Mundo(gtk_widget_get_allocated_width(GTK_WIDGET(drawArea)),
			gtk_widget_get_allocated_height(drawArea));

	adicionarWindow = GTK_WIDGET(
			gtk_builder_get_object(gtkBuilder, "add_object_window"));
	g_signal_connect(GTK_WIDGET(adicionarWindow), "delete_event",
			G_CALLBACK (gtk_widget_hide), NULL);

	g_signal_connect_swapped(G_OBJECT(window_widget), "destroy",
			G_CALLBACK(gtk_main_quit), NULL);

	gtk_builder_connect_signals(gtkBuilder, NULL);

	gtk_widget_show_all(window_widget);

}

void Tela::desenhaPonto(ListaEnc<Coordenada>& coordLista) {
	cairo_t* cr = cairo_create(surface);
	Coordenada coord = corrigeCoord(coordLista.retornaDado(0));
	cairo_move_to(cr, coord.getX(), coord.getY());
	cairo_arc(cr, coord.getX(), coord.getY(), 4.0, 0.0, 2.0 * M_PI);
	cairo_fill_preserve(cr);
	gtk_widget_queue_draw(drawArea);
}

void Tela::desenhaFiguraMultiplasCoordenadas(ListaEnc<Coordenada>& coordLista) {
	cairo_t* cr = cairo_create(surface);
	Coordenada coord1, coord2;
	coord1 = corrigeCoord((coordLista.retornaDado(0)));
	cairo_set_line_width(cr, 0.5);
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_move_to(cr, coord1.getX(), coord1.getY());
	for (int ponto = 1; ponto < coordLista.tamanho(); ponto++) {
		coord2 = corrigeCoord((coordLista.retornaDado(ponto)));
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
	escreveListaObjetos(nome);
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
	gtk_text_view_set_monospace(terminal, TRUE);

	texto = texto + "\n";
	GtkTextBuffer *textoBuf = gtk_text_view_get_buffer(terminal);
	gtk_text_buffer_insert_at_cursor(textoBuf, texto.c_str(), texto.length());
}

Coordenada Tela::corrigeCoord(Coordenada coord) {
	Coordenada centroDesenho = mundo->getCentroDesenho();
	Coordenada zoom = mundo->getZoom();
	Coordenada variacao;
	variacao = (coord - centroDesenho) * zoom - (coord - centroDesenho);
	coord = coord + variacao;
	coord = coord + mundo->getDeslocamento();
	transViewPort(coord);
	return coord;
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
		texto = texto + coordAux.toString() + "\n";
	}
	return texto;
}

void Tela::abrirTelaAdicionar() {

	gtk_widget_show(adicionarWindow);
}

void Tela::adicionar(GtkWidget* button) {
	const gchar* buttonNameTemp = gtk_button_get_label(GTK_BUTTON(button));
	std::string buttonName = std::string(buttonNameTemp);
	string nomeFigura = getNomeFigAdd();
	ListaEnc<Coordenada> cords;

	if (!buttonName.compare("Adicionar Ponto")) {
		limpaListaCoord();
		double x = getSpinButtonValue("coord_x_point");
		double y = getSpinButtonValue("coord_y_point");
		cords.adiciona(Coordenada(x, y));
		setCoordTemp(cords);
		adicionaFigura(nomeFigura, PONTO);

	} else if (!buttonName.compare("Adicionar Reta")) {
		limpaListaCoord();
		double x1 = getSpinButtonValue("coord_x_line1");
		double y1 = getSpinButtonValue("coord_y_line1");
		double x2 = getSpinButtonValue("coord_x_line2");
		double y2 = getSpinButtonValue("coord_y_line2");
		cords.adiciona(Coordenada(x1, y1));
		cords.adiciona(Coordenada(x2, y2));
		setCoordTemp(cords);
		adicionaFigura(nomeFigura, RETA);

	} else if (!buttonName.compare("Adicionar Poligono")) {
		if (coordTemp.tamanho() < 3) {
			escreveTerminal(
					"Número de pontos insuficientes para criação de polígono!");
		} else {
			adicionaFigura(nomeFigura, POLIGONO);
		}
	}
}

string Tela::getNomeFigAdd() {
	GtkEntry* caixaTxt = GTK_ENTRY(
			gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "entryNome"));
	string nome = gtk_entry_get_text(caixaTxt);
	gtk_entry_set_text(caixaTxt, "");
	return nome;
}

int Tela::posicaoFigSelecionada() {
	GtkTreeSelection *selection = GTK_TREE_SELECTION(
			gtk_builder_get_object(gtkBuilder, "treeview-selection"));
	GtkTreeModel *model;
	GtkTreeIter iter;
	GtkTreePath *path;

	if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
		path = gtk_tree_model_get_path(model, &iter);
		return gtk_tree_path_get_indices(path)[0];
	}
	return -1;
}

void Tela::addCord() {
	double x = getSpinButtonValue("coord_x_polig");
	double y = getSpinButtonValue("coord_y_polig");
	coordTemp.adiciona(Coordenada(x, y));
}

void Tela::escreveListaObjetos(string nome) {
	GtkListStore* lista = GTK_LIST_STORE(
			gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "liststore2"));
	GtkTreeIter iterator;
	gtk_list_store_append(lista, &iterator);
	gtk_list_store_set(lista, &iterator, 0, nome.c_str(), -1);
}

void Tela::escalonaFigura() {
	int posFigura = posicaoFigSelecionada();
	if (posFigura > -1) {
		Coordenada coord = FatorOuDeslocamento();
		mundo->escalonaFigura(posFigura, coord);
		redesenhaTudo();
	} else {
		escreveTerminal("Selecione figura!");
	}
}


void Tela::trasladaFigura() {
	int posFigura = posicaoFigSelecionada();
	if (posFigura > -1) {
		Coordenada coord = FatorOuDeslocamento();
		mundo->transladaFigura(posFigura, coord);
		redesenhaTudo();
	} else {
		escreveTerminal("Selecione figura!");
	}
}

void Tela::transladaFiguraMatriz() {
	int posFigura = posicaoFigSelecionada();
	Coordenada deslocamento = FatorOuDeslocamento();
	Figura* f = mundo->getFiguras()->retornaDado(posFigura);
	Coordenada eixo = f->getCentro();

	if (posFigura > -1) {
		f->transform(eixo,  0,  1,  1,  deslocamento);
		redesenhaTudo();
	} else {
		escreveTerminal("Selecione figura!");
	}
}

void Tela::escalonaFiguraMatriz() {
	int posFigura = posicaoFigSelecionada();
	Coordenada escala = FatorOuDeslocamento();
	Figura* f = mundo->getFiguras()->retornaDado(posFigura);
	Coordenada eixo = f->getCentro();
	Coordenada naoDeslocar = Coordenada(0,0);

	if (posFigura > -1) {
		f->transform(eixo, 0, escala.getX(), escala.getY(), naoDeslocar);
		redesenhaTudo();
	} else {
		escreveTerminal("Selecione figura!");
	}
}

void Tela::rotacionaFiguraMatriz() {
	int posFigura = posicaoFigSelecionada();
	Figura* figura = mundo->getFiguras()->retornaDado(posFigura);
	Coordenada naoDeslocar = Coordenada(0,0);
	double angulo = getSpinButtonValue("angulo");
	string nome = figura->getNome();
	Coordenada eixo;	
	switch (tipoRotacao()) {
	case 0:
		// eixo = Coordenada (0,0);
		eixo = mundo->getCentroMundo();
		cout << "X = " << eixo.getX() << "Y = " << eixo.getY() << endl;
		escreveTerminal(
				nome + " girou " + to_string(angulo)
						+ " graus em torno do centro do mundo");
		break;
	case 1:
		eixo = figura->getCentro();
		escreveTerminal(
				nome + " girou " + to_string(angulo)
						+ " graus em torno do seu centro");
		break;
	case 2:
		eixo = Coordenada(getSpinButtonValue("x_rotacao"), getSpinButtonValue("y_rotacao"));
		escreveTerminal(
				nome + " girou " + to_string(angulo)
						+ " graus em torno do ponto " + eixo.toString());
		break;
	}

	if (posFigura > -1) {
		figura->transform(eixo, angulo, 1, 1, naoDeslocar);
		redesenhaTudo();
	} else {
		escreveTerminal("Selecione figura!");
	}
}

int Tela::tipoRotacao() {
	GtkRadioButton *rotacaoCentroTela =
			GTK_RADIO_BUTTON(
					gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "radioCentroTela"));
	GtkRadioButton *rotacaoCentroFigura =
			GTK_RADIO_BUTTON(
					gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "radioCentroFigura"));
	GtkRadioButton *rotacaoPontoEspecifico =
			GTK_RADIO_BUTTON(
					gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "radioPontoEspecifico"));

	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rotacaoCentroTela))) {
		return 0;
	} else if (gtk_toggle_button_get_active(
			GTK_TOGGLE_BUTTON(rotacaoCentroFigura))) {
		return 1;
	} else if (gtk_toggle_button_get_active(
			GTK_TOGGLE_BUTTON(rotacaoPontoEspecifico))) {
		return 2;
	}
	return -1;
}

double Tela::getSpinButtonValue(string nome) {
	GtkSpinButton *spinButton;
	spinButton = GTK_SPIN_BUTTON(
			gtk_builder_get_object( GTK_BUILDER(gtkBuilder), nome.c_str()));
	return gtk_spin_button_get_value(spinButton);
}

void Tela::rotacionaFigura() {
	int posFigura = posicaoFigSelecionada();
	if (posFigura > -1) {
		double angulo = getSpinButtonValue("angulo");
		string nome = mundo->getFiguras()->retornaDado(posFigura)->getNome();

		switch (tipoRotacao()) {
		case 0:
			mundo->rotacionaFiguraCentroTela(posFigura, angulo);
			escreveTerminal(
					nome + " girou " + to_string(angulo)
							+ " graus em torno do centro da tela");
			break;
		case 1:
			mundo->rotacionaFiguraProprioCentro(posFigura, angulo);
			escreveTerminal(
					nome + " girou " + to_string(angulo)
							+ " graus em torno do seu centro");
			break;
		case 2:
			Coordenada coord = Coordenada(getSpinButtonValue("x_rotacao"),
					getSpinButtonValue("y_rotacao"));
			mundo->rotacionaFigura(posFigura, coord, angulo);
			escreveTerminal(
					nome + " girou " + to_string(angulo)
							+ " graus em torno do ponto " + coord.toString());
			break;
		}
		redesenhaTudo();
	} else {
		escreveTerminal("Selecione figura!");
	}
}

Coordenada Tela::FatorOuDeslocamento() {
	double x, y;
	x = getSpinButtonValue("x_desloc");
	y = getSpinButtonValue("y_desloc");
	return Coordenada(x, y);
}
