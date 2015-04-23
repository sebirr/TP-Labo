#ifndef CORREPOCOYO_H_
#define CORREPOCOYO_H_

#include <iostream>
#include <cassert>
using namespace std;

/* 
 * Se puede asumir que el tipo T tiene constructor por copia y operator==
 * No se puede asumir que el tipo T tenga operator=
 */
template<typename T>
class CorrePocoyo{

  public:

	/*
	 * Crea una nueva carrera
	 */	
	CorrePocoyo();

	/*
	 * Una vez copiada, ambas CorrePocoyos deben ser independientes, 
	 * es decir, cuando se borre una no debe borrar la otra.
	 */	
	CorrePocoyo(const CorrePocoyo<T>&);
	
	/*
	 * Acordarse de liberar toda la memoria!
	 */	 
	~CorrePocoyo();

	/*
	 * Agrega un nuevo corredor al CorrePocoyo. Lo agregará al final 
	 */
	void nuevoCorredor(const T&);
	
	/*
	 * Agrega un nuevo corredor al CorrePocoyo. El primer T es el corredor a agregar y lo hace delante del segundo
	 *
	 * PRE: Existe el segundo corredor 
	 */
	void nuevoCorredor(const T&, const T&);
	
	/*
	 * Elimina del pocoyo al que se envía
	 *
	 * PRE: Existe el corredor
	 */
	void seCansa(const T&);
	/*
	 * El corredor pasa al que está adelante 
	 *
	 * PRE: Existe un corredor delante de él y T es un corredor 
	 */
	void sobrepasar(const T&);
	
	/*
	 * Devuelve el corredor que está siendo filmado.
	 *
	 * PRE: Hay adeptos en la CorrePocoyo.
	 */
	const T& corredorFilmado() const;
	
    /*
	 * Devuelve el próximo elemento según el orden dado.
	 * Pasa a filmar al corredor de atás 
	 *
	 * PRE: Hay corredore en la CorrePocoyo.
	 */
	void filmarProxPerdedor();
	    /*
	 * Devuelve el próximo elemento según el orden dado.
	 * Pasa a filmar al corredor de adelante 
	 *
	 * PRE: Hay corredore en la CorrePocoyo.
	 */
	void filmarProxExitoso();
	
	/*
	 * Devuelve al Primero. 
	 *
	 * PRE: Hay elementos 
	 */
	const T& damePrimero() const;	

	/*
	 * Devuelve la posición del elemento pasado por parámetro. 
	 *
	 * PRE: Existe ese corredor 
	 */
	int damePosicion(const T&) const;	

	/*
	 * Devuelve el corredor de la posición. 
	 *
	 * PRE: Existe al menos esa cantidad de corredores en la carrera
	 */
	const T& dameCorredorEnPos(int) const;	




	/*
	 * Dice si la CorrePocoyo tiene o no corredores.
	 */
	bool esVacia() const;

	
	/*
	 * Devuelve la cantidad de corredores de la CorrePocoyo.
	 */
	int tamanio() const;	

	/*
	 * Devuelve true si las CorrePocoyos son iguales.
	 */
	bool operator==(const CorrePocoyo<T>&) const;	
	
	/*
	 * Debe mostrar la carrera por el ostream (y retornar el mismo).
	 * CorrePocoyo vacio: []
	 */
	ostream& mostrarCorrePocoyo(ostream&) const;
	
	//bool existeCorredor (const T&) const; // lo agregué, pues me sirve como auxiliar para los asserts (edit:nevermind, asumo que se cumplen las pre.)
	
  private:
	/*
	 * No se puede modificar esta funcion.
	 */
	CorrePocoyo<T>& operator=(const CorrePocoyo<T>& otra) {
		assert(false);
		return *this;
	}

	/*
	 * Aca va la implementación del nodo.
	 */
	struct Nodo {
		Nodo *siguiente;
		Nodo *anterior;
		T corredor;
		Nodo (const T &init) : corredor(init) {
			siguiente = NULL;
			anterior = NULL;
		}
	};
	Nodo *primero;
	Nodo *ultimo;
	int length;
	Nodo *camara;
};

template<class T>
ostream& operator<<(ostream& out, const CorrePocoyo<T>& a) {
	return a.mostrarCorrePocoyo(out);
}


// Implementación a hacer por los alumnos.
template<typename T>
CorrePocoyo<T>::CorrePocoyo(){
	this->length = 0;
	this->primero = NULL;
	this->ultimo = NULL;
	this->camara = NULL;
}

template<typename T>
CorrePocoyo<T>::CorrePocoyo(const CorrePocoyo<T>& b){
	this->length = 0;
	this->primero = NULL;
	this->ultimo = NULL;
	this->camara = NULL;
	if (b.length > 0) {
		this->nuevoCorredor(b.primero->corredor);
		int i = 1;
		Nodo *aux = b.primero->siguiente;
		while (i < b.length){
			this->nuevoCorredor(aux->corredor);
			if(b.camara == aux){
				this->camara = this->ultimo;
			}
		aux = aux->siguiente;
		i++;
		}
	}
}

template<typename T>
CorrePocoyo<T>::~CorrePocoyo(){
	Nodo *aux;
	aux = this->primero;
	for(int x = 0; x < this->length; x++){
		Nodo *aux2 = aux;
		aux = aux->siguiente;
		delete(aux2);
	}
}

template<typename T>
void CorrePocoyo<T>::nuevoCorredor(const T& corredor){
	Nodo *corredorNuevo = new Nodo(corredor);
	if(this->length == 0){
		this->primero = corredorNuevo;
		this->camara = this->primero;
	}else{
		corredorNuevo->anterior = this->ultimo;
		this->ultimo->siguiente = corredorNuevo;
	}
	this->ultimo = corredorNuevo;
	this->length++;
}

template<typename T>
void CorrePocoyo<T>::nuevoCorredor(const T& corredor, const T& corredorSig){
	assert(!this->esVacia());  //tiene que existir corredorSig 
	Nodo *aux;
	Nodo *aux2;
	Nodo *corredorNuevo = new Nodo(corredor);
	aux = this->primero;
	while(aux->corredor != corredorSig){
		aux = aux->siguiente;
	}
	aux2 = aux->anterior;
	aux->anterior = corredorNuevo;
	if (aux2 != NULL) {
		aux2->siguiente = corredorNuevo;
	}else{
		this->primero = corredorNuevo;
	}
	corredorNuevo->siguiente = aux;
	corredorNuevo->anterior = aux2;
	this->length++;
}

template<typename T>
void CorrePocoyo<T>::seCansa(const T& corredor){ //No está clara la camara. Adopté un método arbitrario
	assert(!this->esVacia()); //assert(existeCorredor(corredor));
	Nodo *aux;
	Nodo *aux2;
	aux = this->primero;
	while(aux->corredor != corredor){
		aux = aux->siguiente;
	}
	aux2 = aux->anterior;
	if (this->length == 1){
		this->primero = NULL;
		this->ultimo = NULL;
		this->camara = NULL;
	}else{
		if(aux2 != NULL){
			aux2->siguiente = aux->siguiente;
		}else{
			this->primero = aux->siguiente;
			this->primero->anterior = NULL;
		}
		if(aux->siguiente != NULL){
			aux->siguiente->anterior = aux2;
		}else{
			this->ultimo = aux2;
			this->ultimo->siguiente = NULL;
		}
	}
	this->camara = this->primero; //no aclara que tiene que pasar con la camara, para que se quede filmando a alguien voy a decir que filma al primero
	delete(aux);
	this->length--;
}

	template<typename T>
	void CorrePocoyo<T>::sobrepasar(const T& corredor){
		assert(!this->esVacia() && this->primero->corredor != corredor); //assert(existeCorredor(corredor)); 
		Nodo * aux = this->primero;										//edit: en realidad no hace falta, asumo que se cumplen precondiciones
		Nodo *aux2;
		while(aux->corredor != corredor){
			aux = aux->siguiente;
		}
		aux2 = aux->anterior;
		if(aux2 == this->primero){
			this->primero = aux;
			aux->anterior = NULL;
		} else{
			aux2->anterior->siguiente = aux;
			aux->anterior = aux2->anterior;
		}
		if(this->ultimo == aux){
			aux2->siguiente = NULL;
			this->ultimo = aux2;
		} else{
			aux->siguiente->anterior = aux2;
			aux2->siguiente = aux->siguiente;
		}
		aux->siguiente = aux2;
		aux2->anterior = aux;
}

	template<typename T>
	const T& CorrePocoyo<T>::corredorFilmado() const{
		assert(this->camara != NULL); //creo que se refiere a eso
		Nodo *aux = this->primero;
		while (this->camara != aux){
			aux = aux->siguiente;
		}
		return aux->corredor;
	}

	template<typename T>
	void CorrePocoyo<T>::filmarProxPerdedor(){      //en este y el siguiente resolví subespecificación con los if, porque sino no tiene sentido
		assert(!this->esVacia());
		Nodo *aux = this->primero;
		while (this->camara != aux){
			aux = aux->siguiente;
		}
		if (aux->siguiente != NULL) {
			this->camara = aux->siguiente;
		}
	}

	template<typename T>
	void CorrePocoyo<T>::filmarProxExitoso(){
		assert(!this->esVacia());
		Nodo *aux = this->primero;
		while (this->camara != aux){
			aux = aux->siguiente;
		}
		if (aux->anterior != NULL){
			this->camara = aux->anterior;
		}
	}

	template<typename T>
	const T& CorrePocoyo<T>::damePrimero() const{
		assert(!this->esVacia());
		return this->primero->corredor; //  ?!?
	}

	template<typename T>
	int CorrePocoyo<T>::damePosicion(const T& corredor) const{   //resolver loops eternos (edit: NO HACE FALTA. ASUMO QUE SE CUMPLE PRECONDICIÓN)
		assert(!this->esVacia()); //assert(existeCorredor(corredor));
		Nodo *aux = this->primero;
		int i= 1;
		while(aux->corredor != corredor){
			i++;
			aux = aux->siguiente;
		}
		return i;
	}

	template<typename T>
	const T& CorrePocoyo<T>::dameCorredorEnPos(int x) const{
		assert(this->length >= x); 
		Nodo *aux = this->primero;
		int i = 1;			//tambien puedo tomar el length
		while(i != x){
			aux = aux->siguiente;
			i++;
		}
		return aux->corredor;
	}

	template<typename T>
	bool CorrePocoyo<T>::esVacia() const{
		if(this->length == 0){
			return true;
		}else{
			return false;
		}
	}

	template<typename T>
	int CorrePocoyo<T>::tamanio() const{
		return this->length;
	}

	template<typename T>
	bool CorrePocoyo<T>::operator==(const CorrePocoyo<T>& b) const{ //camara hace falta?
		if (this->length != b.length) {
			return false;
		} else if(this->primero->corredor != b.primero->corredor){
			return false;
		} else if(this->ultimo->corredor != b.ultimo->corredor){
			return false;
		} else if(this->camara->corredor != b.camara->corredor){
			return false;
		}
		Nodo *correAux = this->primero;
		Nodo *bAux =b.primero;
		while(correAux->corredor == bAux->corredor && correAux != this->ultimo){
			correAux = correAux->siguiente;
			bAux = bAux->siguiente;
		}
		if(correAux->corredor != bAux->corredor){
			return false;
		} else {
			return true;
		}
	}
	template<typename T>
	ostream& CorrePocoyo<T>::mostrarCorrePocoyo(ostream& os) const {
	Nodo *aux = this->primero;

	os << "[";

	while (aux != NULL) {
		if (aux->siguiente != NULL){
			os << aux->corredor << ", ";
		} else {
			os << aux->corredor;
		}

		aux = aux->siguiente;
	}

	os << "]" ;
	return os;
}
/*	template<typename T>
	bool CorrePocoyo<T>::existeCorredor (const T& corredor) const{
		Nodo *aux = this->primero;
		int i = 0;
		while(aux != corredor && i < this.length){
			i++;
			aux = aux->siguiente;
		}
		if (aux->corredor == corredor){!this->esVacia
			return true;
		}else{
			return false;
		}
	}
*/
#endif //CORREPOCOYO_H_		

//PREGUNTAR.. filmarProxPerdedor y filmarProxExitoso, que pasa en en this->ultimo y this->primero respectivamente.