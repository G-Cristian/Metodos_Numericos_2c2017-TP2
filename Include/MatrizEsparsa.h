#ifndef _MATRIZESPARSA_H_
#define _MATRIZESPARSA_H_

#include <map>
#include <utility>
#include "matriz.h"

using namespace std;

typedef pair<int, int> tipoClave;
typedef double tipoElementos;

template<class T> class Matriz;

class MatrizEsparsa {
public:
	MatrizEsparsa(int alto, int ancho);
	template<class T> MatrizEsparsa(const Matriz<T> &otra) {
		_alto = otra.alto();
		_ancho = otra.ancho();

		for (int i = 0; i < _alto; i++) {
			for (int j = 0; j < _ancho; j++) {
				insertarEnYX(i, j, (tipoElementos)otra[i][j]);
			}
		}
	}

	~MatrizEsparsa();

	inline int ancho() const { return _ancho; }
	inline int alto() const { return _alto; }

	tipoElementos enYX(int y, int x) const;
	void insertarEnYX(int y, int x, tipoElementos elemento);
	MatrizEsparsa operator*(const MatrizEsparsa &otra) const;
	MatrizEsparsa transpuesta() const;
	MatrizEsparsa transpuestaPorOtra(const MatrizEsparsa &otra) const;
private:
	map<tipoClave, tipoElementos> _elementos;
	int _alto;
	int _ancho;
};

#endif // !_MATRIZESPARSA_H_
