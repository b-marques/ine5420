#include <gtk/gtk.h>
#include "gtk_actions.hpp"
#include "button.cpp"

GtkBuilder *gtk_builder;
GtkWidget *main_window;

int main (int argc, char **argv)
{
  gtk_init(&argc, &argv);
  GtkActions::style_css();

  gtk_builder = gtk_builder_new();
  gtk_builder_add_from_file(gtk_builder, "src/gui/window.glade", NULL);

  main_window = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtk_builder), "window1"));
  g_signal_connect(main_window,"destroy", G_CALLBACK(gtk_main_quit), NULL);

  Button::create(gtk_builder, "button1", "myButton_default");

  gtk_builder_connect_signals(gtk_builder, NULL);
  gtk_widget_show_all(main_window);

  gtk_main();
  return 0;
}