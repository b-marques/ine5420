/* Lista Especifica para algoritmo de Weiler
 * no header Poligono.hpp.
 */
#ifndef LISTAESPECIALWINDOW_HPP_
#define LISTAESPECIALWINDOW_HPP_
#include "ListaEnc.hpp"
#include "Coordenada.hpp"
class ListaEspecialWindow : public ListaEnc<Coordenada>{
private:
	Coordenada infEsq, infDir, supEsq, supDir;
public:
	ListaEspecialWindow(double xEsq, double xDir, double yCima, double yBaixo);
	virtual ~ListaEspecialWindow();
	void addCoordArtificial(Coordenada coord);
	int linhaCoordenadaArtificial(Coordenada coord);
	void addNaLinha1(Coordenada artf, Elemento<Coordenada> *headAux, int posInicial);
	void addNaLinha2(Coordenada artf, Elemento<Coordenada> *headAux, int posInicial);
	void addNaLinha3(Coordenada artf, Elemento<Coordenada> *headAux, int posInicial);
	void addNaLinha4(Coordenada artf,Elemento<Coordenada> *headAux, int posInicial);
	void retiraInfEsqDuplicado();
};

#endif /* LISTAESPECIALWINDOW_HPP_ */
