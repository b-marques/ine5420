/*
 * DescritorObj.hpp
 *
 *  Created on: 28 de mar de 2017
 *      Author: johann
 */

#ifndef DESCRITOROBJ_HPP_
#define DESCRITOROBJ_HPP_
#include "Mundo.hpp"
#include <string>
using namespace std;

class DescritorObj {
private:
	Mundo* mundo;

	Coordenada leCoord(string& linha);
	Figura* leObjeto(ifstream& arquivo, string& linhaInicial);
public:
	DescritorObj();
	DescritorObj(Mundo* mundo);
	void salvaMundo(string nomeArquivo);
	void leMundo(string nomeArquivo);
	void escreveFigura(string& texto, Figura* figura, int& linha);
	virtual ~DescritorObj();

};

#endif /* DESCRITOROBJ_HPP_ */
