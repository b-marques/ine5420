#include "Elemento.hpp"

template<typename T>
class ListaEnc {

private:
	Elemento<T>* head;
	int size;
public:
	ListaEnc();
	~ListaEnc();
	int getSize();
	// inicio
	void adicionaNoInicio(const T& dado);
	T retiraDoInicio();
	void eliminaDoInicio();
	// posicao
	void adicionaNaPosicao(const T& dado, int pos);
	int posicao(const T& dado) const;
	T* posicaoMem(const T& dado) const;
	bool contem(const T& dado);
	T retiraDaPosicao(int pos);
	//fim
	void adiciona(const T& dado);
	T retira();
	// especifico
	T retiraEspecifico(const T& dado);
	void adicionaEmOrdem(const T& data);
	bool listaVazia() const;
	bool igual(T dado1, T dado2);
	bool maior(T dado1, T dado2);
	bool menor(T dado1, T dado2);
	void destroiLista();
};

template<typename T> ListaEnc<T>::ListaEnc() {
	size = 0;
	head = nullptr;

}

template<typename T> ListaEnc<T>::~ListaEnc() {
	destroiLista();
}

template<typename T> void ListaEnc<T>::adicionaNoInicio(const T& dado) {
	Elemento<T> *novoElemento = new Elemento<T>(dado, head);
	if (novoElemento != nullptr) {
		head = novoElemento;
		size += 1;
	} else {
		throw "ERROLISTACHEIA";
	}
}

template<typename T> T ListaEnc<T>::retiraDoInicio() {
	Elemento<T> *headAux;
	T retorno;
	if (listaVazia()) {
		throw "lista vazia";
	} else {
		headAux = head;
		retorno = headAux->getInfo();
		head = headAux->getProximo();
		size -= 1;
		headAux->~Elemento();
		delete headAux;
		return retorno;
	}

}

template<typename T> void ListaEnc<T>::eliminaDoInicio() {

}

template<typename T> void ListaEnc<T>::adicionaNaPosicao(const T& dado,
		int pos) {
	Elemento<T> *novoElemento;
	Elemento<T> *percorredorDeElementos = head;
	if (pos == 1)
		adicionaNoInicio(dado);
	novoElemento = new Elemento<T>(dado, nullptr);
	if (novoElemento != nullptr) {
		if ((pos <= size + 1) && (pos > 0)) {
			for (int i = 1; i < pos; i++) {
				percorredorDeElementos = percorredorDeElementos->getProximo();
			}
			novoElemento->setProximo(percorredorDeElementos->getProximo());
			percorredorDeElementos->setProximo(novoElemento);
			size += 1;

		} else {
			throw "PosicaoInvaida";
		}
	} else {
		throw "Lista cheia";
	}
}

template<typename T> int ListaEnc<T>::posicao(const T& dado) const {
	Elemento<T> *auxPointer = head;

	for (int var = 1; var <= size; var++) {
		T infoAux = auxPointer->getInfo();
		if (dado == infoAux) {
			delete auxPointer;
			return var;
		}
		auxPointer = auxPointer->getProximo();
	}

	delete auxPointer;
	throw "elemento nao esta na lista";

}

template<typename T> T* ListaEnc<T>::posicaoMem(const T& dado) const {
	Elemento<T> *auxPointer = head;

	for (int var = 1; var <= size; var++) {
		T infoAux = auxPointer->getInfo();
		if (igual(infoAux, dado)) {
			return auxPointer;
		}
		auxPointer = auxPointer->getProximo();
	}

	delete auxPointer;
	throw "Elemento nao presente";

}

template<typename T> bool ListaEnc<T>::contem(const T& dado) {
	Elemento<T> *auxPointer = head;

	for (int var = 1; var <= size; var++) {
		T infoAux = auxPointer->getInfo();
		if (igual(infoAux, dado)) {
			delete auxPointer;
			return true;
		}
		auxPointer = auxPointer->getProximo();
	}

	delete auxPointer;
	return false;

}

template<typename T> T ListaEnc<T>::retiraDaPosicao(int pos) {
	T retorno;
	Elemento<T> *percorredorDeElementos = head, *elementoRetirado;

	if ((pos <= size + 1) && (pos > 0) && !(listaVazia())) {
		if (pos == 1) {
			return retiraDoInicio();
		} else {
			for (int i = 1; i < pos; i++) {
				percorredorDeElementos = percorredorDeElementos->getProximo();
			}
			elementoRetirado = percorredorDeElementos->getProximo();
			percorredorDeElementos->setProximo(elementoRetirado->getProximo());
			retorno = elementoRetirado->getInfo();
			elementoRetirado->~Elemento();
			delete elementoRetirado;
			size -= 1;
			return retorno;
		}
	} else {
		throw "ERROLISTAVAZIA ou PosicaoInvaida";
	}
}

template<typename T> void ListaEnc<T>::adiciona(const T& dado) {
	adicionaNaPosicao(dado, size + 1);
}

template<typename T> T ListaEnc<T>::retira() {
	return retiraDaPosicao(size);
}

template<typename T> T ListaEnc<T>::retiraEspecifico(const T& dado) {
	try {
		int pos = posicao(dado);
		return retiraDaPosicao(pos);
	} catch (int e) {
		throw "elemento nao presente";
	}
}

template<typename T> void ListaEnc<T>::adicionaEmOrdem(const T& data) {
	Elemento<T> *headAux = head;
	for (int pos = 1; pos <= size; pos++) {
		if (menor(data, headAux->getInfo())) {
			adicionaNaPosicao(data, pos);
			pos = size + 1;
		}
		headAux = headAux->getProximo();
		delete headAux;
	}
}

template<typename T> bool ListaEnc<T>::listaVazia() const {
	return (size == 0);
}

template<typename T> bool ListaEnc<T>::igual(T dado1, T dado2) {
	return (dado1 == dado2);
}

template<typename T> bool ListaEnc<T>::maior(T dado1, T dado2) {
	return (dado1 > dado2);
}

template<typename T> bool ListaEnc<T>::menor(T dado1, T dado2) {
	return (dado1 < dado2);
}

template<typename T> int ListaEnc<T>::getSize() {
	return size;
}

template<typename T> void ListaEnc<T>::destroiLista() {
	Elemento<T> *headAux = head;
	for (int pos = 1; pos <= size; pos++) {
		headAux->~Elemento();
		headAux = headAux->getProximo();
	}
	delete head;
}
