#include "../Include/knn.h"
#include <assert.h>

using namespace std;

ComparadorDeDistancias::ComparadorDeDistancias() {

}

ComparadorDeDistancias::~ComparadorDeDistancias() {

}

bool ComparadorDeDistancias::operator()(const tipoDistanciaIndiceElemento &d1, const tipoDistanciaIndiceElemento &d2) const {
	return d1.first > d2.first;
}

//Los valores de las clases deben estar en el rango [0, maximoValorDeClase).
Knn::Knn(int k, const vector<tipoElemento> &elementos, const vector<tipoClase> &clasesPorElemento, int maximoValorDeClase) {
	assert(1 <= k && k <= elementos.size() && elementos.size() == clasesPorElemento.size() && 1 <= maximoValorDeClase);
	_k = k;
	_elementos = elementos;
	_clasesPorElemento = clasesPorElemento;
	_maximoValorDeClase = maximoValorDeClase;
}

Knn::~Knn() {

}

tipoClase Knn::clasificarElemento(const tipoElemento &elemento) const {
	vector<tipoDistanciaIndiceElemento> distanciasCuadradas = obtenerDistanciasCuadradasConElemento(elemento);
	vector<int> indicesDeKElementosMasCercanas = obtenerIndicesDeKElementosMasCercanos(distanciasCuadradas);

	return obtenerClaseDeElementoConMayorFrecuencia(indicesDeKElementosMasCercanas);
}

vector<tipoDistanciaIndiceElemento> Knn::obtenerDistanciasCuadradasConElemento(const tipoElemento &elemento)const {
	int n = _elementos.size();
	vector<tipoDistanciaIndiceElemento> distanciasCuadradas = vector<tipoDistanciaIndiceElemento>(n);

	for (int i = 0; i < n; i++) {
		distanciasCuadradas[i] = tipoDistanciaIndiceElemento(distanciaCuadradaEntreE1YE2(elemento, _elementos[i]), i);
	}

	return distanciasCuadradas;
}

double Knn::distanciaCuadradaEntreE1YE2(const tipoElemento &e1, const tipoElemento &e2)const {
	assert(e1.size() == e2.size());
	int n = e1.size();

	double suma = 0.0;
	double aux = 0.0;

	for (int i = 0; i < n; i++) {
		aux = e1[i] - e2[i];
		suma += aux*aux;
	}

	return suma;
}

vector<int> Knn::obtenerIndicesDeKElementosMasCercanos(const vector<tipoDistanciaIndiceElemento> &distanciasConIndices) const {
	assert(1 <= _k && _k <= distanciasConIndices.size());
	vector<int> kElementosMasCercanos = vector<int>(_k);
	colaDePrioridadDistanciasIndicesMinima colaDePrioridadMinimaDeDistancias = colaDePrioridadDistanciasIndicesMinima(distanciasConIndices.begin(), distanciasConIndices.end(), ComparadorDeDistancias());

	for (int i = 0; i < _k; i++) {
		kElementosMasCercanos[i] = colaDePrioridadMinimaDeDistancias.top().second;
		colaDePrioridadMinimaDeDistancias.pop();
	}

	return kElementosMasCercanos;
}

tipoClase Knn::obtenerClaseDeElementoConMayorFrecuencia(const vector<int> &indicesDeElementos)const {
	assert(indicesDeElementos.size() > 0);
	int n = indicesDeElementos.size();
	vector<int> cantidadDeAparicionesPorClase = vector<int>(_maximoValorDeClase, 0);
	tipoClase claseConMayorApariciones = tipoClase();
	int mayorCantidadDeApariciones = -1;

	int indiceDeElementoActual = 0;
	tipoClase claseActual = tipoClase();
	for (int i = 0; i < n; i++) {
		indiceDeElementoActual = indicesDeElementos[i];
		claseActual = _clasesPorElemento[indiceDeElementoActual];
		cantidadDeAparicionesPorClase[claseActual]++;

		if (cantidadDeAparicionesPorClase[claseActual] > mayorCantidadDeApariciones) {
			mayorCantidadDeApariciones = cantidadDeAparicionesPorClase[claseActual];
			claseConMayorApariciones = claseActual;
		}
	}

	return claseConMayorApariciones;
}