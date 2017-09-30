#ifndef _KNN_H_
#define _KNN_H_

typedef vector<int> tipoElemento;
typedef int tipoClase;

class Knn{
public:
	Knn(int k, const vector<tipoElemento> &elementos, const vector<tipoClase> &clasesPorElemento, int cantidadDeClases);
	~Knn();
	tipoClase clasificarElemento(const tipoElemento &elemento) const;
	
private:
	int _k;
	vector<tipoElemento> _elementos;
	vector<tipoClase> _clasesPorElemento;
	int _cantidadDeClases;
};

#endif