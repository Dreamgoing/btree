//
// Created by 王若璇 on 17/4/17.
//

#ifndef BTREE_BTREE_HPP
#define BTREE_BTREE_HPP

#include "BtreeNode.hpp"
#include "BtreeIterator.hpp"
#include <cassert>
#include <queue>
#include <map>
//#include <boost/graph/adjacency_list.hpp>
//#include <boost/graph/graphviz.hpp>
///@todo thinking in how to use more advanced c++ programming skill
///@todo how to implement the iterator of the Btree
///@todo thinking use smart ptr  to manager memory

using namespace std;
//using namespace boost;


///friend function need forward declaration
template<class T>
void visitNode_(shared_ptr<BtreeNode<T> > node);


template<class T>
class Btree {


public:
    ///type
    typedef T value_type;
    typedef BtreeNode<T>* pointer;
    typedef typename vector<pointer>::iterator btree_iterator;

private:
//    typedef typename BtreeNode<T>::
    shared_ptr<BtreeNode<T> > root;

    mutable map<shared_ptr<BtreeNode<T> >, int> nodeID;

    ///ordered result
    mutable vector<shared_ptr<BtreeNode<T> >> nodeVec;

    mutable vector<BtreeNode<T>* >nodeptrVec;
public:
    const vector<shared_ptr<BtreeNode<T> > > &getNodeVec() const;

    void setNodeVec(const vector<shared_ptr<BtreeNode<T> >> &nodeVec);

private:

    int degree = 3;
    ///degree default construction set t = 3
    ///@details: the maximum number of keys,and the keys current node contains range from [degree/2]-1 to degree-1
    ///nil


    ///lazy flag
    int nodeNum = 0;

    bool updated = false;


private:
//public:
    void showNode_(shared_ptr<BtreeNode<T> > node, int step, void (*func)(shared_ptr<BtreeNode<T> >));

    void BtreeSpilt_(shared_ptr<BtreeNode<T> > x, int pos, shared_ptr<BtreeNode<T> > y);

    void BtreeInsertNonfull_(shared_ptr<BtreeNode<T> > x, const T &k);

    void updateNodeID_();

    void updatenodeVec_();

    void mapNode_(shared_ptr<BtreeNode<T> > node);

    friend void visitNode_(shared_ptr<BtreeNode<T> > node);

public:
    Btree(int t = 3);

    pair<shared_ptr<BtreeNode<T> >, T> BtreeSearch(shared_ptr<BtreeNode<T> > now, const T &k);

    void BtreeCreate();

    void BFSshow();

    void DFSshow();

    void BtreeInsert(const T &k);

    void showBTree();

    int getNodeID(shared_ptr<BtreeNode<T> > node) const;

    const vector<pair<int, int> > getAllPath() const;

    int getDegree();

    shared_ptr<BtreeNode<T> > getBtreeNode(int id);

    void BtreeDelete(const T &k);



    ///@todo destroy tree

};

template<class T>
pair<shared_ptr<BtreeNode<T> >, T> Btree<T>::BtreeSearch(shared_ptr<BtreeNode<T> > now, const T &k) {
    if (now == nullptr) {
        ///not found
        return make_pair(nullptr, -1);
    }
    ///can use b_search

    int pos = 0;
    while (pos < now->keys.size() && k > now->keys[pos].first) {
        pos++;
    }
    if (pos < now->keys.size() && k == now->keys[pos].first) {
        ///found
        return now->keys[pos];
    }

    if (now->leaf) {
        ///not found
        return make_pair(nullptr, -1);
    } else {
        ///first Disk-read(now->keys[pos])
        return BtreeSearch(now->keys[pos], k);
    }


}


///@todo consider how to pass a function to implement traversal
template<class T>
void Btree<T>::BFSshow() {
    queue<shared_ptr<BtreeNode<T> >> qu;
    qu.push(root);
    while (!qu.empty()) {
        shared_ptr<BtreeNode<T> > now = qu.front();
        now->showNode();
        qu.pop();
        for (auto it:now->keys) {
            qu.push(it.second);
        }
    }
}


template<class T>
void Btree<T>::showNode_(shared_ptr<BtreeNode<T> > node, int step, void (*func)(shared_ptr<BtreeNode<T> >)) {
    if (node == nullptr) {
        return;
    }
    if (!updated) {
        if (nodeID.find(node) == nodeID.end()) {
            nodeID[node] = ++nodeNum;
        }
    }
    for (int i = 0; i < step; i++) {
        cout << "  ";
    }
    func(node);
    for (auto it:node->children) {
        showNode_(it, step + 1, func);
    }

}

template<class T>
Btree<T>::Btree(int degree):degree(degree) {

    ///@param degree:the maximum number of keys
    root = nullptr;
    BtreeCreate();
}

template<class T>
void Btree<T>::BtreeCreate() {
    if (root == nullptr) {
        root = make_shared<BtreeNode<T> >();
        nodeNum++;
    }
    root->leaf = true;
    root->num = 0;

    ///Disk-Write(x)
}

template<class T>
void Btree<T>::DFSshow() {
    void (*ptr)(shared_ptr<BtreeNode<T> >);
    ptr = &visitNode_;
    ///如果试图使用c++的成员函数作为回调函数，则会发生错误
    ///使用回调函数的解决方案通常是使用友元，或使用静态成员函数
    ///在设计这个问题上面，还可以使用仿函数等。


    nodeNum = updated ? nodeNum : 0;
    ///@todo rename traversal
    showNode_(root, 0, ptr);
    updatenodeVec_();


}

template<class T>
void Btree<T>::BtreeSpilt_(shared_ptr<BtreeNode<T> > x, int pos, shared_ptr<BtreeNode<T> > y) {
    /**
     * @param
     * x:a nonfull internal node(parent node)
     * pos:an index
     * y:a node which is a full child of x
     * */

    shared_ptr<BtreeNode<T> > newNode = make_shared<BtreeNode<T> >();
    nodeNum++;
    newNode->leaf = y->leaf;
    ///newNode resize
    newNode->keys.resize(degree / 2);
//    cerr<<y->keys.size()<<endl;
    for (int i = 0; i < degree / 2; i++) {
        newNode->keys[i] = y->keys[i];
    }
    newNode->num = newNode->keys.size();
    ///or to resize newNode size
    newNode->children.resize((unsigned long) (degree / 2 + 1));
    if (!y->leaf) {
        for (int i = 0; i <= degree / 2; i++) {
            newNode->children[i] = y->children[i];
        }
    }

    ///get pushup key
    T upKey = y->keys[degree / 2];

//    cout<<upKey<<endl;

    ///reassign node y
    vector<T> tmpKeys;
    tmpKeys.clear();
    for (int i = degree / 2 + 1; i < degree - 1; i++) {
        tmpKeys.push_back(y->keys[i]);
    }
    vector<shared_ptr<BtreeNode<T> > > tmpChildren;
    tmpChildren.clear();

    ///memory error
    if (!y->leaf) {
        for (int i = degree / 2 + 1; i < degree; i++) {
            tmpChildren.push_back(y->children[i]);
        }
    }

    y->keys = tmpKeys;
    y->children = tmpChildren;


//    cout<<upKey<<endl;
    newNode->num = newNode->keys.size();
    y->num = y->keys.size();

    ///insert newNode and key into x->children
    x->children.insert(x->children.begin() + pos, newNode);
    x->keys.insert(x->keys.begin() + pos, upKey);

    ///fix x->num
    assert(x->num + 1 == x->keys.size());

    x->num = x->num + 1;

    ///or
    x->num = x->keys.size();


    ///Disk-Write(y)
    ///Disk-Write(z)
    ///Disk-Write(x)





}

template<class T>
void Btree<T>::BtreeInsert(const T &k) {
    shared_ptr<BtreeNode<T> > tmpRoot = root;
    if (tmpRoot->num == degree - 1) {
        shared_ptr<BtreeNode<T> > node(make_shared<BtreeNode<T> >());
        nodeNum++;

        root = node;
        node->leaf = false;
        node->children.push_back(tmpRoot);
//        cout<<"ok"<<endl;
        BtreeSpilt_(node, 0, tmpRoot);
        BtreeInsertNonfull_(node, k);
    } else {
        BtreeInsertNonfull_(tmpRoot, k);
    }

}

template<class T>
int Btree<T>::getDegree() {

    return degree;
}

template<class T>
void Btree<T>::BtreeInsertNonfull_(shared_ptr<BtreeNode<T> > x, const T &k) {
    ///use std::deque finish insert


    int pos = 0;

    ///found the index which should be insert
    for (auto it:x->keys) {
        if (it > k) {
            break;
        }
        pos++;
    }
    if (x->leaf) {
        ///插入一个节点最终插入到叶子节点的父节点上面去
        ///x为叶节点时，直接插入，因为之前已经可能进行过分割操作，保证了叶节点不满
        x->keys.insert(x->keys.begin() + pos, k);
        x->num = x->keys.size();
        ///Disk-Read(x)
    } else {
        ///Disk-Read(it)
        shared_ptr<BtreeNode<T> > child = x->children[pos];
        if (child == nullptr) {
            ///error
            cerr << "child is nullptr " << endl;
            return;
        }
        if (child->num == degree - 1) {
            ///spilt child
            BtreeSpilt_(x, pos, child);

            if (k > x->keys[pos]) {
                pos++;
            }
        }
        BtreeInsertNonfull_(x->children[pos], k);
    }

}

template<class T>
void Btree<T>::showBTree() {
//    typedef  adjacency_list< listS, vecS, undirectedS > undirectedGraph;
//    undirectedGraph graph1;

}

template<class T>

const vector<pair<int, int> > Btree<T>::getAllPath() const {
    vector<pair<int, int> > res;
    res.clear();
    queue<shared_ptr<BtreeNode<T> >> qu;
    qu.push(root);

    cerr << "nodeID->size: " << nodeID.size() << endl;
    ///BFS traversal

    while (!qu.empty()) {
        shared_ptr<BtreeNode<T> > now = qu.front();
        qu.pop();
        int nowID = getNodeID(now);
        for (auto it:now->children) {
            if (it == nullptr) {
                ///@bug iterator may be nullptr
//                cout<<"NULL"<<endl;
                continue;
            }
            int dstID = getNodeID(it);
            res.push_back(make_pair(nowID, dstID));
            qu.push(it);
        }
    }
    return res;

}

template<class T>
void Btree<T>::updatenodeVec_() {
    nodeVec.clear();
    int num = static_cast<int>(nodeID.size());

    ///ensure nums equal
    assert(num == nodeNum);
    nodeVec.resize(static_cast<unsigned long>(num));
    for (auto it:nodeID) {
        nodeVec[it.second - 1] = it.first;
    }


}

template<class T>
void Btree<T>::updateNodeID_() {
    nodeVec.clear();
    int id = 1;
    ///traversal
    queue<shared_ptr<BtreeNode<T> > > qu;
    qu.push(root);


}

template<class T>
int Btree<T>::getNodeID(shared_ptr<BtreeNode<T> > node) const {
    auto it = nodeID.find(node);
    if (it == nodeID.end()) {
        return -1;
    } else {
        return it->second;
    }
}

template<class T>
void Btree<T>::mapNode_(shared_ptr<BtreeNode<T> > node) {
    if (nodeID.find(node) == nodeID.end()) {
        nodeID[node] = ++nodeNum;
    }
}


template<class T>
void visitNode_(shared_ptr<BtreeNode<T> > node) {
    node->showNode();
}

template<class T>
shared_ptr<BtreeNode<T> > Btree<T>::getBtreeNode(int id) {
    return nodeVec[id - 1];
}

template<class T>
const vector<shared_ptr<BtreeNode<T> >> &Btree<T>::getNodeVec() const {
    return nodeVec;
}

template<class T>
void Btree<T>::setNodeVec(const vector<shared_ptr<BtreeNode<T> >> &nodeVec) {
    Btree::nodeVec = nodeVec;
}

template<class T>
void Btree<T>::BtreeDelete(const T &k) {

}



#endif //BTREE_BTREE_HPP
