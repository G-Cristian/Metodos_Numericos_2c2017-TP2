#include "../Include/parseadorDeArchivoTestIn.h"
#include "../Include/parseadorDeArchivoConClasesImagenes.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>

using namespace std;

ParseadorDeArchivoTestIn::ParseadorDeArchivoTestIn(const string &nombreArchivo, const string &nombreArchivoDeImagenes) {
	ifstream archivoTest(nombreArchivo);
	string rutaDeTrainCSV;
	if (archivoTest.is_open()) {
		leerEncabezado(archivoTest, rutaDeTrainCSV);
		cargarClasesImagenes(rutaDeTrainCSV, nombreArchivoDeImagenes);
		leerParticiones(archivoTest);

		archivoTest.close();
	}
}

ParseadorDeArchivoTestIn::~ParseadorDeArchivoTestIn() {

}

//Devuelve un par con las clases de training en la primera posicion y las imagenes de training en la segunda.
pair<vector<int>, vector<vector<int>>> ParseadorDeArchivoTestIn::dameClasesImagenesDeTrainingParaElIesimoFold(int i)const {
	return dameClasesImagenesDeTestOTrainingParaElIesimoFold(i, tipoEntrenamiento);
}

//Devuelve un par con las clases de test en la primera posicion y las imagenes de test en la segunda.
pair<vector<int>, vector<vector<int>>>  ParseadorDeArchivoTestIn::dameClasesImagenesDeTestParaElIesimoFold(int i)const {
	return dameClasesImagenesDeTestOTrainingParaElIesimoFold(i, tipoTest);
}

pair<vector<int>, vector<vector<int> > > ParseadorDeArchivoTestIn::dameClasesImagenesDeTestOTrainingParaElIesimoFold(int i, bool(* condicion)(int tipo))const {
	assert(0 <= i && i < _kDeKFold);
	vector<int> clases;
	vector<vector<int> > imagenes;
	const list<int> &particion = _particiones[i];
	int indiceImagen = 0;
	for (list<int>::const_iterator it = particion.begin(); it != particion.end(); it++) {
		if (condicion(*it)) {
			clases.push_back(_clases[indiceImagen]);
			imagenes.push_back(_imagenes[indiceImagen]);
		}

		indiceImagen++;
	}

	return pair<vector<int>, vector<vector<int> > >(clases, imagenes);
}

void ParseadorDeArchivoTestIn::leerEncabezado(ifstream &archivo, string &outNutaArchivoTrainCSV) {
	string aux;
	getline(archivo, aux);
	istringstream iss(aux);
	iss >> outNutaArchivoTrainCSV >> _kDeKnn >> _alfaDePCA >> _kDeKFold;
}

void ParseadorDeArchivoTestIn::cargarClasesImagenes(const string &rutaDeARchivoTrainCSV, const string &nombreArchivoDeImagenes) {
	ParseadorDeArchivoConClasesImagenes pdACCI = ParseadorDeArchivoConClasesImagenes();
	pair <vector<int>, vector<vector<int> > > clasesImagenes = pdACCI.parsearArchivoConClasesImagenes(rutaDeARchivoTrainCSV + nombreArchivoDeImagenes);

	_clases = clasesImagenes.first;
	_imagenes = clasesImagenes.second;
}

void ParseadorDeArchivoTestIn::leerParticiones(ifstream &archivo) {
	string lineaParticion;
	while (getline(archivo, lineaParticion)) {
		leerParticion(lineaParticion);
	}

	assert(_particiones.size() == _kDeKFold);
}

void ParseadorDeArchivoTestIn::leerParticion(const string &lineaParticion) {
	istringstream iss(lineaParticion);
	int n;
	list<int> particion = list<int>();
	while (iss >> n) {
		particion.push_back(n);
	}

	assert(particion.size() == _imagenes.size());

	_particiones.push_back(particion);
}

bool ParseadorDeArchivoTestIn::tipoTest(int tipo) {
	return tipo == 0;
}

bool ParseadorDeArchivoTestIn::tipoEntrenamiento(int tipo) {
	return !tipoTest(tipo);
}