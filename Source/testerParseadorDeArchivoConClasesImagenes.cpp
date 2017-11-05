#include "../Include/testerParseadorDeArchivoConClasesImagenes.h"
#include "../Include/parseadorDeArchivoConClasesImagenes.h"

#include <iostream>
#include <fstream>

using namespace std;

TesterParseadorDeArchivoConClasesImagenes::TesterParseadorDeArchivoConClasesImagenes() {

}

TesterParseadorDeArchivoConClasesImagenes::~TesterParseadorDeArchivoConClasesImagenes() {

}

//devuelve los test incorrectos o vector vacio si todos fueron correctos.
vector<string> TesterParseadorDeArchivoConClasesImagenes::correrTests()const {
	vector<string> testsIncorrectos = vector<string>();

	if (!testCantidadDePixelsPorImagenCorrectoLeyendoArchivoDeCatedra_traincsv()) {
		testsIncorrectos.push_back("testCantidadDePixelsPorImagenCorrectoLeyendoArchivoDeCatedra_traincsv");
	}

	if (!testCantidadDeClasesIgualACantidadDeImagenesLeyendoArchivoDeCatedra_traincsv()) {
		testsIncorrectos.push_back("testCantidadDeClasesIgualACantidadDeImagenesLeyendoArchivoDeCatedra_traincsv");
	}

	if (!testParsearCuatroClasesImagenesDeArchivo_test1csv()) {
		testsIncorrectos.push_back("testParsearCuatroClasesImagenesDeArchivo_test1csv");
	}

	return testsIncorrectos;
}

bool TesterParseadorDeArchivoConClasesImagenes::testCantidadDePixelsPorImagenCorrectoLeyendoArchivoDeCatedra_traincsv()const {
	string nombreArchivo = "..//data//train.csv";
	ifstream archivo(nombreArchivo);

	if (!archivo.is_open())
		return false;

	ParseadorDeArchivoConClasesImagenes pdACCI = ParseadorDeArchivoConClasesImagenes();
	int cantidadDePixelsPorImagen = pdACCI.saltearEncabezado(archivo);
	int cantidadDePixelsPorImagenEsperado = 28 * 28;
	archivo.close();

	return cantidadDePixelsPorImagen == cantidadDePixelsPorImagenEsperado;
}

bool TesterParseadorDeArchivoConClasesImagenes::testCantidadDeClasesIgualACantidadDeImagenesLeyendoArchivoDeCatedra_traincsv()const {
	string nombreArchivo = "..//data//train.csv";

	ParseadorDeArchivoConClasesImagenes pdACCI = ParseadorDeArchivoConClasesImagenes();
	pair<vector<int>, vector<vector<int> > > clasesImagenes = pdACCI.parsearArchivoConClasesImagenes(nombreArchivo);

	return clasesImagenes.first.size() == clasesImagenes.second.size();
}

bool TesterParseadorDeArchivoConClasesImagenes::testParsearCuatroClasesImagenesDeArchivo_test1csv()const {
	string nombreArchivo = "..//data//test1.csv";
	ParseadorDeArchivoConClasesImagenes pdACCI = ParseadorDeArchivoConClasesImagenes();
	pair<vector<int>, vector<vector<int> > > clasesImagenes = pdACCI.parsearArchivoConClasesImagenes(nombreArchivo);
	
	vector<int> clasesEsperadas = vector<int>(5);
	clasesEsperadas[0] = 1;
	clasesEsperadas[1] = 1;
	clasesEsperadas[2] = 5;
	clasesEsperadas[3] = 6;
	clasesEsperadas[4] = 2;

	vector<vector<int> > imagenesEsperadas = vector<vector<int> >(5);
	imagenesEsperadas[0] = vector<int>(4);
	imagenesEsperadas[0][0] = 1;
	imagenesEsperadas[0][1] = 2;
	imagenesEsperadas[0][2] = 3;
	imagenesEsperadas[0][3] = 4;

	imagenesEsperadas[1] = vector<int>(4);
	imagenesEsperadas[1][0] = 5;
	imagenesEsperadas[1][1] = 6;
	imagenesEsperadas[1][2] = 7;
	imagenesEsperadas[1][3] = 8;

	imagenesEsperadas[2] = vector<int>(4);
	imagenesEsperadas[2][0] = 9;
	imagenesEsperadas[2][1] = 10;
	imagenesEsperadas[2][2] = 11;
	imagenesEsperadas[2][3] = 12;

	imagenesEsperadas[3] = vector<int>(4);
	imagenesEsperadas[3][0] = 13;
	imagenesEsperadas[3][1] = 14;
	imagenesEsperadas[3][2] = 15;
	imagenesEsperadas[3][3] = 16;

	imagenesEsperadas[4] = vector<int>(4);
	imagenesEsperadas[4][0] = 0;
	imagenesEsperadas[4][1] = 1;
	imagenesEsperadas[4][2] = 2;
	imagenesEsperadas[4][3] = 3;

	return vectoresIguales(clasesImagenes.first, clasesEsperadas) && vectoresDeVectoresIguales(clasesImagenes.second, imagenesEsperadas);
}