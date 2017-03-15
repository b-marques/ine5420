/*
 * Tela.h
 *
 *  Created on: 14 de mar de 2017
 *      Author: johann
 */

#ifndef TELA_H_
#define TELA_H_
#include "Mundo.h"
#include <gtk/gtk.h>
#include <glib.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <cairo.h>
#include <gdk/gdkcairo.h>

class Tela {
private:
	Mundo mundo;
public:
	Tela();
	virtual ~Tela();
};

#endif /* TELA_H_ */
