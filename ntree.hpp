#ifndef NTREE_HPP
#define NTREE_HPP

#include <iostream>

/*
    Implementação de uma árvore n-ária genérica

    @author     Guilherme Guidotti Brandt
    @version    0.1.0
    @date       2018-08-12
*/
template <unsigned int N, class T> class n_tree
{
    private:
        T* info[N - 1];
        int last_index;

        n_tree* branches[N];

    public:
        n_tree();
        ~n_tree();

        bool empty();
        void insert(T);

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