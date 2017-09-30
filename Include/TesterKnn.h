#ifndef _TESTERKNN_H_
#define _TESTERKNN_H_

#include <vector>
#include <string>
#include <utility>
#include "knn.h"

using namespace std;

class TesterKnn {
public:
	TesterKnn();
	~TesterKnn();

	//devuelve los test incorrectos o vector vacio si todos fueron correctos.
	vector<string> correrTests()const;

	bool testDistanciaCuadradaEntreE1YE2Correcta()const;
	bool testObtenerDistanciasCuadradasConElemento()const;
	bool testObtenerKElementosMasCercanosConKIgualAUnoYLaMenorDistanciaEsConElPrimerElemento()const;
	bool testObtenerKElementosMasCercanosConKIgualAUnoYLaMenorDistanciaEsConElUltimoElemento()const;
	bool testObtenerKElementosMasCercanosConKIgualACantidadDeElementos()const;
	bool testObtenerClaseDeElementoConMayorFrecuenciaConKIgualAUno()const;
	bool testObtenerClaseDeElementoConMayorFrecuenciaConKIgualACantidadDeElementos()const;
	bool testClasificarElementoConKIgualAUno()const;
	bool testClasificarElementoConKIgualACantidadDeElementos()const;
private:
	template<class T>
	bool vectoresIguales(const vector<T> &v1, const vector<T> &v2) const{
		bool res = v1.size() == v2.size();
		if (!res)
			return res;

		for (int i = 0; i < v1.size(); i++) {
			if (v1[i] != v2[i]) {
				res = false;
				break;
			}
		}

		return res;
	}
};

#endif // !_TESTERKNN_H_
