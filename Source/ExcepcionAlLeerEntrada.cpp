#include "../Include/ExcepcionAlLeerEntrada.h"

ExcepcionAlLeerEntrada::ExcepcionAlLeerEntrada(const string mensaje) {
	_mensaje = mensaje;
}

ExcepcionAlLeerEntrada::~ExcepcionAlLeerEntrada() {

}

const char* ExcepcionAlLeerEntrada::what()const throw() {
	return _mensaje.c_str();
}