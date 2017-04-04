/*! \brief classe de implementação de uma lista encadeada.
 *
 *	Lista projetada para variados tipos de dados. Usa um vetor
 *	como forma de armazenamento.
 *  \author Johann Westphall.
 *  \since 31/03/15
 *  \version 1.0
 */
#include "../src/Elemento.hpp"
template<typename T>
class ListaEnc {
private:
	Elemento<T>* head; /*!< Ponteiro para primeiro elemento da lista.*/
	int size; /*!< Inteiro para definir quantos elmentos estao na lista.*/

public:
	/*! \brief Construtor da lista.
	 *
	 * Inicializa as variaveis size, em zero,
	 * e head, em nullptr.
	 */
	ListaEnc();
	/*!
	 * \brief Destrutor. Invoca o metodo destrói lista.
	 * \sa destroiLista().
	 */
	~ListaEnc();
	/*! \brief Adiciona um dado de determinado tipo na posi-
	 * cao 1 da lista.
	 *
	 * Instancia um Elemento com o ponteiro para o dado. Testa
	 * se foi alocada memoria para ele, se sim head apontara
	 * para o novo elemento e o novo elemento terá como próximo
	 * o antigo valor de head. Soma 1 a variavel size.
	 * \param dado um dado de determinado tipo a ser adicinado na lista.
	 */
	void adicionaNoInicio(const T& dado);
	/*!\brief Retira dado do primeiro elemento.
	 *
	 * Metodo que testa se a lista esta vazia e caso
	 * nao esteja remove e retorna o dado do primeiro
	 * Elemento da lista, apontado pela variavel head.
	 * Size é decrementada em 1 unidade.
	 * \return dado de determinado tipo presente na lista
	 */
	T retiraDoInicio();
	/*! \brief Elimina primeiro elemento
	 *
	 *	Verifica se a lista esta vazia e caso nao esteja
	 *	deleta o primeiro elemento e atribui a head o pon-
	 *	teiro do segundo. Size é decrementada em 1 unidade.
	 */
	void eliminaDoInicio();
	/*! \brief Adiciona dado a determinada posicao
	 *
	 *  Instancia novo Elemento e verifica se foi alocada
	 *  memoria para ele. Se sim, verifica se a posição
	 *  passada como parâmetro é valida e de acordo com ela
	 *  decide adicionar no inicio ou em outra posicao.
	 *  Se adicionar em uma posicao que nao seja a primeira,
	 *  atribuira como next do novo Elemento o antigo elemento
	 *  da posicao desejada 'x' e ao elemento da posicao 'x-1'
	 *  atribuira o novo Elemento como next. Size sera incrementada
	 *  em 1 unidade.
	 *
	 *  \sa adicionaNoInicio()
	 */
	void adicionaNaPosicao(const T& dado, int pos);
	/*! \brief Retorna posicao de elemento da lista
	 *
	 * 	Recebe o dado e percorre a lista comparando com cada
	 * 	elemento. Se o dado passado for igual a algum dado de um
	 * 	elemento, a posicao dele é retornada.
	 * 	\param dado do tipo T para comparação com outros elementos.
	 * 	\return int posição de elemento igual ao dado passado.
	 */
	int posicao(const T& dado) const;
	/*! \brief Retorna o ponteiro de um dado da lista
	 *
	 * 	Recebe o dado e percorre a lista comparando com cada
	 * 	elemento. Se o dado passado for igual a algum dado de
	 * 	um elemento,a ponteiro para ele é retornado.
	 * 	\param dado do tipo T para comparação com outros elementos.
	 * 	\return ponteiro para o dado igual ao passado como parametro.
	 */
	T* posicaoMem(const T& dado) const;
	/*! \brief Retorna um boolean se um dado estiver na lista
	 *
	 * 	Recebe o dado e percorre a lista comparando com cada
	 * 	elemento. Se o dado passado for igual a algum dado de
	 * 	um elemento, true é retornado.
	 * 	\param dado do tipo T para comparação com outros elementos.
	 * 	\return ponteiro para o dado igual ao passado como parametro.
	 */
	bool contem(const T& dado);
	/*! \brief Retira e retorna dado de determinada posição
	 *
	 * 	Recebe uma posiçao, verifica se a lista nao esta vazia,
	 * 	testa se a posição esta sendo ocupada por algum dado e se
	 * 	estiver percorre a lista até o elemento, salva seu dado e
	 * 	arruma o ponteiro do elemento anterior. Size é decrementado
	 * 	em uma unidade.
	 * 	\param pos posicao de elemento desejado.
	 * 	\return dado do tipo T.
	 */
	T retiraDaPosicao(int pos);
	/*! \brief Adicona elemento no final da lista
	 *
	 * 	É o metodo adicionaNaPosicao() com posição igual a size(final).
	 * 	\sa adicionaNaPosicao().
	 * 	\param dado a ser adicionado no final da lista.
	 */
	void adiciona(const T& dado);
	/*! \brief Retira elemento do final da lista
	 *
	 * 	É o metodo retiraDaPosicao() com posição igual a size-1(final).
	 * 	\sa retiraDaPosicao().
	 * 	\return dado que estava na lista.
	 */
	T retira();
	/*! \brief Retira elemento especifico
	 *
	 * 	É o metodo posicao() e retiraDaPosicao(). Se posicao(dado) retornar
	 * 	uma posicao significa que o elemento esta na lista e entao o metodo
	 * 	retiraDaPosicao() usa a posicao para retirar elemento passado como
	 * 	parametro. Se nao estiver na lista, lançara uma excessao.
	 * 	\sa retiraDaPosicao().
	 * 	\sa posicao().
	 * 	\return dado que estava na lista igual a dado.
	 */
	T retiraEspecifico(const T& dado);
	/*! \brief Adiciona em ordem.
	 *
	 *  Adiciona respeitando a ordem determinada pelo
	 *  operador "<" de um objeto do tipo "T". Se um
	 *  novo objeto for menor ou igual a de outro objeto em
	 *  determinada posicao, esse novo assume a posição do antigo.
	 *  Caso o novo objeto nao seja menor ou igual a nenhum ele-
	 *  mento da lista ele é adicionado na ultima posicao.
	 *  \param dado de determinado tipo a ser adicionado.
	 *  \sa adicionaNaPosicao()
	 */
	void adicionaEmOrdem(const T& data);
	/*! \brief Retorna true se lista estiver vazia.
	 *
	 * 	E false se lista nao estiver. Para isso verifica
	 * 	se "ultimo" == -1
	 * 	\return lista esta vazia ou nao vazia
	 */
	bool listaVazia() const;
	/*! \brief Retorna se um dado é igual ao outro.
	 *
	 * 	Retorna verdadeiro se dois dados do tipo "T"
	 * 	forem um igual ao outro. Se nao, retorna falso.
	 * 	\return dado1 é igual a dado2.
	 */
	bool igual(T dado1, T dado2);
	/*! \brief Retorna se um dado é maior que o outro.
	 *
	 * 	Retorna verdadeiro se dado1 for maior que dado2
	 * 	o tipo "T". Se nao, retorna falso.
	 * 	\return dado1 é maior que dado2.
	 */
	bool maior(T dado1, T dado2);
	/*! \brief Retorna se um dado é menor que o outro.
	 *
	 * 	Retorna verdadeiro se dado1 for menor que dado2
	 * 	o tipo "T". Se nao, retorna falso.
	 * 	\return dado1 é menor que dado2.
	 */
	bool menor(T dado1, T dado2);
	/*! \brief Destrói a lista
	 *
	 * 	Destrói a lista desconsiderando os dados anterior-
	 * 	mente escritos nela. Para isso seta size em 0.
	 * 	Também deleta os antigos dados da memoria, desalo-
	 * 	cando o espaço da memoria.
	 */
	void destroiLista();
	int tamanho() const;
	T retornaDado(int pos) const;
	void operator=(ListaEnc<T>& l2);
};

template<typename T> ListaEnc<T>::ListaEnc() {
	size = 0;
	head = nullptr;
}

template<typename T> ListaEnc<T>::~ListaEnc() {
	destroiLista();
}

template<typename T> void ListaEnc<T>::adicionaNoInicio(const T& dado) {
	Elemento<T> *novoElemento = new Elemento<T>(dado, nullptr);
	Elemento<T> *headAux;
	if (novoElemento != nullptr) {
		headAux = head;
		head = novoElemento;
		novoElemento->setProximo(headAux);
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
		retorno = head->getInfo();
		head = headAux->getProximo();
		size -= 1;
		delete headAux;
		return retorno;
	}
}

template<typename T> void ListaEnc<T>::eliminaDoInicio() {
	Elemento<T> *headAux;
	T retorno;
	if (listaVazia()) {
		throw "lista vazia";
	} else {
		headAux = head;
		head = headAux->getProximo();
		size -= 1;
		delete headAux;
	}
}

template<typename T> void ListaEnc<T>::adicionaNaPosicao(const T& dado,
		int pos) {
	Elemento<T> *novoElemento = new Elemento<T>(dado, nullptr);
	Elemento<T> *percorredorDeElementos = head;

	if ((novoElemento != nullptr) && (pos <= size) && (pos >= 0)) {
		if (pos == 0) {
			delete novoElemento;
			adicionaNoInicio(dado);
		} else {
			for (int i = 0; i < pos - 1; i++) {
				percorredorDeElementos = percorredorDeElementos->getProximo();
			}
			novoElemento->setProximo(percorredorDeElementos->getProximo());
			percorredorDeElementos->setProximo(novoElemento);
			size += 1;
		}
	} else {
		throw "ERROLISTACHEIA ou PosicaoInvaida";
	}
}

template<typename T> int ListaEnc<T>::posicao(const T& dado) const {
	Elemento<T> *auxPointer = head;

	for (int var = 0; var < size; var++) {
		T infoAux = auxPointer->getInfo();
		if (dado == infoAux) {
			// delete auxPointer;
			return var;
		}
		auxPointer = auxPointer->getProximo();
	}
	throw "elemento nao esta na lista";
}

template<typename T> T* ListaEnc<T>::posicaoMem(const T& dado) const {
	Elemento<T> *auxPointer = head;

	for (int var = 0; var < size; var++) {
		T infoAux = auxPointer->getInfo();
		if (igual(infoAux, dado)) {
			return auxPointer;
		}
		auxPointer = auxPointer->getProximo();
	}
	throw "Elemento nao presente";
}

template<typename T> bool ListaEnc<T>::contem(const T& dado) {
	Elemento<T> *auxPointer = head;

	for (int var = 0; var < size; var++) {
		T infoAux = auxPointer->getInfo();
		if (igual(infoAux, dado)) {
			return true;
		}
		auxPointer = auxPointer->getProximo();
	}
	return false;
}

template<typename T> T ListaEnc<T>::retiraDaPosicao(int pos) {
	T retorno;
	Elemento<T> *percorredorDeElementos = head, *elementoRetirado;

	if ((pos < size) && (pos >= 0) && !(listaVazia())) {
		if (pos == 0) {
			return retiraDoInicio();
		} else {
			for (int i = 0; i < pos - 1; i++) {
				percorredorDeElementos = percorredorDeElementos->getProximo();
			}
			elementoRetirado = percorredorDeElementos->getProximo();
			percorredorDeElementos->setProximo(elementoRetirado->getProximo());
			retorno = elementoRetirado->getInfo();
			delete elementoRetirado;
			size -= 1;
			return retorno;
		}
	} else {
		throw "ERROLISTAVAZIA ou PosicaoInvaida";
	}
}

template<typename T> void ListaEnc<T>::adiciona(const T& dado) {
	adicionaNaPosicao(dado, size);
}

template<typename T> T ListaEnc<T>::retira() {
	return retiraDaPosicao(size - 1);
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
	int pos;
	if (listaVazia()) {
		adicionaNoInicio(data);
	} else {
		for (pos = 0; pos < size; pos++) {
			T info = headAux->getInfo();
			if ((menor(data, info)) || (igual(data, info))) {
				adicionaNaPosicao(data, pos);
				pos = size;
			} else if (pos == size - 1) {
				adicionaNaPosicao(data, pos);
			}
			headAux = headAux->getProximo();
		}
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

template<typename T> void ListaEnc<T>::destroiLista() {
	Elemento<T> *headAux = head, *headAux2 = head;
	for (int pos = 0; pos < size; pos++) {
		headAux2 = headAux->getProximo();
		headAux->~Elemento();
		headAux = headAux2;
	}
	delete headAux2;
	size = 0;
	head = nullptr;
}

template<typename T> int ListaEnc<T>::tamanho() const{
	return size;
}

template<typename T> T ListaEnc<T>::retornaDado(int pos) const{
	Elemento<T> *percorredorDeElementos = head;

	if ((pos < size) && (pos >= 0) && !(listaVazia())) {
		if (pos == 0) {
			return head->getInfo();
		} else {
			for (int i = 0; i < pos; i++) {
				percorredorDeElementos = percorredorDeElementos->getProximo();
			}
			return percorredorDeElementos->getInfo();
		}
	} else {
		throw "ERROLISTAVAZIA ou PosicaoInvaida";
	}
}

template<typename T> void ListaEnc<T>::operator =(ListaEnc<T>& l2) {
	destroiLista();
	ListaEnc<T>();
	if (l2.tamanho() > 0) {
		for (int i = 0; i < l2.tamanho(); i++) {
			adiciona(l2.retornaDado(i));
		}
	}
}
