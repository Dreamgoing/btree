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
    vector<BtreeNode<T>*> children;
    vector<T> keys;
    T key;
    size_t num;
    size_t size;
    bool leaf = true;

    ///一部分磁盘块文件

    void showNode(){
        for(auto it:keys){
            cout<<it<<" ";
        }
        cout<<'\n';
    }
    string getKeys(){
        string res;
        res.clear();
        res = "| ";
        for(auto it:keys){
            res+=to_string(it);
            res+=" | ";
        }
        return res;
    }


};

#endif //BTREE_BTREENODE_HPP
