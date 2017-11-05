#ifndef _PARSEADOR_DE_ARCHIVO_CON_CLASES_IMAGENES_H_
#define _PARSEADOR_DE_ARCHIVO_CON_CLASES_IMAGENES_H_

#include <utility>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class ParseadorDeArchivoConClasesImagenes {
public:
	ParseadorDeArchivoConClasesImagenes();
	~ParseadorDeArchivoConClasesImagenes();

	//Devuelve un pair con un vector con las clases y un vector con las imagenes donde
	//la posicion i-esima del primer vector corresponde a la clase de la imagen en la posicion i-esima del segundo vector.
	pair<vector<int>, vector<vector<int> > > parsearArchivoConClasesImagenes(const string &nombreDeArchivo)const;
	//Devuelve la cantidad de pixels por imagen.
	int saltearEncabezado(ifstream &archivo)const;
	pair<vector<int>, vector<vector<int> > > leerClasesImagenes(ifstream &archivo, int cantidadDePixelsPorImagen)const;
	int leerClase(istringstream &iss)const;
	vector<int> leerImagen(istringstream &iss, int cantidadDePixelsPorImagen)const;
};

#endif // !_PARSEADOR_DE_CSV_H_
