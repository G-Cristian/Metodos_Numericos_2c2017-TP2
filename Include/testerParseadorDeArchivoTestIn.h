#ifndef _TESTER_PARSEADOR_DE_ARCHIVO_TEST_IN_H_
#define _TESTER_PARSEADOR_DE_ARCHIVO_TEST_IN_H_

#include <vector>
#include <string>

using namespace std;

class TesterParseadorDeArchivoTestIn {
public:
	TesterParseadorDeArchivoTestIn();
	~TesterParseadorDeArchivoTestIn();

	//devuelve los test incorrectos o vector vacio si todos fueron correctos.
	vector<string> correrTests()const;
	bool testKDeKnnCorrecto()const;
	bool testAlfaDePcaCorrecto()const;
	bool testKDeKFoldCorrecto()const;
	bool testClasesTestsCorrectas()const;
	bool testImagenesTestsCorrectas()const;
	bool testClasesEntrenamientoCorrectas()const;
	bool testImagenesEntrenamientoCorrectas()const;
};

#endif // !_TESTER_PARSEADOR_DE_ARCHIVO_TEST_IN_H_
