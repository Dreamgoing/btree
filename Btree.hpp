//
// Created by 王若璇 on 17/4/17.
//

#ifndef BTREE_BTREE_HPP
#define BTREE_BTREE_HPP

#include "BtreeNode.hpp"
#include <cassert>
#include <queue>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
///@todo thinking in how to use more advanced c++ programming skill

using namespace std;
using namespace boost;

template <class T>
class Btree {

private:
    BtreeNode<T>* root;


    int degree = 3;
    ///degree default construction set t = 3
    ///@details: the maximum number of keys,and the keys current node contains range from [degree/2]-1 to degree-1
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
    void BtreeInsert(const T& k);
    void showBTree();

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
    while (pos<now->keys.size()&&k>now->keys[pos].first){
        pos++;
    }
    if(pos<now->keys.size()&&k==now->keys[pos].first){
        ///found
        return now->keys[pos];
    }

    if(now->leaf){
        ///not found
        return make_pair(nullptr,-1);
    } else{
        ///first Disk-read(now->keys[pos])
        return BtreeSearch(now->keys[pos],k);
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
        for(auto it:now->keys){
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
        showNode_(it,step+1);
    }

}

template <class T>
Btree<T>::Btree(int degree):degree(degree) {

    ///@param degree:the maximum number of keys
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
    ///newNode resize
    newNode->keys.resize(degree/2);
//    cerr<<y->keys.size()<<endl;
    for(int i = 0;i<degree/2;i++){
        newNode->keys[i] = y->keys[i];
    }
    newNode->num = newNode->keys.size();
    ///or to resize newNode size
    newNode->children.resize((unsigned long) (degree / 2 + 1));
    if(!y->leaf){
        for(int i =0;i<=degree/2;i++){
            newNode->children[i]=y->children[i];
        }
    }

    ///get pushup key
    T upKey = y->keys[degree/2];

//    cout<<upKey<<endl;

    ///reassign node y
    vector<T> tmpKeys;
    tmpKeys.clear();
    for(int i = degree/2+1;i<degree-1;i++){
        tmpKeys.push_back(y->keys[i]);
    }
    vector<BtreeNode<T>* >tmpChildren;
    tmpChildren.clear();

    ///memory error
    if(!y->leaf){
        for(int i = degree/2+1;i<degree;i++){
            tmpChildren.push_back(y->children[i]);
        }
    }

    y->keys = tmpKeys;
    y->children = tmpChildren;


//    cout<<upKey<<endl;
    newNode->num = newNode->keys.size();
    y->num = y->keys.size();

    ///insert newNode and key into x->children
    x->children.insert(x->children.begin()+pos,newNode);
    x->keys.insert(x->keys.begin()+pos,upKey);

    ///fix x->num
    assert(x->num+1==x->keys.size());

    x->num = x->num+1;

    ///or
    x->num = x->keys.size();


    ///Disk-Write(y)
    ///Disk-Write(z)
    ///Disk-Write(x)





}

template <class T>
void Btree<T>::BtreeInsert(const T &k) {
    BtreeNode<T>* tmpRoot = root;
    if(tmpRoot->num==degree-1){
        BtreeNode<T>* node = new BtreeNode<T>;
        root = node;
        node->leaf = false;
        node->children.push_back(tmpRoot);
//        cout<<"ok"<<endl;
        BtreeSpilt_(node,0,tmpRoot);
        BtreeInsertNonfull_(node,k);
    } else{
        BtreeInsertNonfull_(tmpRoot,k);
    }

}

template <class T>
int Btree<T>::getDegree() {

    return degree;
}

template <class T>
void Btree<T>::BtreeInsertNonfull_(BtreeNode<T> *x, const T &k) {
    ///use std::deque finish insert


    int pos = 0;

    ///found the index which should be insert
    for(auto it:x->keys){
        if(it>k){
            break;
        }
        pos++;
    }
    if(x->leaf){
        ///插入一个节点最终插入到叶子节点的父节点上面去
        ///x为叶节点时，直接插入，因为之前已经可能进行过分割操作，保证了叶节点不满
        x->keys.insert(x->keys.begin()+pos,k);
        x->num = x->keys.size();
        ///Disk-Read(x)
    } else{
        ///Disk-Read(it)
        BtreeNode<T>* child = x->children[pos];
        if(child== nullptr){
            ///error
            cerr<<"child is nullptr "<<endl;
            return;
        }
        if(child->num==degree-1){
            ///spilt child
            BtreeSpilt_(x,pos,child);

            if(k>x->keys[pos]){
                pos++;
            }
        }
        BtreeInsertNonfull_(x->children[pos],k);
    }

}

template <class T>
void Btree<T>::showBTree() {
    typedef  adjacency_list< listS, vecS, undirectedS > undirectedGraph;
    undirectedGraph graph1;

}


#endif //BTREE_BTREE_HPP
