#ifndef GTK_ACTIONS_HPP
#define GTK_ACTIONS_HPP

#include <gtk/gtk.h>

class GtkActions {

public:
	static void on_button1_clicked(GtkWidget *widget, gpointer data);
};

#endif /* GTK_ACTIONS_HPP */