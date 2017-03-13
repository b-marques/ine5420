#include <gtk/gtk.h>
#include "gtk_actions.hpp"
#include "button.cpp"

static cairo_surface_t *surface = NULL;
GtkWidget *drawing_area;
GtkWidget *main_window; 
GtkWidget *button;
gboolean switch_cairo = TRUE;

static void clear_surface (){
  cairo_t *cr;
  cr = cairo_create (surface);

  cairo_set_source_rgb (cr, 1, 1, 1);
  cairo_paint (cr);

  cairo_destroy (cr);
}

static gboolean create_surface (GtkWidget *widget, GdkEventConfigure *event, gpointer data){
  if (surface)
    cairo_surface_destroy (surface);

  surface = gdk_window_create_similar_surface (gtk_widget_get_window (widget),
                                       CAIRO_CONTENT_COLOR,
                                       gtk_widget_get_allocated_width (widget),
                                       gtk_widget_get_allocated_height (widget));
  clear_surface ();
  return TRUE;
}

static gboolean redraw (GtkWidget *widget, cairo_t   *cr,  gpointer   data){
  cairo_set_source_surface (cr, surface, 0, 0);
  cairo_paint (cr);

  return FALSE;
}

static void draw_slice() {
    cairo_t *cr;
    cr = cairo_create (surface);
    cairo_move_to(cr, 500, 500);
    cairo_line_to(cr, 0, 0);
    cairo_stroke(cr);
}

static void draw_rect() {
    cairo_t *cr;
    cr = cairo_create (surface);
    cairo_rectangle(cr, 20, 20, 200, 200);
    cairo_stroke(cr);
}

static void clicked(){
    if (switch_cairo) {
      clear_surface();
      draw_slice();
      switch_cairo = FALSE;
    } else {
      clear_surface();
      draw_rect();
      switch_cairo = TRUE;
    } 

    gtk_widget_queue_draw(drawing_area);
}  



int main (int argc, char **argv)
{
  gtk_init(&argc, &argv);
  GtkActions::style_css();

  // GtkWidget *main_window;
  GtkBuilder *gtk_builder;
  // GtkWidget *drawing_area;

  gtk_builder = gtk_builder_new();
  gtk_builder_add_from_file(gtk_builder, "src/gui/window.glade", NULL);

  main_window = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtk_builder), "window1"));
  g_signal_connect(main_window,"destroy", G_CALLBACK(gtk_main_quit), NULL);

  drawing_area = GTK_WIDGET(gtk_builder_get_object( GTK_BUILDER(gtk_builder), "drawingarea1"));
  g_signal_connect(drawing_area,"draw", G_CALLBACK(redraw), NULL);
  g_signal_connect (drawing_area,"configure-event", G_CALLBACK (create_surface), NULL);

  button = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtk_builder), "button1"));
  gtk_widget_set_name(button, "myButton_default");
  g_signal_connect (button, "clicked", G_CALLBACK (clicked), NULL);
  // Button::create(gtk_builder, "button1", "myButton_default");

  gtk_builder_connect_signals(gtk_builder, NULL);
  gtk_widget_show_all(main_window);

  gtk_main();
  return 0;
}
