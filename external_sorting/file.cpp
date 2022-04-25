#include "file.h"
#include <iostream>
#include <vector>
#include <cmath>
#include "page.h"
#include "buffer.h"
using namespace std;

file::file(int a,int tr,int bs)
{
    //ctor
    page_size = a;
    total_records = tr;
    B = bs;
    head = nullptr;
    total_pages=0;
    b = new buffer(B,page_size);
}

void file::status(){

    page *curr = head;
    int cc = 0;
    while(curr != nullptr){
        cc++;
        curr = curr->right;
    }
    cout << cc;
    curr = head;
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

void file::insert_record(int r){
    page *curr = head;
    while(curr != nullptr){
        int a = curr->size_remaining();
        if(a > 0){
            curr->add_record(r);
            return;
        }
        if(curr->right == nullptr)
            break;

        curr = curr->right;
    }

    page *p;
    p = new page(page_size);
    p->add_record(r);
    total_pages++;

    if(head == nullptr){
        head = p;
        return;
    }

    curr->right = p;
    p->left = curr;


}

void file::sorting(){
    int k = B-1;
    int pass =0 ;
    page* curr=head;
    while(curr != nullptr){
        for(int i=0;i<B && curr!=nullptr ;i++,curr =curr->right){
            curr->sort_and_remove_duplicates();
        }
    }
    pass++;
    cout << " Done 0th pass\n";
    mergingkway(pass, total_pages);

}

void file::mergingkway(int pass, int N){
    int k = B - 1;
    int maxpages = pow(k,(pass - 1));
    N = ceil(N/k);
    page* curr = head;
    vector<page *> current_pages;
    for(int i=0; i <= N; i++){

        for(int j = 0; j < k && curr!= nullptr;j++){
            for(int s=0; s < maxpages && curr!=nullptr; s++, curr=curr->right){
                /**<  for(auto i:curr->records)
                    cout << i << " ";
                cout << endl; */
                current_pages.push_back(curr);
                b->bufferpages.push_back(curr);
            }
        }
        cout << "check1\n";
        vector<int> result = b->sort_existing_pages();
        int c = 0;
        for(page* damn : current_pages){
            damn->records.clear();
            for(int j = 0; j < page_size && c < result.size() ; j++){
                damn->records.push_back(result[c++]);
            }
        }
        cout << "check2\n";
        b->clearpages();
        current_pages.clear();
    }


    cout << " Done "<<pass<<"th pass\n";
    if(N > 0 )
        mergingkway(pass+1,N);
    else{
        page * now = head;
        int cc=1;
        while(now != nullptr){
            for(auto i:now->records)
                    cout <<cc++<< ":" << i << " ";
            if(now->right->get_no_records() == 0)
                now->right = nullptr;
            now = now->right;
        }
        cout << endl;
    }
}
file::~file()
{
    //dtor
}
