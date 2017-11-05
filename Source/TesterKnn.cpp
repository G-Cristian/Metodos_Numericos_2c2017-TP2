#include "../Include/TesterKnn.h"
#include "../Include/knn.h"

TesterKnn::TesterKnn() {

}

TesterKnn::~TesterKnn() {

}

//devuelve los test incorrectos o vector vacio si todos fueron correctos.
vector<string> TesterKnn::correrTests()const{
	vector<string> testsIncorrectos = vector<string>();

	if (!testDistanciaCuadradaEntreE1YE2Correcta()) {
		testsIncorrectos.push_back("testDistanciaCuadradaEntreE1YE2Correcta");
	}

	if (!testObtenerDistanciasCuadradasConElemento()) {
		testsIncorrectos.push_back("testObtenerDistanciasCuadradasConElemento");
	}

	if (!testObtenerKElementosMasCercanosConKIgualAUnoYLaMenorDistanciaEsConElPrimerElemento()) {
		testsIncorrectos.push_back("testObtenerKElementosMasCercanosConKIgualAUnoYLaMenorDistanciaEsConElPrimerElemento");
	}

	if (!testObtenerKElementosMasCercanosConKIgualAUnoYLaMenorDistanciaEsConElUltimoElemento()) {
		testsIncorrectos.push_back("testObtenerKElementosMasCercanosConKIgualAUnoYLaMenorDistanciaEsConElUltimoElemento");
	}

	if (!testObtenerKElementosMasCercanosConKIgualACantidadDeElementos()) {
		testsIncorrectos.push_back("testObtenerKElementosMasCercanosConKIgualACantidadDeElementos");
	}

	if (!testObtenerClaseDeElementoConMayorFrecuenciaConKIgualAUno()) {
		testsIncorrectos.push_back("testObtenerClaseDeElementoConMayorFrecuenciaConKIgualAUno");
	}

	if (!testObtenerClaseDeElementoConMayorFrecuenciaConKIgualACantidadDeElementos()) {
		testsIncorrectos.push_back("testObtenerClaseDeElementoConMayorFrecuenciaConKIgualACantidadDeElementos");
	}

	if (!testClasificarElementoConKIgualAUno()) {
		testsIncorrectos.push_back("testClasificarElementoConKIgualAUno");
	}

	if (!testClasificarElementoConKIgualACantidadDeElementos()) {
		testsIncorrectos.push_back("testClasificarElementoConKIgualACantidadDeElementos");
	}

	return testsIncorrectos;
}

bool TesterKnn::testDistanciaCuadradaEntreE1YE2Correcta() const{
	vector<double> e1 = vector<double>();
	e1.push_back(1);
	e1.push_back(2);
	e1.push_back(3);

	vector<double> e2 = vector<double>();
	e2.push_back(3);
	e2.push_back(1);
	e2.push_back(4);

	vector<vector<double> > elementos = vector<vector<double> >();
	elementos.push_back(e1);
	Knn knn = Knn(1, elementos, vector<int>(1), 4);

	double distanciaAlCuadrado = (1 - 3)*(1 - 3) + (2 - 1)*(2 - 1) + (3 - 4)*(3 - 4);
	return knn.distanciaCuadradaEntreE1YE2(e1, e2) == distanciaAlCuadrado;
}

bool TesterKnn::testObtenerDistanciasCuadradasConElemento()const {
	vector<double> e1 = vector<double>();
	e1.push_back(1);
	e1.push_back(2);
	e1.push_back(3);

	vector<double> e2 = vector<double>();
	e2.push_back(3);
	e2.push_back(1);
	e2.push_back(4);

	vector<double> e3 = vector<double>();
	e3.push_back(2);
	e3.push_back(2);
	e3.push_back(4);

	vector<vector<double> > elementos = vector<vector<double> >();
	elementos.push_back(e1);
	elementos.push_back(e2);
	Knn knn = Knn(1, elementos, vector<int>(2), 4);

	vector<pair<double, int> > distancias = knn.obtenerDistanciasCuadradasConElemento(e3);

	vector<pair<double, int> > distanciasEsperadas = vector<pair<double, int> >();
	distanciasEsperadas.push_back( pair<double, int> ( (1 - 2)*(1 - 2) + (2 - 2)*(2 - 2) + (3 - 4)*(3 - 4) , 0));
	distanciasEsperadas.push_back(pair<double, int>((2 - 3)*(2 - 3) + (2 - 1)*(2 - 1) + (4 - 4)*(4 - 4), 1));

	return vectoresIguales(distancias, distanciasEsperadas);
}

bool TesterKnn::testObtenerKElementosMasCercanosConKIgualAUnoYLaMenorDistanciaEsConElPrimerElemento()const {
	vector<double> e1 = vector<double>();
	e1.push_back(1);
	e1.push_back(2);
	e1.push_back(3);

	vector<double> e2 = vector<double>();
	e2.push_back(3);
	e2.push_back(1);
	e2.push_back(4);

	vector<double> e3 = vector<double>();
	e3.push_back(2);
	e3.push_back(2);
	e3.push_back(4);

	vector<double> e4 = vector<double>();
	e4.push_back(10);
	e4.push_back(10);
	e4.push_back(10);

	vector<double> e5 = vector<double>();
	e5.push_back(9);
	e5.push_back(9);
	e5.push_back(9);

	vector<vector<double> > elementos = vector<vector<double> >();
	elementos.push_back(e1);
	elementos.push_back(e2);
	elementos.push_back(e3);
	elementos.push_back(e4);


	Knn knn = Knn(1, elementos, vector<int>(4), 4);

	vector<pair<double, int> > distancias = knn.obtenerDistanciasCuadradasConElemento(e5);

	vector<int> kElementosMasCercanos = knn.obtenerIndicesDeKElementosMasCercanos(distancias);

	vector<int> kElementosMasCercanosEsperado = vector<int>();
	kElementosMasCercanosEsperado.push_back(3);

	return vectoresIguales(kElementosMasCercanos, kElementosMasCercanosEsperado);
}

bool TesterKnn::testObtenerKElementosMasCercanosConKIgualAUnoYLaMenorDistanciaEsConElUltimoElemento()const {
	vector<double> e1 = vector<double>();
	e1.push_back(1);
	e1.push_back(2);
	e1.push_back(3);

	vector<double> e2 = vector<double>();
	e2.push_back(3);
	e2.push_back(1);
	e2.push_back(4);

	vector<double> e3 = vector<double>();
	e3.push_back(2);
	e3.push_back(2);
	e3.push_back(4);

	vector<double> e4 = vector<double>();
	e4.push_back(10);
	e4.push_back(10);
	e4.push_back(10);

	vector<double> e5 = vector<double>();
	e5.push_back(1);
	e5.push_back(2);
	e5.push_back(3);

	vector<vector<double> > elementos = vector<vector<double> >();
	elementos.push_back(e1);
	elementos.push_back(e2);
	elementos.push_back(e3);
	elementos.push_back(e4);


	Knn knn = Knn(1, elementos, vector<int>(4), 4);

	vector<pair<double, int> > distancias = knn.obtenerDistanciasCuadradasConElemento(e5);

	vector<int> kElementosMasCercanos = knn.obtenerIndicesDeKElementosMasCercanos(distancias);

	vector<int> kElementosMasCercanosEsperado = vector<int>();
	kElementosMasCercanosEsperado.push_back(0);

	return vectoresIguales(kElementosMasCercanos, kElementosMasCercanosEsperado);
}

bool TesterKnn::testObtenerKElementosMasCercanosConKIgualACantidadDeElementos()const {
	vector<double> e1 = vector<double>();
	e1.push_back(1);
	e1.push_back(2);
	e1.push_back(3);

	vector<double> e2 = vector<double>();
	e2.push_back(3);
	e2.push_back(1);
	e2.push_back(4);

	vector<double> e3 = vector<double>();
	e3.push_back(2);
	e3.push_back(2);
	e3.push_back(4);

	vector<double> e4 = vector<double>();
	e4.push_back(10);
	e4.push_back(10);
	e4.push_back(10);

	vector<double> e5 = vector<double>();
	e5.push_back(3);
	e5.push_back(2);
	e5.push_back(3);

	vector<vector<double> > elementos = vector<vector<double> >();
	elementos.push_back(e1);
	elementos.push_back(e2);
	elementos.push_back(e3);
	elementos.push_back(e4);


	Knn knn = Knn(4, elementos, vector<int>(4), 4);

	vector<pair<double, int> > distancias = knn.obtenerDistanciasCuadradasConElemento(e5);

	vector<int> kElementosMasCercanos = knn.obtenerIndicesDeKElementosMasCercanos(distancias);

	//dist e5 con e1 = ||(3,2,3) - (1,2,3)||^2 = 4
	//dist e5 con e2 = ||(3,2,3) - (3,1,4)||^2 = 2
	//dist e5 con e3 = ||(3,2,3) - (2,2,4)||^2 = 2
	//dist e5 con e3 = ||(3,2,3) - (10,10,10)||^2 = (-7)*(-7) + (-8)*(-8) + (-7)*(-7) = 49 + 64 + 49 = 162
	vector<int> kElementosMasCercanosEsperado1 = vector<int>();
	kElementosMasCercanosEsperado1.push_back(1);
	kElementosMasCercanosEsperado1.push_back(2);
	kElementosMasCercanosEsperado1.push_back(0);
	kElementosMasCercanosEsperado1.push_back(3);

	vector<int> kElementosMasCercanosEsperado2 = vector<int>();
	kElementosMasCercanosEsperado2.push_back(2);
	kElementosMasCercanosEsperado2.push_back(1);
	kElementosMasCercanosEsperado2.push_back(0);
	kElementosMasCercanosEsperado2.push_back(3);

	return vectoresIguales(kElementosMasCercanos, kElementosMasCercanosEsperado1) || vectoresIguales(kElementosMasCercanos, kElementosMasCercanosEsperado2);
}

bool TesterKnn::testObtenerClaseDeElementoConMayorFrecuenciaConKIgualAUno()const {
	vector<double> e1 = vector<double>();
	e1.push_back(1);
	e1.push_back(2);
	e1.push_back(3);

	vector<double> e2 = vector<double>();
	e2.push_back(3);
	e2.push_back(1);
	e2.push_back(4);

	vector<double> e3 = vector<double>();
	e3.push_back(2);
	e3.push_back(2);
	e3.push_back(4);

	vector<double> e4 = vector<double>();
	e4.push_back(10);
	e4.push_back(10);
	e4.push_back(10);

	vector<double> e5 = vector<double>();
	e5.push_back(1);
	e5.push_back(2);
	e5.push_back(3);

	vector<vector<double> > elementos = vector<vector<double> >();
	elementos.push_back(e1);
	elementos.push_back(e2);
	elementos.push_back(e3);
	elementos.push_back(e4);


	vector<int> clases = vector<int>();
	clases.push_back(1);
	clases.push_back(0);
	clases.push_back(0);
	clases.push_back(0);

	Knn knn = Knn(1, elementos, clases, 2);

	vector<pair<double, int> > distancias = knn.obtenerDistanciasCuadradasConElemento(e5);
	vector<int> kElementosMasCercanos = knn.obtenerIndicesDeKElementosMasCercanos(distancias);
	int clase = knn.obtenerClaseDeElementoConMayorFrecuencia(kElementosMasCercanos);

	int claseEsperada = 1;

	return clase == claseEsperada;
}

bool TesterKnn::testObtenerClaseDeElementoConMayorFrecuenciaConKIgualACantidadDeElementos()const {
	vector<double> e1 = vector<double>();
	e1.push_back(1);
	e1.push_back(2);
	e1.push_back(3);

	vector<double> e2 = vector<double>();
	e2.push_back(3);
	e2.push_back(1);
	e2.push_back(4);

	vector<double> e3 = vector<double>();
	e3.push_back(2);
	e3.push_back(2);
	e3.push_back(4);

	vector<double> e4 = vector<double>();
	e4.push_back(10);
	e4.push_back(10);
	e4.push_back(10);

	vector<double> e5 = vector<double>();
	e5.push_back(3);
	e5.push_back(2);
	e5.push_back(3);

	vector<vector<double> > elementos = vector<vector<double> >();
	elementos.push_back(e1);
	elementos.push_back(e2);
	elementos.push_back(e3);
	elementos.push_back(e4);

	vector<int> clases = vector<int>();
	clases.push_back(2);
	clases.push_back(1);
	clases.push_back(0);
	clases.push_back(2);

	Knn knn = Knn(4, elementos, clases, 3);

	//dist e5 con e1 = ||(3,2,3) - (1,2,3)||^2 = 4
	//dist e5 con e2 = ||(3,2,3) - (3,1,4)||^2 = 2
	//dist e5 con e3 = ||(3,2,3) - (2,2,4)||^2 = 2
	//dist e5 con e3 = ||(3,2,3) - (10,10,10)||^2 = (-7)*(-7) + (-8)*(-8) + (-7)*(-7) = 49 + 64 + 49 = 162
	vector<pair<double, int> > distancias = knn.obtenerDistanciasCuadradasConElemento(e5);
	vector<int> kElementosMasCercanos = knn.obtenerIndicesDeKElementosMasCercanos(distancias);
	int clase = knn.obtenerClaseDeElementoConMayorFrecuencia(kElementosMasCercanos);

	int claseEsperada = 2;

	return clase == claseEsperada;
}

bool TesterKnn::testClasificarElementoConKIgualAUno()const {
	vector<double> e1 = vector<double>();
	e1.push_back(1);
	e1.push_back(2);
	e1.push_back(3);

	vector<double> e2 = vector<double>();
	e2.push_back(3);
	e2.push_back(1);
	e2.push_back(4);

	vector<double> e3 = vector<double>();
	e3.push_back(2);
	e3.push_back(2);
	e3.push_back(4);

	vector<double> e4 = vector<double>();
	e4.push_back(10);
	e4.push_back(10);
	e4.push_back(10);

	vector<double> e5 = vector<double>();
	e5.push_back(1);
	e5.push_back(2);
	e5.push_back(3);

	vector<vector<double> > elementos = vector<vector<double> >();
	elementos.push_back(e1);
	elementos.push_back(e2);
	elementos.push_back(e3);
	elementos.push_back(e4);


	vector<int> clases = vector<int>();
	clases.push_back(1);
	clases.push_back(0);
	clases.push_back(0);
	clases.push_back(0);

	Knn knn = Knn(1, elementos, clases, 2);

	int clase = knn.clasificarElemento(e5);

	int claseEsperada = 1;

	return clase == claseEsperada;
}

bool TesterKnn::testClasificarElementoConKIgualACantidadDeElementos()const {
	vector<double> e1 = vector<double>();
	e1.push_back(1);
	e1.push_back(2);
	e1.push_back(3);

	vector<double> e2 = vector<double>();
	e2.push_back(3);
	e2.push_back(1);
	e2.push_back(4);

	vector<double> e3 = vector<double>();
	e3.push_back(2);
	e3.push_back(2);
	e3.push_back(4);

	vector<double> e4 = vector<double>();
	e4.push_back(10);
	e4.push_back(10);
	e4.push_back(10);

	vector<double> e5 = vector<double>();
	e5.push_back(3);
	e5.push_back(2);
	e5.push_back(3);

	vector<vector<double> > elementos = vector<vector<double> >();
	elementos.push_back(e1);
	elementos.push_back(e2);
	elementos.push_back(e3);
	elementos.push_back(e4);


	vector<int> clases = vector<int>();
	clases.push_back(2);
	clases.push_back(1);
	clases.push_back(0);
	clases.push_back(2);

	Knn knn = Knn(4, elementos, clases, 3);

	//dist e5 con e1 = ||(3,2,3) - (1,2,3)||^2 = 4
	//dist e5 con e2 = ||(3,2,3) - (3,1,4)||^2 = 2
	//dist e5 con e3 = ||(3,2,3) - (2,2,4)||^2 = 2
	//dist e5 con e3 = ||(3,2,3) - (10,10,10)||^2 = (-7)*(-7) + (-8)*(-8) + (-7)*(-7) = 49 + 64 + 49 = 162

	int clase = knn.clasificarElemento(e5);

	int claseEsperada = 2;

	return clase == claseEsperada;
}