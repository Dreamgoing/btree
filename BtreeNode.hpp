//
// Created by 王若璇 on 17/4/17.
//

#ifndef BTREE_BTREENODE_HPP
#define BTREE_BTREENODE_HPP

#include <vector>
#include <iostream>
#include <deque>

using namespace std;

template <class T>
class BtreeNode{

public:
    BtreeNode(){}
    BtreeNode(const T& t):key(t),num(0){}
public:
    deque<pair<T,BtreeNode*> >children;
    T key;
    size_t num;
    size_t size;
    bool leaf = false;

    ///一部分磁盘块文件

    void showNode(){
        cout<<key<<" ";
    }


};

#endif //BTREE_BTREENODE_HPP