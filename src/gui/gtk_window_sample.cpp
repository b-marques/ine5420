#include <gtk/gtk.h>
#include "gtk_actions.hpp"
#include <string.h>

GtkWidget *button_1;
GtkBuilder *gtk_builder;
GtkWidget *window_widget;

int main (int argc, char **argv)
{
  gtk_init(&argc, &argv);

  gtk_builder = gtk_builder_new();
  gtk_builder_add_from_file(gtk_builder, "window.glade", NULL);

  window_widget = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtk_builder), "window1"));
  g_signal_connect(window_widget,"destroy", G_CALLBACK(gtk_main_quit), NULL);

  button_1 = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtk_builder), "button1"));
  g_signal_connect (button_1, "clicked", G_CALLBACK (GtkActions::on_button1_clicked), NULL);
  
  gtk_builder_connect_signals(gtk_builder, NULL);
  gtk_widget_show_all(window_widget);

  gtk_main();
  return 0;
}