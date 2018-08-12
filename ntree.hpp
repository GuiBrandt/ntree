#ifndef NTREE_HPP
#define NTREE_HPP

#include <iostream>

/**
 * @brief Árvore n-ária de busca
 * 
 * @tparam N Número de nós filhos por nó
 * @tparam T Tipo de valor armazenado na árvore
 */
template <unsigned int N, class T> class n_tree
{
    private:
        T* info[N - 1];         //! Vetor de informações
        int last_index;         //! Última posição ocupada no vetor de informações

        n_tree* branches[N];    //! Vetor de nós filhos

    public:
        /**
         * @brief Construtor
         */
        n_tree();
        /**
         * @brief Destrutor
         */
        ~n_tree();
        /**
         * @brief Determina se a árvore está vazia
         * 
         * @return true se a árvore não tiver nenhum elemento ou nó filho
         * @return false 
         */
        bool empty();
        /**
         * @brief Insere uma informação na árvore
         * 
         * @param data Dados a serem inseridos na árvore
         */
        void insert(const T& data);
        /**
         * @brief Escreve uma árvore para uma stream de saída em ordem
         * 
         * @param out Stream de saída
         * @param tree Árvore a ser escrita
         * @return std::ostream& A stream recebida por parâmetro
         */ 
        // Nota: Isso precisa estar dentro da declaração da classe devido ao 
        // parâmetro genérico (n_tree<N, T>) em uma "função amiga"
        friend std::ostream& operator<<(std::ostream& out, const n_tree<N, T>& tree)
        {
            for (int i = 0; i <= tree.last_index; i++)
            {
                if (i > 0)
                    out << " ";

                if (tree.branches[i])
                    out << *tree.branches[i] << " ";
                out << *tree.info[i];
            }

            if (tree.branches[N - 1])
                out << " " << *tree.branches[N - 1];

            return out;
        }
};

#endif // NTREE_HPP