/*
 * Tela.cpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#include "Tela.hpp"
#include "ViewPortOffset.hpp"
#include "Figura3D.hpp"

Tela::Tela() {
	GtkWidget *window_widget;
	gtkBuilder = gtk_builder_new();

	gtk_builder_add_from_file(gtkBuilder, "window.glade", NULL);
	window_widget = GTK_WIDGET(
			gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "main_window"));
	drawArea = GTK_WIDGET(
			gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "drawing_area"));
	//surface = NULL;
	desenhador = new Desenhador(drawArea);
	mundo = new Mundo(gtk_widget_get_allocated_width(GTK_WIDGET(drawArea)),
			gtk_widget_get_allocated_height(drawArea));
	descritor = new DescritorObj(mundo);
	adicionarWindow = GTK_WIDGET(
			gtk_builder_get_object(gtkBuilder, "add_object_window"));
	g_signal_connect(GTK_WIDGET(adicionarWindow), "delete_event",
			G_CALLBACK (gtk_widget_hide), NULL);

	g_signal_connect_swapped(G_OBJECT(window_widget), "destroy",
			G_CALLBACK(gtk_main_quit), NULL);
	gtk_builder_connect_signals(gtkBuilder, NULL);
	gtk_widget_show_all(window_widget);
}

void Tela::adicionaFigura(string nome, TipoFigura tipo) {
	Figura* f;
	int tipoClip;
	int xDirVP = gtk_widget_get_allocated_width(drawArea) - VPOffset;
	int yCimaVP = gtk_widget_get_allocated_height(drawArea) - VPOffset;
	switch (tipo) {
	case PONTO:
		f = mundo->adicionaPonto(nome, coordTemp);
		break;
	case RETA:
		f = mundo->adicionaReta(nome, coordTemp);
		break;
	case POLIGONO:
		f = mundo->adicionaPoligono(nome, coordTemp);
		break;
	case BEZIER:
		f = mundo->adicionaBezier(nome, coordTemp);
		break;
	case BSPLINE:
		f = mundo->adicionaBspline(nome, coordTemp);
		break;	
	default:
		break;
	}
	tipoClip = tipoClipping();
	if(!tipoClip)
		redesenhaFigura(f);
	else
		redesenhaFiguraClip(f, tipoClip, xDirVP, yCimaVP);
	escreveTerminal("Figura adicionada: " + nome + coordenadasTxt(coordTemp));
	escreveListaObjetos(nome);
	limpaListaCoord();
}

void Tela::limpaListaCoord() {
	ListaEnc<Coordenada> novaLista;
	coordTemp = novaLista;
	GtkLabel* label_coord = GTK_LABEL(
			gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "coord_number"));
	gtk_label_set_text(GTK_LABEL(label_coord), std::to_string(coordTemp.tamanho()).c_str());
}

string Tela::getEntryText(string nomeEntry) {
	GtkEntry* caixaTxt = GTK_ENTRY(
			gtk_builder_get_object(gtkBuilder, nomeEntry.c_str()));
	return gtk_entry_get_text(caixaTxt);
}

double Tela::getPasso() {
	return atof(getEntryText("entryPasso").c_str());
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
	desenhador->limpaDesenho();
	int tipoClip = tipoClipping();
	if (tipoClip != 0) {
		desenhador->desenhaViewPort();
		int xDirVP = gtk_widget_get_allocated_width(drawArea) - VPOffset;
		int yCimaVP = gtk_widget_get_allocated_height(drawArea) - VPOffset;
		for (int i = 0; i < figLista->tamanho(); i++) {
			redesenhaFiguraClip(figLista->retornaDado(i), tipoClip, xDirVP,
					yCimaVP);
		}
	} else {
		for (int i = 0; i < figLista->tamanho(); i++) {
			redesenhaFigura(figLista->retornaDado(i));
		}
	}
}

void Tela::redesenhaFiguraClip(Figura* f, int tipoClip, int xDirVP,
		int yCimaVP) {
	ListaEnc<Coordenada> *coordsFig;
	ListaEnc<ListaEnc<Coordenada>*> *coords;
	coords = f->getCoordTelaClip(VPOffset, xDirVP, yCimaVP, VPOffset, tipoClip);
	TipoFigura tipo = f->getTipo();
	if (coords != nullptr) {
		for (int i = 0; i < coords->tamanho(); i++) {
			coordsFig = coords->retornaDado(i);
			if(tipo == RETA || tipo == BEZIER || tipo == BSPLINE)
				desenhador->desenhaPoligonoRetaCurva(*coordsFig, false);
			else if(tipo == POLIGONO || tipo == FIGURA3D)
				desenhador->desenhaPoligonoRetaCurva(*coordsFig, true);
			else
				desenhador->desenhaPonto(*coordsFig);
			delete coordsFig;
		}
		delete coords;
	}
}

void Tela::redesenhaFigura(Figura* f) {
	ListaEnc<Coordenada> coordsFig;
	coordsFig = f->getCoordTela();
	TipoFigura tipo = f->getTipo();
	if(tipo == RETA || tipo == BEZIER || tipo == BSPLINE)
		desenhador->desenhaPoligonoRetaCurva(coordsFig, false);
	else if(tipo == POLIGONO)
		desenhador->desenhaPoligonoRetaCurva(coordsFig, true);
	else if(tipo == PONTO)
		desenhador->desenhaPonto(coordsFig);
	else {
		Figura3D *fig = (Figura3D*) f;
		for (int i = 0; i < fig->numSuperficies(); i++) {
			desenhador->desenhaPoligonoRetaCurva(fig->getSuperficie(i), true);
		}
	}
}

gboolean Tela::redraw(GtkWidget* widget, cairo_t* cr) {
	return desenhador->redraw(cr);
}

gboolean Tela::criaSurface(GtkWidget *widget) {
	return desenhador->criaSurface(widget);
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

void Tela::adicionarPonto() {

	string nomeFigura = getNomeFigAdd();
	if (coordTemp.tamanho() != 1) {
		escreveTerminal(
				"Número de pontos inválido para criação de ponto!");
	} else {
		adicionaFigura(nomeFigura, PONTO);
		limpaListaCoord();
	}
}

void Tela::adicionarReta() {
	string nomeFigura = getNomeFigAdd();
	if (coordTemp.tamanho() != 2) {
		escreveTerminal(
				"Número de pontos inválido para criação de reta!");
	} else {
		adicionaFigura(nomeFigura, RETA);
		limpaListaCoord();
	}
}

void Tela::adicionarPoligono() {
	string nomeFigura = getNomeFigAdd();
	if (coordTemp.tamanho() < 3) {
		escreveTerminal(
				"Número de pontos insuficientes para criação de polígono!");
	} else {
		adicionaFigura(nomeFigura, POLIGONO);
		limpaListaCoord();
	}
}

void Tela::adicionarBezier() {
	string nomeFigura = getNomeFigAdd();
	if (coordTemp.tamanho() % 3 != 1) {
		escreveTerminal(
				"Número de pontos não obedecem regra para criação da curva de Bezier");
	} else {
		adicionaFigura(nomeFigura, BEZIER);
		limpaListaCoord();
	}
}

void Tela::adicionarBspline(){
	string nomeFigura = getNomeFigAdd();
	if (coordTemp.tamanho() < 4) {
		escreveTerminal(
				"Número de pontos não obedecem regra para criação da curva Bspline");
	} else {
		adicionaFigura(nomeFigura, BSPLINE);
		limpaListaCoord();
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
	double x = getSpinButtonValue("coord_x");
	double y = getSpinButtonValue("coord_y");
	double z = getSpinButtonValue("coord_z");
	coordTemp.adiciona(Coordenada(x, y, z));
	GtkLabel* label_coord = GTK_LABEL(
			gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "coord_number"));
	gtk_label_set_text(label_coord, std::to_string(coordTemp.tamanho()).c_str());
}	

void Tela::escreveListaObjetos(string nome) {
	GtkListStore* lista = GTK_LIST_STORE(
			gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "listFiguras"));
	GtkTreeIter iterator;
	gtk_list_store_append(lista, &iterator);
	gtk_list_store_set(lista, &iterator, 0, nome.c_str(), -1);
}

void Tela::limpaListaObjetos() {
	GtkListStore* lista = GTK_LIST_STORE(
			gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "listFiguras"));
	gtk_list_store_clear(lista);
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

void Tela::transladaFigura() {
	int posFigura = posicaoFigSelecionada();
	if (posFigura > -1) {
		Coordenada coord = FatorOuDeslocamento();
		mundo->transladaFigura(posFigura, coord);
		redesenhaTudo();
	} else {
		escreveTerminal("Selecione figura!");
	}
}

int Tela::tipoRotacao() {
	GtkRadioButton *rotacaoCentroMundo =
			GTK_RADIO_BUTTON(
					gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "radioCentroMundo"));
	GtkRadioButton *rotacaoCentroFigura =
			GTK_RADIO_BUTTON(
					gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "radioCentroFigura"));
	GtkRadioButton *rotacaoPontoEspecifico =
			GTK_RADIO_BUTTON(
					gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "radioPontoEspecifico"));

	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rotacaoCentroMundo))) {
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

int Tela::tipoClipping() {
	GtkRadioButton *clipOff = GTK_RADIO_BUTTON(
			gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "clipOff"));
	GtkRadioButton *clipCs = GTK_RADIO_BUTTON(
			gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "clipCs"));
	GtkRadioButton *clipLb = GTK_RADIO_BUTTON(
			gtk_builder_get_object (GTK_BUILDER(gtkBuilder), "clipLb"));

	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(clipOff))) {
		return 0;
	} else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(clipCs))) {
		return 1;
	} else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(clipLb))) {
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
		//mexer
		double angulo = getSpinButtonValue("angulo");
		string nome = mundo->getFiguras()->retornaDado(posFigura)->getNome();

		switch (tipoRotacao()) {
		case 0:
			//mundo->rotacionaFiguraCentroMundo(posFigura, angulo);
			escreveTerminal(
					nome + " girou " + to_string(angulo)
							+ " graus em torno do centro da tela");
			break;
		case 1:
			//mundo->rotacionaFiguraProprioCentro(posFigura, angulo);
			escreveTerminal(
					nome + " girou " + to_string(angulo)
							+ " graus em torno do seu centro");
			break;
		case 2:
			Coordenada coord = Coordenada(getSpinButtonValue("x_rotacao"),
					getSpinButtonValue("y_rotacao"));
			//mundo->rotacionaFigura(posFigura, coord, angulo);
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
	double x, y, z;
	x = getSpinButtonValue("x_desloc");
	y = getSpinButtonValue("y_desloc");
	z = getSpinButtonValue("z_desloc");
	return Coordenada(x, y, z);
}

void Tela::salvaMundo() {
	string nomeArq = getEntryText("nomeArq");
	descritor->salvaMundo(nomeArq);
}

void Tela::abreMundo() {
	string nomeFig, nomeArq = getEntryText("nomeArq");
	descritor->leMundo(nomeArq);
	limpaListaObjetos();
	ListaEnc<Figura*>* figuras = mundo->getFiguras();
	for (int i = 0; i < figuras->tamanho(); i++) {
		nomeFig = figuras->retornaDado(i)->getNome();
		escreveListaObjetos(nomeFig);
	}
	redesenhaTudo();
}

void Tela::giraTelaHora() {
	double angulo = getSpinButtonValue("angulo");
	mundo->giraTela(-angulo);
	redesenhaTudo();
}

void Tela::giraTelaAntiHora() {
	double angulo = getSpinButtonValue("angulo");
	mundo->giraTela(angulo);
	redesenhaTudo();
}

void Tela::tamanhoDrawMudou(GdkRectangle* novoTam) {
	mundo->mudaTamanhoDesenho(novoTam->width, novoTam->height);
	redesenhaTudo();
}
