//
// Created by 王若璇 on 17/4/20.
//
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <fstream>
#include "Btree.hpp"
#include "BtreeNode.hpp"

#define DEBUG_SHOW_GV
using namespace std;

#ifndef BTREE_BTREEVISUALIZE_HPP
#define BTREE_BTREEVISUALIZE_HPP


class BtreeVisualize{

    ///design this class as a final class
public:
    template <class T>
    static void writeGV(const Btree<T> &btree,string filePath){
        ///copy error be caution about copy assignment
        vector<pair<int,int> > path = btree.getAllPath();
//
        vector<string> label;
        vector<string> tree;
        label.clear();
        tree.clear();
        int pos = 0;
        for(auto it:btree.getNodeVec()){
            string tmp;
            tmp.clear();
            tmp+=to_string(++pos);
            tmp+=it->getLabel();
            label.push_back(tmp);
        }
        for(auto it:path){
            string tmp;
            tmp.clear();
            tmp = to_string(it.first)+" -> "+to_string(it.second)+";";
            tree.push_back(tmp);
        }

#ifdef DEBUG_SHOW_GV
        for(auto it:label){
            cout<<it<<endl;
        }
        cout<<"\n";
        for(auto it:tree){
            cout<<it<<endl;
        }
#endif

        if(filePath.substr(filePath.length()-3,3)!=".gv"){
            cout<<"illegal file format! check again "<<endl;
        }

        fstream gv;
        gv.open(filePath);
        if(!gv.is_open()){
            gv.clear();
            gv.open(filePath,std::ios::out); ///Create file
        }
        gv<<"digraph g{ \n";
        for(auto it:label){
            gv<<it<<" \n";
        }
        gv<<"\n";
        for(auto it:tree){
            gv<<it<<" \n";
        }
        gv<<"}";




    }

};

#endif //BTREE_BTREEVISUALIZE_HPP
