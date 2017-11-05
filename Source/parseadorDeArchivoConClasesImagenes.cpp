#include "../Include/parseadorDeArchivoConClasesImagenes.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

ParseadorDeArchivoConClasesImagenes::ParseadorDeArchivoConClasesImagenes(){
}

ParseadorDeArchivoConClasesImagenes::~ParseadorDeArchivoConClasesImagenes() {
}

//Devuelve un pair con un vector con las clases y un vector con las imagenes donde
//la posicion i-esima del primer vector corresponde a la clase de la imagen en la posicion i-esima del segundo vector.
pair<vector<int>, vector<vector<int> > > ParseadorDeArchivoConClasesImagenes::parsearArchivoConClasesImagenes(const string &nombreDeArchivo)const{
	pair<vector<int>, vector<vector<int> > > clasesImagenes = pair<vector<int>, vector<vector<int> > >();
	ifstream archivo(nombreDeArchivo);

	if (archivo.is_open()) {
		int cantidadDePixelsPorImagenes = saltearEncabezado(archivo);
		clasesImagenes = leerClasesImagenes(archivo, cantidadDePixelsPorImagenes);

		archivo.close();
	}

	return clasesImagenes;
}

//Devuelve la cantidad de pixels por imagen.
int ParseadorDeArchivoConClasesImagenes::saltearEncabezado(ifstream &archivo)const {
	int cantidadDePixelsPorImagen = 0;
	string encabezado;
	getline(archivo, encabezado);
	istringstream iss(encabezado);
	string textoLabel;
	//lee el texto 'label'
	getline(iss, textoLabel, ',');
	string textoPixel;
	//lee los textos 'pixel0,pixel1,...'
	while (getline(iss, textoPixel, ',')) {
		cantidadDePixelsPorImagen++;
	}

	return cantidadDePixelsPorImagen;
}

pair<vector<int>, vector<vector<int> > > ParseadorDeArchivoConClasesImagenes::leerClasesImagenes(ifstream &archivo, int cantidadDePixelsPorImagen)const {
	pair<vector<int>, vector<vector<int> > > clasesImagenes = pair<vector<int>, vector<vector<int> > >();
	string lineaDeClaseImagen;

	while (getline(archivo, lineaDeClaseImagen)) {
		istringstream iss(lineaDeClaseImagen);
		clasesImagenes.first.push_back(leerClase(iss));
		clasesImagenes.second.push_back(leerImagen(iss, cantidadDePixelsPorImagen));
	}

	return clasesImagenes;
}
int ParseadorDeArchivoConClasesImagenes::leerClase(istringstream &iss)const {
	string clase;

	getline(iss, clase, ',');

	return stoi(clase);
}

vector<int> ParseadorDeArchivoConClasesImagenes::leerImagen(istringstream &iss, int cantidadDePixelsPorImagen)const {
	vector<int> imagen = vector<int>();
	imagen.reserve(cantidadDePixelsPorImagen);
	string numero;

	while (getline(iss, numero, ',')) {
		imagen.push_back(stoi(numero));
	}

	return imagen;
}