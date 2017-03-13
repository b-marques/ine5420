#include <gtk/gtk.h>
#include "gtk_actions.hpp"
#include <string>

class Button {
public:
	// Button(GtkBuilder *gtk_builder, std::string id, std::string css_name){
	// 	button_ = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtk_builder), id.c_str()));
	// 	gtk_widget_set_name(button_, css_name.c_str());
	// 	g_signal_connect (button_, "clicked", G_CALLBACK (GtkActions::on_button1_clicked), NULL);
	// };

	static void create(GtkBuilder *gtk_builder, std::string id){
		GtkWidget *button = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtk_builder), id.c_str()));
		gtk_widget_set_name(button, "myButton_default");
		g_signal_connect (button, "clicked", G_CALLBACK (GtkActions::on_button1_clicked), NULL);
	};

	static void create(GtkBuilder *gtk_builder, std::string id, std::string css_name){
		GtkWidget *button = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtk_builder), id.c_str()));
		gtk_widget_set_name(button, css_name.c_str());
		g_signal_connect (button, "clicked", G_CALLBACK (GtkActions::on_button1_clicked), NULL);
	};
private:
	// GtkWidget *button_;
};