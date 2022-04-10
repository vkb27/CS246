#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <vector>
using namespace std;

class node
{
    public:
        node(int,int);
        node(int,int,int);
        bool isleaf;
        int t;
        int d;
        int maxcap = 2*t + 1;
        int maxcap_4leaf = 2*d;
        int mincap =t;
        int mincap_4leaf = d;
        vector <int> contents;
        vector <node *> pointer;
        node * parent;

        bool isFull();
        int splitleaf();
        int splitnode();

        node * left;
        node * right;
        virtual ~node();

    protected:

    private:
};

#endif // NODE_H
