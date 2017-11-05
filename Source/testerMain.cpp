#include <iostream>
#include <vector>
#include <string>

#include "../Include/TesterKnn.h"
#include "../Include/testerParseadorDeArchivoConClasesImagenes.h"
#include "../Include/testerParseadorDeArchivoTestIn.h"

using namespace std;

void mostrarTestsIncorrectos(const vector<string> &testIncorrectos);

int main() {
	TesterKnn testerKnn = TesterKnn();
	vector<string> testsIncorrectos = testerKnn.correrTests();
	if (testsIncorrectos.size() > 0) {
		cout << "Tests incorrectos de Knn." << endl << endl;
		mostrarTestsIncorrectos(testsIncorrectos);
	}
	else {
		cout << "Tests Knn correctos." << endl << endl;
	}

	TesterParseadorDeArchivoConClasesImagenes testerParseadorDeArchivoConClasesImagenes = TesterParseadorDeArchivoConClasesImagenes();
	testsIncorrectos = testerParseadorDeArchivoConClasesImagenes.correrTests();
	if (testsIncorrectos.size() > 0) {
		cout << "Tests incorrectos de ParseadorDeArchivoConClasesImagenes." << endl << endl;
		mostrarTestsIncorrectos(testsIncorrectos);
	}
	else {
		cout << "Tests ParseadorDeArchivoConClasesImagenes correctos." << endl << endl;
	}

	TesterParseadorDeArchivoTestIn testerParseadorDeArchivoTestIn = TesterParseadorDeArchivoTestIn();
	testsIncorrectos = testerParseadorDeArchivoTestIn.correrTests();
	if (testsIncorrectos.size() > 0) {
		cout << "Tests incorrectos de ParseadorDeArchivoTestIn." << endl << endl;
		mostrarTestsIncorrectos(testsIncorrectos);
	}
	else {
		cout << "Tests ParseadorDeArchivoTestIn correctos." << endl << endl;
	}
	

	return 0;
}

void mostrarTestsIncorrectos(const vector<string> &testIncorrectos) {
	int n = testIncorrectos.size();

	for (int i = 0; i < n; i++) {
		cout << testIncorrectos[i] << endl;
	}
	cout << endl;
}