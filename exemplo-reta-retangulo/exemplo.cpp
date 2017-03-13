#include <gtk/gtk.h>
#include <glib.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <cairo.h>
#include <gdk/gdkcairo.h>
using namespace std;
int a = 0;

extern "C" gboolean desenha(GtkWidget *widget, cairo_t *cr,
		gpointer user_data) {
	cairo_set_line_width(cr, 1);
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_rectangle(cr, 20, 20, 200, 200);
	cairo_move_to(cr, 100, 100);
	cairo_rel_line_to(cr, 50, -50);
	cairo_stroke(cr);
	return FALSE;
}
extern "C" void b1_handler(GtkButton *button, gpointer user_data) {
	char c[16];
	a++;
	sprintf(c, "%d", a);
	gtk_button_set_label(button, c);

}
int main(int argc, char *argv[]) {
	GtkWidget *window_widget;
	GtkBuilder *gtkBuilder;
	GtkDrawingArea *drawArea;
	gtk_init(&argc, &argv);
	gtkBuilder = gtk_builder_new();
	gtk_builder_add_from_file(gtkBuilder, "window.glade", NULL);
	window_widget = GTK_WIDGET(
			gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "window1"));
	drawArea = GTK_DRAWING_AREA(
			gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "drawingarea1"));
	gtk_builder_connect_signals(gtkBuilder, NULL);
	gtk_widget_show_all(window_widget);
	gtk_main();
	return 0;
}
