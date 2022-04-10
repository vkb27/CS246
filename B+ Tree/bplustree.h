#ifndef BPLUSTREE_H
#define BPLUSTREE_H
#include "node.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class bplustree
{
    public:
        bplustree(int t, int d);
        int t,d;
        node *root;
        node *leaves;
        int cc;
        void add(int);
        void status();
        virtual ~bplustree();

    protected:

    private:
        vector <int> slicing(vector<int>&,int,int);
        vector <node *> slicing_pointer(vector<node *>&,int,int);
        int add_in_leaf(int,node*,node*,int,vector<node*>);
        int add_in_index(int,node*,node*,int,vector<node*>);
};

#endif // BPLUSTREE_H
