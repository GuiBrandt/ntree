/**
 * @brief Cabeçalho para a classe de árvore n-ária de busca
 * 
 * @file ntree.hpp
 * @author Guilherme Brandt
 * @date 2018-08-18
 */

#ifndef NTREE_HPP
#define NTREE_HPP

#include <iostream>
#include <functional>
#include <queue>

/**
 * @brief Árvore n-ária de busca
 * 
 * @tparam N Número de nós filhos por nó
 * @tparam T Tipo de valor armazenado na árvore
 */
template < unsigned int N, class T > class n_tree {
	
private:

	T info[N - 1];      	//! Vetor de informações
	int last_index;        	//! Última posição ocupada no vetor de informações

	n_tree * branches[N];  	//! Vetor de nós filhos
	int n_branches;        	//! Quantidade de nós filhos que a árvore tem de fato

	/**
	 * @brief Busca uma informação no vetor de informações da árvore
	 * 
	 * @param data Informação a ser procurada
	 * 
	 * @return int O índice da informação no vetor ou o índice onde seria
	 * inserida para manter o vetor ordenado
	 */
	int where(const T & data) {
		int beg = 0,
			end = last_index + 1,
			i = 0;

		while (beg < end) {
			i = (beg + end) >> 1;

			if (info[i] < data)
				beg = i + 1;
			else if (info[i] > data)
				end = i;
			else
				return i;
		}

		return beg;
	}

	/**
	 * @brief Cria um nó na posição I do vetor de ponteiros
	 * 
	 * @param i Índice no vetor de ponteiros
	 */
	void create_branch(int i) {
		branches[i] = new n_tree <N, T> ();
		n_branches++;
	}

	/**
	 * @brief Remove um nó da posição I do vetor de ponteiros
	 * 
	 * @param i Índice no vetor de ponteiros
	 */
	void delete_branch(int i) {
		delete branches[i];

		branches[i] = NULL;
		n_branches--;
	}

	/**
	 * @brief Retorna o galho mais próximo a uma posição
	 *  
	 * @param i Posição no vetor de galhos
	 * @return int Posição do galho mais próximo à posição dada
	 */
	int closest_branch(int i) {
		int l = i, r = i;
		while (l > 0 && r < N) {
			if (branches[l] != NULL)
				return l;
			if (branches[r] != NULL)
				return r;

			if (l > 0)
				l--;
			if (r < N)
				r++;
		}
		return -1;
	}

	/**
	 * @brief Remove uma informação do vetor e troca ela por outra, 
	 * mantendo a coerência da árvore
	 * 
	 * @param i Índice no vetor de informações
	 * 
	 * @return T informação que foi removida
	 */
	T remove_info(int i) {
		T data = info[i];

		if (is_leaf()) {
			for (; i < last_index; i++)
				info[i] = info[i + 1];

			last_index--;
		} else {
			int closest = closest_branch(i);

			if (closest <= i) {
				for (; i > closest; i--)
					info[i] = info[i - 1];

				info[i] = branches[closest]->pop();
			} else {
				for (; i < closest - 1; i++)
					info[i] = info[i + 1];

				info[i] = branches[closest]->popleft();
			}

			if (branches[closest]->empty())
				delete_branch(closest);
		}

		return data;
	}

public:

	/**
	 * @brief Construtor
	 */
	n_tree() {
		last_index = -1;

		for (int i = 0; i < N; i++)
			branches[i] = 0;

		n_branches = 0;
	}

	/**
	 * @brief Construtor de cópia
	 * 
	 * @param model Objeto modelo
	 */
	n_tree(const n_tree & model) {
		*this = model;
	}

	/**
	 * @brief Operador de cópia
	 * 
	 * @param model Objeto modelo
	 * @return n_tree& Cópia do objeto modelo
	 */
	n_tree & operator = (const n_tree & model) {
		if (this == & model)
			return *this;

		last_index = model.last_index;

		for (int i = 0; i <= last_index; i++)
			info[i] = model.info[i];

		for (int i = 0; i < N; i++)
			if (branches[i])
				delete branches[i];

		for (int i = 0; i < N; i++)
			branches[i] = new n_tree<N, T> (model.branches[i]);

		n_branches = model.n_branches;

		return *this;
	}

	/**
	 * @brief Destrutor
	 */
	~n_tree() {
		if (is_leaf())
			return;

		for (int i = 0; i < N; i++)
			if (branches[i])
				delete branches[i];
	}

	/**
	 * @brief Determina se a árvore é uma folha
	 * 
	 * @return true se a árvore for uma folha
	 * @return false caso contrário
	 */
	bool is_leaf() {
		return n_branches == 0;
	}

	/**
	 * @brief Determina se a árvore está vazia
	 * 
	 * @return true se a árvore não tiver nenhum elemento ou nó filho
	 * @return false caso contrário
	 */
	bool empty() {
		return last_index < 0;
	}

	/**
	 * @brief Obtém o menor valor da árvore
	 * 
	 * @return T Menor valor contido na árvore
	 */
	T min() throw (const char*) {
		if (empty())
			throw "Empty tree has no minimum value";

		if (branches[0])
			return branches[0]->min();

		return info[0];
	}

	/**
	 * @brief Obtém o maior valor da árvore
	 * 
	 * @return T Maior valor contido na árvore
	 */
	T max() throw (const char*) {
		if (empty())
			throw "Empty tree has no maximum value";

		if (branches[N - 1])
			return branches[N - 1]->max();

		return info[last_index];
	}

	/**
	 * @brief Remove o maior valor da árvore e retorna
	 * 
	 * @return T Maior valor contido na árvore
	 */
	T pop() throw (const char*) {
		if (empty())
			throw "Can't pop from an empty tree";

		if (branches[N - 1])
			return branches[N - 1]->pop();
		else
			return remove_info(last_index);
	}

	/**
	 * @brief Remove o menor valor da árvore e retorna
	 * 
	 * @return T Menor valor contido na árvore
	 */
	T popleft() throw (const char*) {
		if (empty())
			throw "Can't pop from an empty tree";

		if (branches[0])
			return branches[0]->popleft();
		else
			return remove_info(0);
	}

	/**
	 * @brief Remove todas as informações da árvore
	 */
	void clear() {
		last_index = -1;

		for (int i = 0; i < N; i++) {
			if (branches[i])
				delete branches[i];

			branches[i] = 0;
		}

		n_branches = 0;
	}

	/**
	 * @brief Insere uma informação na árvore
	 * 
	 * @param data Dados a serem inseridos na árvore
	 */
	void insert(const T & data) {
		int at = where(data);

		if (last_index < (int)N - 2) {
			for (int i = last_index; i >= at; i--)
				info[i + 1] = info[i];

			info[at] = data;

			last_index++;
		} else {
			if (!branches[at])
				create_branch(at);

			branches[at]->insert(data);
		}
	}

	/**
	 * @brief Exclui uma informação da árvore
	 * 
	 * @param data Dados a serem removidos
	 */
	void remove(const T & data) {
		int at = where(data);
		remove_info(at);
	}

	/**
	 * @brief Percorre a árvore em ordem
	 * 
	 * @param function Função a ser chamada como callback para cada elemento
	 * percorrido
	 */
	void in_order(std::function<void(const T&)> function) const {
		for (int i = 0; i <= last_index; i++) {
			if (branches[i])
				branches[i]->in_order(function);

			function(info[i]);
		}

		if (branches[N - 1])
			branches[N - 1]->in_order(function);
	}
	
	/**
	 * @brief Percorre a árvore em pré-ordem
	 * 
	 * @param function Função a ser chamada como callback para cada elemento
	 * percorrido
	 */
	void pre_order(std::function<void(const T&)> function) const {
		for (int i = 0; i <= last_index; i++)
			function(info[i]);
		
		for (int i = 0; i <= N - 1; i++)
			if (branches[i])
				branches[i]->pre_order(function);
	}
	
	/**
	 * @brief Percorre a árvore em pós-ordem
	 * 
	 * @param function Função a ser chamada como callback para cada elemento
	 * percorrido
	 */
	void post_order(std::function<void(const T&)> function) const {
		for (int i = 0; i <= N - 1; i++)
			if (branches[i])
				branches[i]->post_order(function);

		for (int i = 0; i <= last_index; i++)
			function(info[i]);
	}

	/**
	 * @brief Percorre a árvore por nível
	 * 
	 * @param function Função a ser chamada como callback para cada elemento
	 * percorrido
	 */
	void by_level(std::function<void(const T&)> function) const {
		std::queue<const n_tree*> q;
		q.push(this);

		while (!q.empty()) {
			const n_tree* current = q.front();
			q.pop();
			
			for (int i = 0; i <= current->last_index; i++) {
				function(current->info[i]);

				if (current->branches[i])
					q.push(current->branches[i]);
			}

			if (current->branches[N - 1])
				q.push(current->branches[N - 1]);
		}
	}

	/**
	 * @brief Escreve uma árvore para uma stream de saída em ordem
	 * 
	 * @param out Stream de saída
	 * @param tree Árvore a ser escrita
	 * @return std::ostream& A stream recebida por parâmetro
	 */
	friend std::ostream & operator << (
		std::ostream & out,
		const n_tree < N, T > & tree
	) {
		tree.in_order([&out](T info) -> void {
			out << info << " ";
		});
		return out;
	}
};

#endif // NTREE_HPP