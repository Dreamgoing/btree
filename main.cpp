#include <iostream>
#include "Btree.hpp"
int main() {
//    std::cout << "Hello, World!" << std::endl;

    ///
    Btree<int> btree(4);
    Btree<string> a;
    cout<<btree.getDegree()<<endl;
    cout<<a.getDegree()<<endl;


    return 0;
}