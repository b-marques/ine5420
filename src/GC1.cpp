#include <gtk/gtk.h>
#include <glib.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <cairo.h>
#include <gdk/gdkcairo.h>
#include "Mundo.h"
using namespace std;

cairo_surface_t* surface = NULL;
cairo_t* cr;
GtkBuilder *gtkBuilder;
GtkWidget* drawingArea;
Mundo mundo;
double xi, yi;
int a = 0;

void clear_surface() {
	cairo_t *cr;
	cr = cairo_create(surface);

	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_paint(cr);
	cairo_destroy(cr);
}

extern "C" gboolean redraw(GtkWidget *widget, cairo_t *cr, gpointer data) {
	cairo_set_source_surface(cr, surface, 0, 0);
	cairo_paint(cr);

	return FALSE;
}

extern "C" gboolean configura(GtkWidget *widget, GdkEventConfigure *event,
		gpointer data) {
	if (surface)
		cairo_surface_destroy(surface);

	surface = gdk_window_create_similar_surface(gtk_widget_get_window(widget),
			CAIRO_CONTENT_COLOR, gtk_widget_get_allocated_width(widget),
			gtk_widget_get_allocated_height(widget));
	clear_surface();
	drawingArea = widget;
	cr = cairo_create(surface);
	cairo_set_line_width(cr, 0.5);
	cairo_set_source_rgb(cr, 1,0,0);
	cairo_move_to(cr, 50, 50);
	cairo_line_to(cr, 100, 100);
	cairo_stroke(cr);
	return TRUE;
}

extern "C" void iniciais_clicked(GtkWidget *button, gpointer user_data) {
	GtkEntry *entry1, *entry2;
	entry1 = GTK_ENTRY(
			gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "entry1"));
	entry2 = GTK_ENTRY(
			gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "entry2"));
	xi = atof(gtk_entry_get_text(entry1));
	yi = atof(gtk_entry_get_text(entry2));
	//cairo_move_to(cr, x1, y1);
	gtk_entry_set_text(entry1, "");
	gtk_entry_set_text(entry2, "");

}

extern "C" void finais_clicked(GtkWidget *button, gpointer user_data) {
	GtkEntry *entry1, *entry2;
	double xf, yf;
	entry1 = GTK_ENTRY(
			gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "entry1"));
	entry2 = GTK_ENTRY(
			gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "entry2"));
	xf = atof(gtk_entry_get_text(entry1));
	yf = atof(gtk_entry_get_text(entry2));
	mundo.adicionaReta("CU", xi, yi, xf, yf);
	gtk_entry_set_text(entry1, "");
	gtk_entry_set_text(entry2, "");
	cairo_set_line_width(cr, 0.5);
	cairo_set_source_rgb(cr, 1,0,0);
	cairo_move_to(cr, xi, yi);
	cairo_line_to(cr, xf, yf);
	cairo_stroke(cr);
	gtk_widget_queue_draw(drawingArea);
}
extern "C" void destroitudo(GtkWidget *button, gpointer user_data) {
	gtk_widget_grab_focus(drawingArea);
}
extern "C" gboolean keypress(GtkWidget *widget, GdkEvent *event,
		gpointer user_data) {
	if(event->key.keyval == GDK_KEY_s){
		cairo_move_to(cr, 50, 50);
		cairo_line_to(cr, 2, 2);
		cairo_stroke(cr);
		gtk_widget_queue_draw(drawingArea);
	}
	return FALSE;
}

int main(int argc, char *argv[]) {
	GtkWidget *window_widget;
	gtk_init(&argc, &argv);
	gtkBuilder = gtk_builder_new();
	gtk_builder_add_from_file(gtkBuilder, "window.glade", NULL);
	window_widget = GTK_WIDGET(
			gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "window1"));
	gtk_builder_connect_signals(gtkBuilder, NULL);
	gtk_widget_show_all(window_widget);
	gtk_main();
	return 0;
}
