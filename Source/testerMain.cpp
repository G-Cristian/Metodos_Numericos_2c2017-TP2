#include <iostream>
#include <vector>
#include <string>

#include "../Include/TesterKnn.h"

using namespace std;

void mostrarTestsIncorrectos(const vector<string> &testIncorrectos);

int main() {
	TesterKnn testerKnn = TesterKnn();
	vector<string> testsKnnIncorrectos = testerKnn.correrTests();
	if (testsKnnIncorrectos.size() > 0) {
		cout << "Tests incorrectos de Knn." << endl << endl;
		mostrarTestsIncorrectos(testsKnnIncorrectos);
	}
	else {
		cout << "Tests Knn correctos." << endl << endl;
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