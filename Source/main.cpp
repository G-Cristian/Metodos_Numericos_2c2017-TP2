#include "../Include/ExcepcionAlLeerEntrada.h"
#include "../Include/matriz.h"
#include "../Include/knn.h"
#include "../Include/pca.h"
#include "../Include/parseadorDeArchivoTestIn.h"
#include <string>
#include <sstream>


using namespace std;

const double EPSILON = 0.0001;

enum Metodos { KNN_SIN_PCA = 0, PCA_CON_KNN = 1 };
enum ModoDeEjecucion {EJECUCION_TEST_NUESTRA = 0, EJECUCION_PEDIDA_POR_CATEDRA = 1};

struct ResultadosDeEntrada {
	ModoDeEjecucion modoDeEjecucion;
	Metodos metodo;

	//Para modo EJECUCION_TEST_NUESTRA
	string nombreDelArchivoPuntoInConLosDatos;
	string nombreDelArchivoPuntoOutConLosAutovaloresEsperados;

	//Para el modo EJECUCION_PEDIDA_POR_CATEDRA
	string nombreDelArchivoDeEntradaConDatosDeEntrenamiento;
	string nombreDelArchivoConDatosDeTestAClasificar;
	string nombreDelArchivoDeSalidaConLaClasificacionDeLosDatosDeTest;
};

ResultadosDeEntrada parsearEntrada(int argc, char*argv[]);
string armarMensajeDeError(const string &mensaje);
string mensajeConFormaDeEjecucion();

void ejecutarSegunNuestroModo(Metodos metodo, const string &archivoIn, const string &archivoOut);
void ejecutarSegunModoDeCatedra(Metodos metodo, const string &nombreArchivoDeEntrenamiento, const string &nombreArchivoTest, const string &nombreArchivoDeSalida);
Matriz<double> cantEsperadoObtenido(const vector<int>& esperados, const vector<int>& obtenidos);
vector<vector<double> > achicarImagenes(const PCA<double> &pca, const vector<vector<int> > &imagenes);

//Matriz<double> transformacionCaracteristica(vector<int>  &Imagen, pca<double> &p);
//pair<vector<int>, vector<vector<double> > > achicoDim(pair<vector<int>, vector<vector<int> > > &Imagenes, int alfa, int epsilonMetPotencia);

//Matriz<double> deVectorAMatriz(vector<int> &v);
//vector<double> deMatrizAVector(Matriz<double> &M);

template<class tipoRecivido, class tipoACastear>
vector<vector<tipoACastear>> castearVectorDeVector (const vector<vector<tipoRecivido>> &otro){
	vector<vector<tipoACastear>>ret = vector<vector<tipoACastear>>(otro.size());
	for (int i = 0; i < otro.size(); i++) {
		ret[i] = vector<tipoACastear>(otro[i].begin(), otro[i].end());
	}

	return ret;
}


int main( int argc, char* argv[] ){
	ResultadosDeEntrada datosDeEntrada;
	try {
		datosDeEntrada = parsearEntrada(argc, argv);

		if (datosDeEntrada.modoDeEjecucion == ModoDeEjecucion::EJECUCION_TEST_NUESTRA) {
			ejecutarSegunNuestroModo(datosDeEntrada.metodo, datosDeEntrada.nombreDelArchivoPuntoInConLosDatos, datosDeEntrada.nombreDelArchivoPuntoOutConLosAutovaloresEsperados);
		}
		else if (datosDeEntrada.modoDeEjecucion == ModoDeEjecucion::EJECUCION_PEDIDA_POR_CATEDRA) {
			ejecutarSegunModoDeCatedra(datosDeEntrada.metodo,
				datosDeEntrada.nombreDelArchivoDeEntradaConDatosDeEntrenamiento,
				datosDeEntrada.nombreDelArchivoConDatosDeTestAClasificar,
				datosDeEntrada.nombreDelArchivoDeSalidaConLaClasificacionDeLosDatosDeTest);
		}
	}
	catch (ExcepcionAlLeerEntrada e) {
		cout << "Error: " << e.what();
	}

	return 0;
}

ResultadosDeEntrada parsearEntrada(int argc, char*argv[]) {
	ResultadosDeEntrada resultado;

	if (argc < 3) {
		throw ExcepcionAlLeerEntrada(armarMensajeDeError("Faltan argumentos"));
	}
	string aux = argv[1];
	if (aux != "-m")
		throw ExcepcionAlLeerEntrada(armarMensajeDeError("Se esperaba  \'-m\' como primer parametro."));

	aux = argv[2];
	if(stoi(aux) != 0 && stoi(aux) != 1){
		throw ExcepcionAlLeerEntrada(armarMensajeDeError("ERROR, NO EXISTE METODO"));
	}
	resultado.metodo = (Metodos)stoi(aux);
	
	aux = argv[3];
	if (aux == "-i") {
		resultado.modoDeEjecucion = ModoDeEjecucion::EJECUCION_PEDIDA_POR_CATEDRA;
		aux = argv[4];
		resultado.nombreDelArchivoDeEntradaConDatosDeEntrenamiento = aux;

		aux = argv[5];
		if (aux != "-q")
			throw ExcepcionAlLeerEntrada(armarMensajeDeError("Se esperaba -q como tercer parametro."));

		aux = argv[6];
		resultado.nombreDelArchivoConDatosDeTestAClasificar = aux;

		aux = argv[7];
		if(aux != "-o")
			throw ExcepcionAlLeerEntrada(armarMensajeDeError("Se esperaba -o como cuarto parametro."));

		aux = argv[8];
		resultado.nombreDelArchivoDeSalidaConLaClasificacionDeLosDatosDeTest = aux;
	}
	else if (aux == "-in"){
		resultado.modoDeEjecucion = ModoDeEjecucion::EJECUCION_TEST_NUESTRA;
		aux = argv[4];
		resultado.nombreDelArchivoPuntoInConLosDatos = aux;

		aux = argv[5];
		if(aux != "-out")
			throw ExcepcionAlLeerEntrada(armarMensajeDeError("Se esperaba -out como tercer parametro."));

		aux = argv[6];
		resultado.nombreDelArchivoPuntoOutConLosAutovaloresEsperados = aux;
	}
	else {
		throw ExcepcionAlLeerEntrada(armarMensajeDeError("Se esperaba \'-i\' o \'-in\'  como segundo parametro."));
	}

	return resultado;
}

string armarMensajeDeError(const string &mensaje) {
	stringstream ss;
	ss << mensaje << endl << endl;
	ss << mensajeConFormaDeEjecucion();

	return ss.str();
}

string mensajeConFormaDeEjecucion() {
	stringstream formaDeEjecucion;

	formaDeEjecucion << "Forma de Ejecucion" << endl;
	formaDeEjecucion << "./tp2 -m <method> -i <train_set> -q <test_set> -o <classif>" << endl;
	formaDeEjecucion << endl;
	formaDeEjecucion << "<method> el metodo a ejecutar con posibilidad de extension (0: kNN, 1: PCA + kNN,... etc)" << endl;
	formaDeEjecucion << "<train_set> sera el nombre del archivo de entrada con los datos de entrenamiento." << endl;
	formaDeEjecucion << "<test_set> sera el nombre del archivo con los datos de test a clasificar" << endl;
	formaDeEjecucion << "<classif> el nombre del archivo de salida con la clasicacion de los datos de test de <test_set>" << endl;

	formaDeEjecucion << endl;
	formaDeEjecucion << "o" << endl;
	formaDeEjecucion << endl;
	formaDeEjecucion << "./tp2 -m <method> -in <datos> -out <esperado>" << endl;
	formaDeEjecucion << endl;
	formaDeEjecucion << "<method> el metodo a ejecutar con posibilidad de extension (0: kNN, 1: PCA + kNN,... etc)" << endl;
	formaDeEjecucion << "<datos> archivo \'.in\' formato: " << endl;
	formaDeEjecucion << "Primer linea: <path al directorio de data> <k-KNN> <alpha-PCA> <k-KFold>" << endl;
	formaDeEjecucion << "Se asume que la base de datos se llama \'train.csv\'" << endl;
	formaDeEjecucion << "Luego debe haber `k-KFold` l�neas de 42.000 valores cada una, uno por cada muestra de la base de entrenamiento," << endl;
	formaDeEjecucion << "donde un 1 indicar� que esa muestra se considera parte del entrenamiento," << endl;
	formaDeEjecucion << "y un 0 que se considera parte del test.Luego, de esta forma se pueden codificar las" << endl;
	formaDeEjecucion << "particiones realizadas por el `k-KFold` cross validation." << endl;
	formaDeEjecucion << "<esperado> archivo \'.out\' con formato: " << endl;
	formaDeEjecucion << "Debera estar compuestos de \'alpha-PCA\' * \'k-KFold\' l�neas correspondientes a los autovalores obtenidos al realizar PCA." << endl;
	formaDeEjecucion << "Para cada fold deber�n aparecer los \'alpha-PCA\' autovalores obtenidos, ordenados seg�n magintud decreciente" << endl;

	return formaDeEjecucion.str();
}

void ejecutarSegunNuestroModo(Metodos metodo, const string &archivoIn, const string &archivoOut) {

	/* medición del tiempo (WIP)
	std::clock_t tiempoInicial;
	double tiempoParcial = 0;
	double tiempoTotal = 0;
	*/

	ParseadorDeArchivoTestIn parseadorArchivoIn = ParseadorDeArchivoTestIn(archivoIn);
	//metodo es KNN
	if(metodo == 0){

		/* medición del tiempo (WIP)
		tiempoInicial = std::clock();
		*/

		int kdeKNN = parseadorArchivoIn.dameKDeKnn();
		int KdeFold = parseadorArchivoIn.dameKDeKFold();
		int i = 0;
		Matriz<double> promedioMatrices = Matriz<double>(10,10,0.0);
		while( i < KdeFold){
			pair<vector<int>, vector<vector<int> > > parDeClasesTrainingImagenes = parseadorArchivoIn.dameClasesImagenesDeTrainingParaElIesimoFold(i);
			Knn metKnn = Knn(kdeKNN, castearVectorDeVector<int,double>(parDeClasesTrainingImagenes.second), parDeClasesTrainingImagenes.first, 10);
			int j = 0;
			vector<int> obtenidos;
			while(j < parseadorArchivoIn.dameClasesImagenesDeTestParaElIesimoFold(i).second.size()){//cant imagenes test
				obtenidos.push_back(metKnn.clasificarElemento(castearVectorDeVector<int,double>(parseadorArchivoIn.dameClasesImagenesDeTestParaElIesimoFold(i).second)[j]));
				j++;
			}
			
			Matriz<double> mataux = cantEsperadoObtenido(parseadorArchivoIn.dameClasesImagenesDeTestParaElIesimoFold(i).first, obtenidos);
			std::cout<<"Fold "<< i << std::endl;
			mataux.mostrar();
			std::cout<<std::endl;
			promedioMatrices = promedioMatrices + mataux;

			/* medición del tiempo (WIP)
			tiempoParcial = ( std::clock() - tiempoInicial ) / (double) CLOCKS_PER_SEC;
			printf("Tiempo parcial (este pliegue): %4.6f\n", tiempoParcial);
			tiempoTotal = tiempoTotal + tiempoParcial;
			*/

			i++;
		}

		promedioMatrices = promedioMatrices*(1/KdeFold);
		std::cout<<"Fold promedio"<<std::endl;
		promedioMatrices.mostrar();
		std::cout<<std::endl;

				

	}else{
		int alpha = parseadorArchivoIn.dameAlfaDePCA();
		int kdeKNN = parseadorArchivoIn.dameKDeKnn();
		int KdeFold = parseadorArchivoIn.dameKDeKFold();
		int i = 0;
		Matriz<double> promedioMatrices = Matriz<double>(10,10,0.0);
		pair<vector<int>, vector<vector<int> > > auxTraining;
		pair<vector<int>, vector<vector<int> > > auxTest;
		while( i < KdeFold){
			auxTraining = parseadorArchivoIn.dameClasesImagenesDeTrainingParaElIesimoFold(i);
			auxTest = parseadorArchivoIn.dameClasesImagenesDeTestParaElIesimoFold(i);
			PCA<double> pca = PCA<double>(auxTraining.second, alpha, EPSILON);

			vector<vector<double> > imagenesTrainingAchicadas = achicarImagenes(pca, auxTraining.second);
			vector<vector<double> > imagenesTestAchicadas = achicarImagenes(pca, auxTest.second);
			Knn metKnn = Knn(kdeKNN, imagenesTrainingAchicadas, auxTraining.first, 10);

			vector<int> obtenidos;
			for (int j = 0; j < imagenesTestAchicadas.size(); j++) {
				obtenidos.push_back(metKnn.clasificarElemento(imagenesTestAchicadas[j]));
			}
			
			Matriz<int> mataux = cantEsperadoObtenido(auxTest.first, obtenidos);
			std::cout<<"Fold "<< i << std::endl;
			mataux.mostrar();
			std::cout<<std::endl;
			promedioMatrices = promedioMatrices + mataux;	
			i++; 
		} 
		promedioMatrices = promedioMatrices*1/KdeFold;
		std::cout<<"Fold promedio"<<std::endl;
		promedioMatrices.mostrar();
		std::cout<<std::endl;
	
	}

	//TODO
}

void ejecutarSegunModoDeCatedra(Metodos metodo, const string &nombreArchivoDeEntrenamiento, const string &nombreArchivoTest, const string &nombreArchivoDeSalida) {
	//TODO
}

//matriz que en posicion (i,j) i es el digito esperado y j es el obtenido, y lo que hay en M(i,j) es la cantidad de veces que se obtuvo j
Matriz<double> cantEsperadoObtenido(const vector<int>& esperados, const vector<int>& obtenidos){
	Matriz<double> resultadoEsperadosObtenidos = Matriz<double>(10, 10, 0.0);
	int i = 0;
	while(i < esperados.size()){
		resultadoEsperadosObtenidos[esperados[i]][obtenidos[i]]++;
		i++;
	}
	return resultadoEsperadosObtenidos;
}

vector<vector<double> > achicarImagenes(const PCA<double> &pca, const vector<vector<int> > &imagenes) {
	int cantidadDeImagenes = imagenes.size();

	vector<vector<double> > imagenesSalida = vector<vector<double> >(cantidadDeImagenes);
	for (int i = 0; i < cantidadDeImagenes; i++) {
		imagenesSalida[i] = pca.transformacionCaracteristica(imagenes[i]);
	}

	return imagenesSalida;
}

/*
Matriz<double> transformacionCaracteristica(vector<int>  &Imagen, pca<double> &p){
	return p.cambioDeBase()*deVectorAMatriz(Imagen);


}

pair<vector<int>, vector<vector<double> > > achicoDim(pair<vector<int>, vector<vector<int> > > &Imagenes, int alfa, int epsilonMetPotencia){
	PCA<double> metodoPCA = PCA<double>(Imagenes.second, alfa, epsilonMetPotencia);

	Matriz<int> ImagenesEnMatriz = Matriz<int>(Imagenes.second); 
	metodoPCA.metPCA(ImagenesEnMatriz, alfa, EPSILON);
	vector<int> clasesImagenes;
	vector<vector<double> > imagenesReducidas;
	pair<vector<int>, vector<vector<double> > > clasesImagenesReducidas;
	int i = 0;
	vector<double> imagenIesimaAchicada;
	while (i < ImagenesEnMatriz.ancho()){
		Matriz<double> transCaracteristica = transformacionCaracteristica(Imagenes.second[i], metodoPCA);
		imagenIesimaAchicada = deMatrizAVector(transCaracteristica);
		imagenesReducidas.push_back(imagenIesimaAchicada);
		clasesImagenes.push_back(Imagenes.first[i]);
		i++;
	}
	clasesImagenesReducidas = make_pair(clasesImagenes, imagenesReducidas);
	return clasesImagenesReducidas;
}

Matriz<double> deVectorAMatriz(vector<int> &v){
	Matriz<double> vector_pasado = Matriz<double>(v.size(), 1, 0.0);
	int i = 0;
	while(i < v.size()){
		vector_pasado[i][1] =v[i];
		i++;
	}
	return vector_pasado;
}

vector<double> deMatrizAVector(Matriz<double> &M){
	vector<double> matriz_pasada;
	int i = 0;
	while(i < M.alto()){
		matriz_pasada.push_back(M[i][1]);
		i++;
	}
	return matriz_pasada;
}
*/
