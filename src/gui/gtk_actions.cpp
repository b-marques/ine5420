#include "gtk_actions.hpp"

void GtkActions::activate(GtkApplication* app, gpointer user_data)
{

}

void GtkActions::on_button1_clicked(GtkWidget *widget, gpointer data)
{
	g_print("Hello World\n");
}
