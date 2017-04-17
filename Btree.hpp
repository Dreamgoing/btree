//
// Created by 王若璇 on 17/4/17.
//

#ifndef BTREE_BTREE_HPP
#define BTREE_BTREE_HPP

#include "BtreeNode.hpp"
#include <queue>

///@todo thinking in how to use more advanced c++ programming skill

using namespace std;

template <class T>
class Btree {

private:
    BtreeNode<T>* root;
    int degree = 3;
    ///degree default construction set t = 3

    ///nil


private:
    void showNode_(BtreeNode<T>* node,int step);

    void BtreeSpilt_(BtreeNode<T>* x,int pos,BtreeNode<T>* y);

    void BtreeInsertNonfull_(BtreeNode<T>* x,const T& k);


public:
    Btree(int t = 3);
    pair<BtreeNode<T>*,T> BtreeSearch(BtreeNode<T> *now,const T& k);
    void BtreeCreate();
    void BFSshow();
    void DFSshow();
    void BtreeInsert(BtreeNode<T>* now,const T& k);

    int getDegree();

};

template <class T>
pair<BtreeNode<T>*, T> Btree<T>::BtreeSearch(BtreeNode<T> *now, const T &k) {
    if(now== nullptr){
        ///not found
        return make_pair(nullptr,-1);
    }
    ///can use b_search
    int pos = 0;
    while (pos<now->children.size()&&k>now->children[pos].first){
        pos++;
    }
    if(pos<now->children.size()&&k==now->children[pos].first){
        ///found
        return now->children[pos];
    }

    if(now->leaf){
        ///not found
        return make_pair(nullptr,-1);
    } else{
        ///first Disk-read(now->children[pos])
        return BtreeSearch(now->children[pos],k);
    }


}

template <class T>
void Btree<T>::BFSshow() {
    queue<BtreeNode<T>*> qu;
    qu.push(root);
    while (!qu.empty()){
        BtreeNode<T>* now = qu.front();
        now->showNode();
        qu.pop();
        for(auto it:now->children){
            qu.push(it.second);
        }
    }
}

template <class T>
void Btree<T>::showNode_(BtreeNode<T> *node,int step) {
    if(node== nullptr){
        return;
    }
    for(int i = 0;i<step;i++){
        cout<<"  ";
    }
    node->showNode();
    for(auto it:node->children){
        showNode_(it.second,step+1);
    }

}

template <class T>
Btree<T>::Btree(int degree):degree(degree) {

    ///@param degree:the maximum number of children
    root = nullptr;
    BtreeCreate();
}

template <class T>
void Btree<T>::BtreeCreate() {
    if(root== nullptr){
        root = new BtreeNode<T>();
    }
    root->leaf = true;
    root->num = 0;

    ///Disk-Write(x)
}

template <class T>
void Btree<T>::DFSshow() {
    showNode_(root,0);

}

template <class T>
void Btree<T>::BtreeSpilt_(BtreeNode<T> *x, int pos, BtreeNode<T> *y) {
    /**
     * @param
     * x:a nonfull internal node(parent node)
     * pos:an index
     * y:a node which is a full child of x
     * */

    BtreeNode<T>* newNode = new BtreeNode<T>();
    newNode->leaf = y->leaf;
    newNode->num = (size_t)degree-1;

}

template <class T>
void Btree<T>::BtreeInsert(BtreeNode<T> *now, const T &k) {

}

template <class T>
int Btree<T>::getDegree() {

    return degree;
}

template <class T>
void Btree::BtreeInsertNonfull_(BtreeNode<T> *x, const T &k) {
    ///use std::deque finish insert
    auto it;
    for(it:x->children){
        if(it.first>k){
            break;
        }
    }
    x->children.insert(it,make_pair(k,new BtreeNode));
    x->num = x->children.size();
}


#endif //BTREE_BTREE_HPP
