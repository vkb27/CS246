#include "file.h"
#include <iostream>
#include <vector>
#include "page.h"
using namespace std;

file::file(int a)
{
    //ctor
    page_size = a;
    head = nullptr;
    total_pages=0;
}

void file::status(){
    cout << total_pages;
    page *curr = head;
    while(curr != nullptr){
        cout << " " << curr->get_no_records();
        curr = curr->right;
    }
    cout << endl;
}

void file::search_for_record(int val){

    int page_id=0;
    page *curr = head;
    while(curr != nullptr){
        int a = curr->search_record(val);
        if(a != -1){
            cout << page_id << " " << a << endl;
            return;
        }
        page_id++;
        curr = curr->right;
    }
    cout << "-1 -1\n";
    return;
}

void file::insert_record(int r,int r_size){
    page *curr = head;
    while(curr != nullptr){
        int a = curr->size_remaining();
        if(a >= r_size + 4){
            curr->add_record(r,r_size);
            return;
        }
        if(curr -> right == nullptr)
            break;
    }

    page *p;
    p = new page(page_size);
    p->add_record(r,r_size);
    total_pages++;

    if(curr == nullptr){
        head = p;
        return;
    }
    curr->right = p;
    p->left = curr;


}

file::~file()
{
    //dtor
}
