#include <iostream>
#include "Btree.hpp"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>

using namespace std;
using namespace boost;

void testBtreeInsert(){
    Btree<int> btree;
    btree.BtreeInsert(1);
    btree.BtreeInsert(2);
//    btree.BtreeInsert(3);
//    btree.BtreeInsert(4);
    btree.DFSshow();
}
void testGraph(){

    typedef adjacency_list< listS, vecS, directedS > digraph;

    // instantiate a digraph object with 8 vertices
    digraph g(8);

    // add some edges
    add_edge(0, 1, g);
    add_edge(1, 5, g);
    add_edge(5, 6, g);
    add_edge(2, 3, g);
    add_edge(2, 4, g);
    add_edge(3, 5, g);
    add_edge(4, 5, g);
    add_edge(5, 7, g);

    // represent graph in DOT format and send to cout
    write_graphviz(cout, g);

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
//    testBtreeInsert();

//    testGraph();
    return 0;
}