#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <gtk/gtk.h>

class MainWindow{
	public:
		MainWindow(){
			button_add_ = 
		};
	private:
		GtkWidget* button_add_;

		GtkWidget* button_zoom_in_;
		GtkWidget* button_zoom_out_;
		
		GtkWidget* button_move_up_;
		GtkWidget* button_move_down_;
		GtkWidget* button_move_right_;
		GtkWidget* button_move_left_;


};

#endif /* MAIN_WINDOW_HPP */