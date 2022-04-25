#include "buffer.h"
#include "page.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include"page.h"
#include <vector>
using namespace std;

buffer::buffer(int val, int ps)
{
    //ctor
    B = val;
    pagesize = ps;
    head = new page(pagesize);

}
void buffer::add_page(page* t){
    //if(bufferpages.size() < B-1)
    cout << "in";
    bufferpages.push_back(t);
    cout << "out";
}

vector<int> buffer::sort_existing_pages(){
    vector<int> dd;

    vector<int>::iterator ip;

    for(page* i: bufferpages){
        dd.insert(dd.end(), i->records.begin(), i->records.end());
    }
    sort(dd.begin(),dd.end());

    ip = std::unique(dd.begin(), dd.end());
    dd.resize(std::distance(dd.begin(), ip));
    return dd;
}

void buffer::clearpages(){
    bufferpages.clear();
}

void buffer::add_record(int r){
    page* curr;
    curr = head;
    while(curr->size_remaining() == 0){
        if(curr->right == nullptr)
            break;
        curr = curr->right;
    }
    if(curr->size_remaining() > 0){
        curr->add_record(r);
    }else if(curr->right == nullptr)
    {
        if(B_used < B){
            page* n = new page(pagesize);
            curr->right = n;
            n->left = curr;
            n->add_record(r);
            B_used++;
        }
        else{
            printf("empty buffer now\n");
        }
    }
}
buffer::~buffer()
{
    //dtor
}
