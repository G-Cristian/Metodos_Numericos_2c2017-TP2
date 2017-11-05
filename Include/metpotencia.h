#include "matriz.h"
#include <utility>

//using namespace std;
template <class T>
Matriz<T> vectorRandomMetodoPotencia(int &cantFilas){
	Matriz<T> randomVector = Matriz<T>(cantFilas, 1, 0.0);
	int i = 0;
	while(i < cantFilas){
			randomVector[i][0] = rand() % 100 + 1;
		i++;
	}
	return randomVector;
}

/*Metodo de Potencia 1 : uso cantidad de iteraciones fija para aproximar autovector*/
 template <class T>
 std::pair<T, Matriz<T> > MetodoPotenciaIteracionesFijas(const Matriz<T> &M, int cantIter){
 	int filasM = Matriz<T>::M.alto();
 	Matriz<T> aprox_autovector = vectorRandomMetodoPotencia<T>(filasM);
 	int i = 0;

 	while(i < cantIter){

 		aprox_autovector =  M*aprox_autovector;
 		T norma_vector = 1/aprox_autovector.Matriz<T>::norma();
 		aprox_autovector = aprox_autovector*(norma_vector);

 		i++;
 	}

 	T aprox_autovalor = (aprox_autovector.Matriz<T>::transpuesta()*M*aprox_autovector)/(aprox_autovector.Matriz<T>::transpuesta()*aprox_autovector);

 	std::pair<T, Matriz<T>> autovector_con_autovalor = std::make_pair(aprox_autovalor, aprox_autovector);

 	return autovector_con_autovalor;
 }  

/*Metodo de Potencia 2 : itero hasta que la diferencia de la norma entre dos iteraciones consecutivas 
                        sea menor a cierto epsilon pasado como parametro*/

 template <class T>
 std::pair<T, Matriz<T> > MetodoPotenciaConvergencia(const Matriz<T> &M, T &epsilonConvergencia){
	int filasM = M.alto();
	Matriz<T> aprox_autovector = vectorRandomMetodoPotencia<T>(filasM);
 	T distancia_aproximaciones_consecutivas = epsilonConvergencia;
 	Matriz<T> iteracion_anterior = aprox_autovector;

 	while(distancia_aproximaciones_consecutivas >= epsilonConvergencia){
 		iteracion_anterior = aprox_autovector;
 		aprox_autovector =  M*aprox_autovector;
 		T norma_vector = 1/aprox_autovector.Matriz<T>::norma();
 		aprox_autovector = aprox_autovector*(norma_vector);

 		distancia_aproximaciones_consecutivas = (aprox_autovector-iteracion_anterior).norma();
 	}

 	T aprox_autovalor = (aprox_autovector.Matriz<T>::transpuesta()*M*aprox_autovector)[0][0]/(aprox_autovector.Matriz<T>::transpuesta()*aprox_autovector)[0][0];

 	std::pair<T, Matriz<T>> autovector_con_autovalor = std::make_pair(aprox_autovalor, aprox_autovector);

 	return autovector_con_autovalor; 		

 }