#ifndef _KNN_H_
#define _KNN_H_

#include <vector>
#include <queue>
#include <functional>
#include <utility>

using namespace std;

typedef vector<int> tipoElemento;
typedef int tipoClase;
typedef pair<double, int> tipoDistanciaIndiceElemento;

class ComparadorDeDistancias {
public:
	ComparadorDeDistancias();
	~ComparadorDeDistancias();

	bool operator()(const tipoDistanciaIndiceElemento &d1, const tipoDistanciaIndiceElemento &d2) const;
};

typedef priority_queue<tipoDistanciaIndiceElemento, vector<tipoDistanciaIndiceElemento>, ComparadorDeDistancias> colaDePrioridadDistanciasIndicesMinima;

class Knn {
public:
	//Los valores de las clases deben estar en el rango [0, maximoValorDeClase).
	Knn(int k, const vector<tipoElemento> &elementos, const vector<tipoClase> &clasesPorElemento, int maximoValorDeClase);
	~Knn();
	tipoClase clasificarElemento(const tipoElemento &elemento) const;
	vector<tipoDistanciaIndiceElemento> obtenerDistanciasCuadradasConElemento(const tipoElemento &elemento)const;
	double distanciaCuadradaEntreE1YE2(const tipoElemento &e1, const tipoElemento &e2)const;
	vector<int> obtenerIndicesDeKElementosMasCercanos(const vector<tipoDistanciaIndiceElemento> &distanciasConIndices) const;
	tipoClase obtenerClaseDeElementoConMayorFrecuencia(const vector<int> &indicesDeElementos)const;
private:
	int _k;
	vector<tipoElemento> _elementos;
	vector<tipoClase> _clasesPorElemento;
	int _maximoValorDeClase;
};

#endif
