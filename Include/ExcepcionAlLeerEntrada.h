#ifndef _EXCEPCION_AL_LEER_ENTRADA_H_
#define _EXCEPCION_AL_LEER_ENTRADA_H_

#include <iostream>
#include <exception>
#include <string>

using namespace std;

class ExcepcionAlLeerEntrada:public exception {
public:
	ExcepcionAlLeerEntrada(const string mensaje);
	~ExcepcionAlLeerEntrada();

	virtual const char* what()const throw();
private:
	string _mensaje;
};

#endif // !_EXCEPCION_AL_LEER_ENTRADA_H_
