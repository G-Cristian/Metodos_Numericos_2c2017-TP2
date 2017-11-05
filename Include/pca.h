#ifndef _PCA_H_
#define _PCA_H_

#include "matriz.h"
#include "metPotencia.h"
#include "deflacion.h"
#include <assert.h>
#include <vector>
#include <utility>
#include <math.h>

using namespace std;

template<class T>
class PCA {
public:
	PCA(const vector<vector< int> > &imagenes, int alfa, double epsilonConvergencia) {
		_alfa = alfa;
		Matriz<T> matrizDeCovarianza = obtenerMartrizDeCovarianza(imagenes);
		inicializarAutovaloresYAutovectores(matrizDeCovarianza, epsilonConvergencia);
	}
	~PCA() {}

	Matriz<T> obtenerMartrizDeCovarianza(const vector<vector< int> > &imagenes)const {
		const vector<T> promedio = obtenerPromedio(imagenes);
		Matriz<T> matrizIntermedia = obtenerMatrizIntermediaConPromedios(imagenes, promedio);

		return matrizIntermedia.transpuesta() * matrizIntermedia;
	}

	//Obtiene promedio de las imagenes.
	//Cada imagen (vector int) debe tener el mismo tamaño.
	//Debe haber por lo menos una imagen.
	vector<T> obtenerPromedio(const vector<vector< int> > &imagenes) const {
		assert(imagenes.size() > 0);
		int n = imagenes.size();
		int m = imagenes[0].size();

		vector<T> promedio = vector<T>(m, T());

		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				promedio[i] += (T)imagenes[j][i];
			}

			promedio[i] /= n;
		}

		return promedio;
	}

	vector<T> transformacionCaracteristica(const vector<int>& imagen)const {
		vector<T> ret = vector<T>(_alfa);
		int n = imagen.size();
		Matriz<T> imagenMatriz = Matriz<T>(imagen);
		for (int i = 0; i < _alfa; i++) {
			ret[i] = (_autovectores[i].transpuesta() * imagenMatriz)[0][0];
		}

		return ret;
	}

private:

	Matriz<T> obtenerMatrizIntermediaConPromedios(const vector<vector< int> > &imagenes, const vector<T> &promedio)const {
		int n = imagenes.size();
		int m = imagenes[0].size();
		Matriz<T> matriz = Matriz<T>(n, m, T());
		
		for (int i = 0; i < n; i++) {
			matriz[i] = obtenerFilaDeMatrizIntermediaConPromedios(imagenes[i], promedio);
		}

		return matriz;
	}

	vector<T> obtenerFilaDeMatrizIntermediaConPromedios(const vector<int> &imagen, const vector<T> &promedio)const {
		int n = imagen.size();
		vector<T> ret = vector<T>(n);
		for (int i = 0; i < n; i++) {
			ret[i] = ((T)imagen[i] - promedio[i])/sqrt(n - 1);
		}

		return ret;
	}

	void inicializarAutovaloresYAutovectores(const Matriz<T> &matrizDeCovarianza, double epsilonConvergencia) {
		_autovalores = vector<T>(_alfa);
		_autovectores = vector<Matriz<T> >(_alfa);
		Matriz<T> aux = matrizDeCovarianza;

		pair<T, Matriz<T>> autovalor_con_autovector;

		for (int i = 0; i < _alfa; i++) {
			autovalor_con_autovector = MetodoPotenciaConvergencia(aux, epsilonConvergencia);

			_autovalores[i] = autovalor_con_autovector.first;
			_autovectores[i] = autovalor_con_autovector.second;
			aux = deflacion(aux, autovalor_con_autovector);
		}
	}

	int _alfa;
	vector<T> _autovalores;
	vector<Matriz<T> > _autovectores;
};

#endif // !_PCA_H_
