#ifndef _PARSEADOR_DE_ARCHIVO_TEST_IN_H_
#define _PARSEADOR_DE_ARCHIVO_TEST_IN_H_

#include <string>
#include <vector>
#include <list>
#include <utility>

using namespace std;

class ParseadorDeArchivoTestIn {
public:
	ParseadorDeArchivoTestIn(const string &nombreArchivo, const string &nombreArchivoDeImagenes = "train.csv");
	~ParseadorDeArchivoTestIn();

	inline int dameKDeKnn()const { return _kDeKnn; }
	inline int dameAlfaDePCA()const { return _alfaDePCA; }
	inline int dameKDeKFold()const { return _kDeKFold; }
	pair<vector<int>, vector<vector<int>>>  dameClasesImagenesDeTrainingParaElIesimoFold(int i)const;
	pair<vector<int>, vector<vector<int>>>  dameClasesImagenesDeTestParaElIesimoFold(int i)const;
private:
	void leerEncabezado(ifstream &archivo, string &outNutaArchivoTrainCSV);
	void cargarClasesImagenes(const string &rutaDeARchivoTrainCSV, const string &nombreArchivoDeImagenes);
	void leerParticiones(ifstream &archivo);
	void leerParticion(const string &lineaParticion);
	static bool tipoTest(int tipo);
	static bool tipoEntrenamiento(int tipo);

	pair<vector<int>, vector<vector<int> > > dameClasesImagenesDeTestOTrainingParaElIesimoFold(int i, bool(* condicion)(int tipo))const;

	int _kDeKnn;
	int _alfaDePCA;
	int _kDeKFold;
	vector<int> _clases;
	vector<vector<int> > _imagenes;
	vector<list<int> > _particiones;
};

#endif // !_PARSEADOR_DE_ARCHIVO_TEST_IN_H_
