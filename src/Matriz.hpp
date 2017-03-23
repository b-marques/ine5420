#include "Coordenada.hpp"
#include <vector>
#include <math.h>      

class Matriz {
private: 
	std::vector<std::vector<double> > matriz;
public:
	Matriz(Coordenada coord, int dimensao){
		matriz.resize(1);
    	matriz[0].resize(dimensao+1);

    	matriz[0][0] = coord.getX();
    	matriz[0][1] = coord.getY();
		matriz[0][2] = 1;

	};

	static Coordenada matrizTransformacao(Coordenada& coord, Coordenada& eixo, double grau, double escalaX, double escalaY, Coordenada deslocamento){
		Coordenada* origem = new Coordenada();

		Coordenada deslocOrigem = eixo - *origem;
		
		double anguloRad = grau * M_PI / 180.0;
		double x = deslocamento.getX()+ escalaX*((coord.getX() - deslocOrigem.getX())*cos(anguloRad)+(coord.getY()-deslocOrigem.getY())*sin(anguloRad)) + deslocOrigem.getX();
		double y = deslocamento.getY()+ escalaY*((coord.getY() - deslocOrigem.getY())*cos(anguloRad)-(coord.getX()-deslocOrigem.getX())*sin(anguloRad)) + deslocOrigem.getY();

		return Coordenada(x, y);
	};

};