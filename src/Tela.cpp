/*
 * Tela.cpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#include "Tela.h"



Tela::Tela() {
	GtkWidget *window_widget;
	GtkBuilder *gtkBuilder = gtk_builder_new();
	gtk_builder_add_from_file(gtkBuilder, "window.glade", NULL);
	window_widget = GTK_WIDGET(
			gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "window1"));
	gtk_builder_connect_signals(gtkBuilder, NULL);
	gtk_widget_show_all(window_widget);
	gtk_main();
}

Tela::~Tela() {
	// TODO Auto-generated destructor stub
}

