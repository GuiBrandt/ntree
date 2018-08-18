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
        int n_branches;         //! Quantidade de nós filhos que a árvore tem de fato

        /**
         * @brief Busca uma informação no vetor de informações da árvore
         * 
         * @param data Informação a ser procurada
         * 
         * @return int O índice da informação no vetor ou o índice onde seria
         * inserida para manter o vetor ordenado
         */
        int where(const T& data)
        {
            int beg = 0,
                end = last_index + 1,
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

        /**
         * @brief Cria um nó na posição I do vetor de ponteiros
         * 
         * @param i Índice no vetor de ponteiros
         */
        void create_branch(int i)
        {
            branches[i] = new n_tree<N, T>();
            n_branches++;
        }

        /**
         * @brief Remove um nó da posição I do vetor de ponteiros
         * 
         * @param i Índice no vetor de ponteiros
         */
        void delete_branch(int i)
        {
            delete branches[i];

            branches[i] = NULL;
            n_branches--;
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

            n_branches = 0;
        }

        /**
         * @brief Destrutor
         */
        ~n_tree()
        {
            if (is_leaf())
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
            return n_branches == 0;
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
         * @brief Obtém o menor valor da árvore
         * 
         * @return T Menor valor contido na árvore
         */
        T min() throw (const char*)
        {
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
        T max() throw (const char*)
        {
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
        T pop() throw (const char*)
        {
            if (empty())
                throw "Can't pop from an empty tree";

            // Se o último ponteiro tem informação, o maior da árvore é o maior
            // do último ponteiro
            if (branches[N - 1])
                return branches[N - 1]->pop();

            // Se não, é a informação na última posição
            T max = info[last_index];

            // Se não for uma folha, precisa relocar tuuudo de novo, levando em
            // conta os nós filhos
            if (!is_leaf())
            {
                for (int i = N - 2; i >= 0; i--)
                {
                    if (i > 0)
                        info[i] = info[i - 1];

                    if (branches[i] == NULL)
                        continue;

                    info[i] = branches[i]->pop();

                    // Se a árvore no ponteiro ficou vazia, pode deletar aquela
                    // árvore
                    if (branches[i]->empty())
                        delete_branch(i);

                    break;
                }
            }

            // Se for uma folha, só diminui o índice e boa
            else
                last_index--;

            return max;
        }
        
        /**
         * @brief Remove o menor valor da árvore e retorna
         * 
         * @return T Menor valor contido na árvore
         */
        T popleft() throw (const char*)
        {
            if (empty())
                throw "Can't shift from an empty tree";

            // Se o primeiro ponteiro tem informação, o menor da árvore é o 
            // menor do primeiro ponteiro
            if (branches[0])
                return branches[0]->popleft();

            // Se não, é a informação na primeira posição
            T max = info[0];

            // Se não for uma folha, precisa relocar tuuudo de novo, levando em
            // conta os nós filhos
            if (!is_leaf())
            {
                for (int i = 0; i < N; i++)
                {
                    if (i < N - 2)
                        info[i] = info[i + 1];

                    if (branches[i + 1] == NULL)
                        continue;

                    info[i] = branches[i + 1]->popleft();

                    // Se a árvore no ponteiro ficou vazia, pode deletar aquela
                    // árvore
                    if (branches[i + 1]->empty())
                        delete_branch(i + 1);

                    break;
                }
            }

            // Se for uma folha, é mais fácil relocar as coisas
            else
            {
                for (int i = 0; i < last_index; i++)
                    info[i] = info[i + 1];

                last_index--;
            }

            return max;
        }

        /**
         * @brief Insere uma informação na árvore
         * 
         * @param data Dados a serem inseridos na árvore
         */
        void insert(const T& data)
        {
            int at = where(data);

            if (last_index < (int)N - 2)
            {
                for (int i = last_index; i >= at; i--)
                    info[i + 1] = info[i];

                info[at] = data;
                last_index++;
            }
            else
            {
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
        void remove(const T& data)
        {
            int at = where(data);

            if (is_leaf())
            {
                if (info[at] != data)
                    return;

                for (int i = at; i < last_index; i++)
                    info[i] = info[i + 1];
                last_index--;
            }
            else if (branches[at] != NULL && info[at] > data)
                branches[at]->remove(data);

            else if (branches[at + 1] != NULL && info[at] < data)
                branches[at + 1]->remove(data);

            else
            {
                if (branches[at])
                    info[at] = branches[at]->pop();
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