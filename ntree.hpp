#ifndef NTREE_HPP
#define NTREE_HPP

#include <iostream>
#include <iterator>

/**
 * @brief Árvore n-ária de busca
 * 
 * @tparam N Número de nós filhos por nó
 * @tparam T Tipo de valor armazenado na árvore
 */
template <unsigned int N, class T> class n_tree
{
    private:
        T info[N - 1];          //! Vetor de informações
        int last_index;         //! Última posição ocupada no vetor de informações

        n_tree* branches[N];    //! Vetor de nós filhos

        /**
         * @brief Faz busca binária no vetor de informações da árvore
         * 
         * @param data Informação a ser procurada
         * 
         * @return O índice da informação no vetor ou o índice onde seria
         * inserida para manter o vetor ordenado
         */
        int bsearch(const T& data)
        {
            int beg = 0,
                end = last_index,
                i = 0;

            while (beg < end)
            {
                i = (beg + end) >> 1;
                
                if (info[i] < data)
                    beg = i + 1;
                else if (info[i] > data)
                    end = i;
                else
                    break;
            }

            return beg;
        }

    public:
        /**
         * @brief Construtor
         */
        n_tree()
        {
            last_index = -1;

            for (int i = 0; i < N; i++)
                branches[i] = 0;
        }

        /**
         * @brief Destrutor
         */
        ~n_tree()
        {
            if (last_index < N - 2)
                return;

            for (int i = 0; i < N; i++)
                if (branches[i])
                    delete branches[i];
        }

        /**
         * Determina se a árvore é uma folha
         * 
         * @return true se a árvore for uma folha
         * @return false caso contrário
         */
        bool is_leaf()
        {
            return last_index < (int)N - 2;
        }

        /**
         * @brief Determina se a árvore está vazia
         * 
         * @return true se a árvore não tiver nenhum elemento ou nó filho
         * @return false caso contrário
         */
        bool empty()
        {
            return last_index < 0;
        }

        /**
         * @brief Insere uma informação na árvore
         * 
         * @param data Dados a serem inseridos na árvore
         */
        void insert(const T& data) 
        {
            int at = bsearch(data);
            if (is_leaf())
            {
                for (int i = last_index; i >= at; i--)
                    info[i + 1] = info[i];

                info[at] = data;
                last_index++;
            }
            else
            {
                if (branches[at] == 0)
                    branches[at] = new n_tree<N, T>();

                branches[at]->insert(data);
            }
        }

        /**
         * @brief Exclui uma informação da árvore
         * 
         * @param data Dados a serem removidos
         */
        void remove(const T& data)
        {
            if (is_leaf())
            {
                int at = bsearch(data);
                last_index--;
            }
        }

        /**
         * @brief Escreve uma árvore para uma stream de saída em ordem
         * 
         * @param out Stream de saída
         * @param tree Árvore a ser escrita
         * @return std::ostream& A stream recebida por parâmetro
         */
        friend std::ostream& operator<<(std::ostream& out, const n_tree<N, T>& tree)
        {
            out << "(";

            for (int i = 0; i <= tree.last_index; i++)
            {
                if (i > 0)
                {
                    out << ";";
                    out << " ";
                }

                if (tree.branches[i])
                    out << *tree.branches[i] << "; ";
                out << tree.info[i];
            }

            if (tree.branches[N - 1])
                out << " " << *tree.branches[N - 1];

            out << ")";

            return out;
        }
};

#endif // NTREE_HPP