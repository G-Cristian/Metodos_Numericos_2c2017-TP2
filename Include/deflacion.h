#include "matriz.h"
#include <utility>



//Deflacion: Si λ1 y u1 son autovalor dominante y autovector de A y v es un vector tal que vt.u1 = 1; entonces, los autovalores
//de la matriz B = A − λ1 (u1vt) son: 0, λ2, . . . , λn (donde λi es autovalor de A)

template <class T>
Matriz<T> deflacion(Matriz<T> &A, const pair<T, Matriz<T> > &autovector_con_autovalor) {

	T autovalor = autovector_con_autovalor.first;
	Matriz<T> autovector = autovector_con_autovalor.second;
	Matriz<T> autovector_t = autovector_con_autovalor.second.Matriz<T>::transpuesta();

	Matriz<T> vi_x_vi_t = autovector * autovector_t; //autovector vi multiplicado por autovector vi transpuesto

	return A - (vi_x_vi_t*autovalor);
}