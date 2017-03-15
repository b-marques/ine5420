#include <gtk/gtk.h>
#include <glib.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <cairo.h>
#include <gdk/gdkcairo.h>
#include "Mundo.h"
#include "Tela.h"
using namespace std;

Tela* tela;


int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);
	tela = new Tela();
	return 0;
}
