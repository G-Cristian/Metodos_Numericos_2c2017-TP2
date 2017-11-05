#include "../Include/testerParseadorDeArchivoTestIn.h"
#include "../Include/parseadorDeArchivoTestIn.h"
#include "../Include/testerParseadorDeArchivoConClasesImagenes.h"

TesterParseadorDeArchivoTestIn::TesterParseadorDeArchivoTestIn() {

}

TesterParseadorDeArchivoTestIn::~TesterParseadorDeArchivoTestIn() {

}

//devuelve los test incorrectos o vector vacio si todos fueron correctos.
vector<string> TesterParseadorDeArchivoTestIn::correrTests()const {
	vector<string> testsIncorrectos = vector<string>();

	if (!testKDeKnnCorrecto()) {
		testsIncorrectos.push_back("testKDeKnnCorrecto");
	}

	if (!testAlfaDePcaCorrecto()) {
		testsIncorrectos.push_back("testAlfaDePcaCorrecto");
	}

	if (!testKDeKFoldCorrecto()) {
		testsIncorrectos.push_back("testKDeKFoldCorrecto");
	}

	if (!testClasesTestsCorrectas()) {
		testsIncorrectos.push_back("testClasesTestsCorrectas");
	}

	if (!testImagenesTestsCorrectas()) {
		testsIncorrectos.push_back("testImagenesTestsCorrectas");
	}

	if (!testClasesEntrenamientoCorrectas()) {
		testsIncorrectos.push_back("testClasesEntrenamientoCorrectas");
	}

	if (!testImagenesEntrenamientoCorrectas()) {
		testsIncorrectos.push_back("testImagenesEntrenamientoCorrectas");
	}

	return testsIncorrectos;
}

bool TesterParseadorDeArchivoTestIn::testKDeKnnCorrecto()const {
	string nombreArchivoTestIn = "../data/test_de_parseadorDeTestIn1.in";
	string nombreArchivoDeEntrenamiento = "test1.csv";

	ParseadorDeArchivoTestIn pdATI = ParseadorDeArchivoTestIn(nombreArchivoTestIn, nombreArchivoDeEntrenamiento);
	int kDeKnnEsperado = 5;

	return pdATI.dameKDeKnn() == kDeKnnEsperado;
}

bool TesterParseadorDeArchivoTestIn::testAlfaDePcaCorrecto()const {
	string nombreArchivoTestIn = "../data/test_de_parseadorDeTestIn1.in";
	string nombreArchivoDeEntrenamiento = "test1.csv";

	ParseadorDeArchivoTestIn pdATI = ParseadorDeArchivoTestIn(nombreArchivoTestIn, nombreArchivoDeEntrenamiento);
	int alfaDePCAEsperado = 50;

	return pdATI.dameAlfaDePCA() == alfaDePCAEsperado;
}

bool TesterParseadorDeArchivoTestIn::testKDeKFoldCorrecto()const {
	string nombreArchivoTestIn = "../data/test_de_parseadorDeTestIn1.in";
	string nombreArchivoDeEntrenamiento = "test1.csv";

	ParseadorDeArchivoTestIn pdATI = ParseadorDeArchivoTestIn(nombreArchivoTestIn, nombreArchivoDeEntrenamiento);
	int kDeKFoldEsperado = 2;

	return pdATI.dameKDeKFold() == kDeKFoldEsperado;
}

bool TesterParseadorDeArchivoTestIn::testClasesTestsCorrectas()const {
	string nombreArchivoTestIn = "../data/test_de_parseadorDeTestIn1.in";
	string nombreArchivoDeEntrenamiento = "test1.csv";

	ParseadorDeArchivoTestIn pdATI = ParseadorDeArchivoTestIn(nombreArchivoTestIn, nombreArchivoDeEntrenamiento);
	vector<int> clasesEsperadas1 = vector<int>(2);
	clasesEsperadas1[0] = 1;
	clasesEsperadas1[1] = 5;

	vector<int> clasesEsperadas2 = vector<int>(3);
	clasesEsperadas2[0] = 1;
	clasesEsperadas2[1] = 6;
	clasesEsperadas2[2] = 2;

	return	TesterParseadorDeArchivoConClasesImagenes::vectoresIguales(clasesEsperadas1, pdATI.dameClasesImagenesDeTestParaElIesimoFold(0).first)
		&& TesterParseadorDeArchivoConClasesImagenes::vectoresIguales(clasesEsperadas2, pdATI.dameClasesImagenesDeTestParaElIesimoFold(1).first);
}

bool TesterParseadorDeArchivoTestIn::testImagenesTestsCorrectas()const {
	string nombreArchivoTestIn = "../data/test_de_parseadorDeTestIn1.in";
	string nombreArchivoDeEntrenamiento = "test1.csv";

	ParseadorDeArchivoTestIn pdATI = ParseadorDeArchivoTestIn(nombreArchivoTestIn, nombreArchivoDeEntrenamiento);

	vector<int> imagen1 = vector<int>(4);
	imagen1[0] = 1;
	imagen1[1] = 2;
	imagen1[2] = 3;
	imagen1[3] = 4;

	vector<int> imagen2 = vector<int>(4);
	imagen2[0] = 5;
	imagen2[1] = 6;
	imagen2[2] = 7;
	imagen2[3] = 8;

	vector<int> imagen3 = vector<int>(4);
	imagen3[0] = 9;
	imagen3[1] = 10;
	imagen3[2] = 11;
	imagen3[3] = 12;

	vector<int> imagen4 = vector<int>(4);
	imagen4[0] = 13;
	imagen4[1] = 14;
	imagen4[2] = 15;
	imagen4[3] = 16;

	vector<int> imagen5 = vector<int>(4);
	imagen5[0] = 0;
	imagen5[1] = 1;
	imagen5[2] = 2;
	imagen5[3] = 3;

	vector<vector<int> > imagenesEsperadas1 = vector<vector<int> >(2);
	imagenesEsperadas1[0] = imagen1;
	imagenesEsperadas1[1] = imagen3;

	vector<vector<int> >  imagenesEsperadas2 = vector<vector<int> >(3);
	imagenesEsperadas2[0] = imagen2;
	imagenesEsperadas2[1] = imagen4;
	imagenesEsperadas2[2] = imagen5;


	return	TesterParseadorDeArchivoConClasesImagenes::vectoresDeVectoresIguales(imagenesEsperadas1, pdATI.dameClasesImagenesDeTestParaElIesimoFold(0).second)
		&& TesterParseadorDeArchivoConClasesImagenes::vectoresDeVectoresIguales(imagenesEsperadas2, pdATI.dameClasesImagenesDeTestParaElIesimoFold(1).second);
}

bool TesterParseadorDeArchivoTestIn::testClasesEntrenamientoCorrectas()const {
	string nombreArchivoTestIn = "../data/test_de_parseadorDeTestIn1.in";
	string nombreArchivoDeEntrenamiento = "test1.csv";

	ParseadorDeArchivoTestIn pdATI = ParseadorDeArchivoTestIn(nombreArchivoTestIn, nombreArchivoDeEntrenamiento);

	vector<int> clasesEsperadas1 = vector<int>(3);
	clasesEsperadas1[0] = 1;
	clasesEsperadas1[1] = 6;
	clasesEsperadas1[2] = 2;

	vector<int> clasesEsperadas2 = vector<int>(2);
	clasesEsperadas2[0] = 1;
	clasesEsperadas2[1] = 5;


	return	TesterParseadorDeArchivoConClasesImagenes::vectoresIguales(clasesEsperadas1, pdATI.dameClasesImagenesDeTrainingParaElIesimoFold(0).first)
		&& TesterParseadorDeArchivoConClasesImagenes::vectoresIguales(clasesEsperadas2, pdATI.dameClasesImagenesDeTrainingParaElIesimoFold(1).first);
}

bool TesterParseadorDeArchivoTestIn::testImagenesEntrenamientoCorrectas()const {
	string nombreArchivoTestIn = "../data/test_de_parseadorDeTestIn1.in";
	string nombreArchivoDeEntrenamiento = "test1.csv";

	ParseadorDeArchivoTestIn pdATI = ParseadorDeArchivoTestIn(nombreArchivoTestIn, nombreArchivoDeEntrenamiento);

	vector<int> imagen1 = vector<int>(4);
	imagen1[0] = 1;
	imagen1[1] = 2;
	imagen1[2] = 3;
	imagen1[3] = 4;

	vector<int> imagen2 = vector<int>(4);
	imagen2[0] = 5;
	imagen2[1] = 6;
	imagen2[2] = 7;
	imagen2[3] = 8;

	vector<int> imagen3 = vector<int>(4);
	imagen3[0] = 9;
	imagen3[1] = 10;
	imagen3[2] = 11;
	imagen3[3] = 12;

	vector<int> imagen4 = vector<int>(4);
	imagen4[0] = 13;
	imagen4[1] = 14;
	imagen4[2] = 15;
	imagen4[3] = 16;

	vector<int> imagen5 = vector<int>(4);
	imagen5[0] = 0;
	imagen5[1] = 1;
	imagen5[2] = 2;
	imagen5[3] = 3;

	vector<vector<int> >  imagenesEsperadas1 = vector<vector<int> >(3);
	imagenesEsperadas1[0] = imagen2;
	imagenesEsperadas1[1] = imagen4;
	imagenesEsperadas1[2] = imagen5;

	vector<vector<int> > imagenesEsperadas2 = vector<vector<int> >(2);
	imagenesEsperadas2[0] = imagen1;
	imagenesEsperadas2[1] = imagen3;


	return	TesterParseadorDeArchivoConClasesImagenes::vectoresDeVectoresIguales(imagenesEsperadas1, pdATI.dameClasesImagenesDeTrainingParaElIesimoFold(0).second)
		&& TesterParseadorDeArchivoConClasesImagenes::vectoresDeVectoresIguales(imagenesEsperadas2, pdATI.dameClasesImagenesDeTrainingParaElIesimoFold(1).second);
}
