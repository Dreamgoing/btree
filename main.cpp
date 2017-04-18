#include <iostream>
#include "Btree.hpp"

void testBtreeInsert(){
    Btree<int> btree;
    btree.BtreeInsert(1);
    btree.BtreeInsert(2);
//    btree.BtreeInsert(3);
//    btree.BtreeInsert(4);
    btree.DFSshow();
}
int main() {
//    std::cout << "Hello, World!" << std::endl;

    ///
    Btree<int> btree(4);

    ///pass-by const reference 是传递的右值引用，通过const关键字来实现右值引用。
    ///通常来说引用类型都是左值引用
//
//    const int& r = 9;
////    int& s= 9;
//    Btree<string> a;
//    cout<<btree.getDegree()<<endl;
//    cout<<a.getDegree()<<endl;
    testBtreeInsert();

    return 0;
}