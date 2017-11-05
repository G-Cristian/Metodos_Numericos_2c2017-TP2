#ifndef _TESTER_PARSEADOR_DE_ARCHIVO_CON_CLASES_IMAGENES_H_
#define _TESTER_PARSEADOR_DE_ARCHIVO_CON_CLASES_IMAGENES_H_

#include <vector>
#include <string>

using namespace std;

class TesterParseadorDeArchivoConClasesImagenes {
public:
	TesterParseadorDeArchivoConClasesImagenes();
	~TesterParseadorDeArchivoConClasesImagenes();

	//devuelve los test incorrectos o vector vacio si todos fueron correctos.
	vector<string> correrTests()const;
	bool testCantidadDePixelsPorImagenCorrectoLeyendoArchivoDeCatedra_traincsv()const;
	bool testCantidadDeClasesIgualACantidadDeImagenesLeyendoArchivoDeCatedra_traincsv()const;
	bool testParsearCuatroClasesImagenesDeArchivo_test1csv()const;

	template<class T>
	static bool vectoresIguales(const vector<T> &v1, const vector<T> &v2) {
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
	template<class T>
	static bool vectoresDeVectoresIguales(const vector<vector<T> > &v1, const vector<vector<T> > &v2) {
		bool res = v1.size() == v2.size();
		if (!res)
			return res;

		for (int i = 0; i < v1.size(); i++) {
			if (!vectoresIguales(v1[i], v2[i])) {
				res = false;
				break;
			}
		}

		return res;
	}
};

#endif // !_TESTER_PARSEADOR_DE_CSV_
