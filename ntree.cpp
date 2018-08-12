#include "ntree.hpp"
#include <iostream>
#include <vector>

template<unsigned int N, class T> n_tree<N, T>::n_tree()
{
    last_index = -1;

    for (int i = 0; i < N; i++)
        branches[i] = 0;
}

template<unsigned int N, class T> n_tree<N, T>::~n_tree()
{
    for (int i = 0; i <= last_index; i++)
        delete info[i];

    if (last_index < N - 2)
        return;

    for (int i = 0; i < N; i++)
        if (branches[i])
            delete branches[i];
}

template<unsigned int N, class T> bool n_tree<N, T>::empty()
{
    return last_index < 0;
}

template<unsigned int N, class T> void n_tree<N, T>::insert(T data)
{
    int at = 0;

    if (!empty())
        for (; at <= last_index && *info[at] < data; at++);

    if (last_index < (int)N - 2)
    {
        for (int i = last_index; i >= at; i--)
            info[i + 1] = info[i];

        info[at] = new T(data);
        last_index++;
    }
    else
    {
        if (branches[at] == 0)
            branches[at] = new n_tree<N, T>();

        branches[at]->insert(data);
    }
}

int main(int argc, char** argv)
{
    n_tree<5, double> t;
    t.insert(0.0);
    t.insert(1.3);
    t.insert(54.24);
    t.insert(0.5454);
    t.insert(0.032);
    std::cout << t;

    return 0;
}