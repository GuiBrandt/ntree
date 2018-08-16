#include "ntree.hpp"
#include <iostream>

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