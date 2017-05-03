#include <vector>
#include <math.h>      
#include "Coordenada.hpp"

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

	static Coordenada matrizTransformacao(const Coordenada& coord,const Coordenada& eixo, double grau, const Coordenada& escala, const Coordenada& deslocamento){
		// {{x,y,1}}.{{1,0,0},{0,1,0},{-d,-f,1}}. {{cos o, -sin o, 0}, {sin o, cos o, 0},{0,0,1}} . {{u,0,0},{0,w,0},{0,0,1}}. {{1,0,0},{0,1,0},{d,f,1}} . {{1,0,0},{0,1,0},{c,b,1}}
		// VER "matriz-transformacao.png" para entender
		double anguloRad = grau * M_PI / 180.0;
		double x = deslocamento.getX()+ escala.getX()*((coord.getX() - eixo.getX())*cos(anguloRad)+(coord.getY()-eixo.getY())*sin(anguloRad)) + eixo.getX();
		double y = deslocamento.getY()+ escala.getY()*((coord.getY() - eixo.getY())*cos(anguloRad)-(coord.getX()-eixo.getX())*sin(anguloRad)) + eixo.getY();

		return Coordenada(x, y);
	};

	static Coordenada giraCoord(Coordenada& coord, Coordenada eixo, double grau){
		double anguloRad = -grau * M_PI / 180.0;
		double cosAngulo = cos(anguloRad), senAngulo = sin(anguloRad);
		Coordenada coordRel = coord - eixo;
		double x = coordRel.getX() * cosAngulo
				- coordRel.getY() * senAngulo;
		double y = coordRel.getX() * senAngulo
				+ coordRel.getY() * cosAngulo;
		return Coordenada(x, y) + eixo;
	}

	static Coordenada rotaciona3d(Coordenada coord, Coordenada& eixo0, double& sinA, double& cosA, double& sinB, double& cosB, double& sinSig, double& cosSig){
	double x, y, z, k, l, m, xFinal, yFinal, zFinal;
	k = coord.getX();
	l = coord.getY();
	m = coord.getZ();
	x = eixo0.getX();
	y = eixo0.getY();
	z = eixo0.getZ();
	xFinal = x + ((k - x)*sinB + ((l - y)*sinA + (m - z)*cosA)*cosB)*sinB + (((k
	    - x)*cosB - ((l - y)*sinA + (m - z)*cosA)*sinB)*cosSig - ((l - y)*cosA
	    - (m - z)*sinA)*sinSig)*cosB;

	yFinal = y + (((k - x)*sinB + ((l - y)*sinA + (m - z)*cosA)*cosB)*cosB - (((k
	    - x)*cosB - ((l - y)*sinA + (m - z)*cosA)*sinB)*cosSig - ((l - y)*cosA
	    - (m - z)*sinA)*sinSig)*sinB)*sinA + (((k - x)*cosB - ((l - y)*sinA
		+ (m - z)*cosA)*sinB)*sinSig + ((l - y)*cosA - (m - z)*sinA)*cosSig)*cosA;

	zFinal = z + (((k - x)*sinB + ((l - y)*sinA + (m - z)*cosA)*cosB)*cosB - (((k
			 - x)*cosB - ((l - y)*sinA + (m - z)*cosA)*sinB)*cosSig - ((l - y)*cosA
			 - (m - z)*sinA)*sinSig)*sinB)*cosA - (((k - x)*cosB - ((l - y)*sinA
			 + (m - z)*cosA)*sinB)*sinSig + ((l - y)*cosA - (m - z)*sinA)*cosSig)*sinA;

	return Coordenada(xFinal, yFinal, zFinal);
	};

/*
	  x + ((k - x)*sin(b) + ((l - y)*sin(a) + (m - z)*cos(a))*cos(b))*sin(b) + (((k
	  - x)*cos(b) - ((l - y)*sin(a) + (m - z)*cos(a))*sin(b))*cos(d) - ((l - y)*cos(
	  a) - (m - z)*sin(a))*sin(d))*cos(b)

	  y + (((k - x)*sin(b) + ((l - y)*sin(a) + (m - z)*cos(a))*cos(b))*cos(b) - (((k
	   - x)*cos(b) - ((l - y)*sin(a) + (m - z)*cos(a))*sin(b))*cos(d) - ((l - y)*cos
	  (a) - (m - z)*sin(a))*sin(d))*sin(b))*sin(a) + (((k - x)*cos(b) - ((l - y)*sin
	  (a) + (m - z)*cos(a))*sin(b))*sin(d) + ((l - y)*cos(a) - (m - z)*sin(a))*cos(d
	  ))*cos(a)


	  z + (((k - x)*sin(b) + ((l - y)*sin(a) + (m - z)*cos(a))*cos(b))*cos(b) - (((k
	   - x)*cos(b) - ((l - y)*sin(a) + (m - z)*cos(a))*sin(b))*cos(d) - ((l - y)*cos
	  (a) - (m - z)*sin(a))*sin(d))*sin(b))*cos(a) - (((k - x)*cos(b) - ((l - y)*sin
	  (a) + (m - z)*cos(a))*sin(b))*sin(d) + ((l - y)*cos(a) - (m - z)*sin(a))*cos(d
	  ))*sin(a)
*/
};

