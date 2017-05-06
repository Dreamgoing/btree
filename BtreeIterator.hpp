//
// Created by 王若璇 on 17/5/4.
//

#ifndef BTREE_BTREEITERATOR_HPP
#define BTREE_BTREEITERATOR_HPP

///@brief BtreeIterator class using iterator design pattern

//#include "Btree.hpp"
//#include "BtreeNode.hpp"
#include <iterator>

///@param T          Template for Btree
template <class T>
struct BtreeIterator_traits{
    typedef typename T::value_type;
    typedef typename T::pointer;
};

template <class T>
class BtreeIterator{





};



#endif //BTREE_BTREEITERATOR_HPP
