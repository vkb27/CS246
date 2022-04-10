#include "node.h"
#include <iostream>
#include <vector>
using namespace std;

node::node(int T, int D)
{
    //ctor
    t = T;
    d = D;
    isleaf = true;
    maxcap = 2*t + 1;
    maxcap_4leaf = 2*d;
    mincap =t;
    mincap_4leaf = d;
    left = nullptr;
    right = nullptr;
    parent = nullptr;

}

node::node(int T, int D, int isindex)
{
    //ctor
    t = T;
    d = D;
    left = nullptr;
    right = nullptr; parent = nullptr;
    maxcap = 2*t + 1;
    maxcap_4leaf = 2*d;
    mincap =t;
    mincap_4leaf = d;
    if(isindex == 1)
        isleaf = false;
}

bool node::isFull(){
    if(isleaf){
        return (contents.size() > maxcap_4leaf) ;
    }
    else{
        return (contents.size() > maxcap);
    }
}
node::~node()
{
    //dtor
}
