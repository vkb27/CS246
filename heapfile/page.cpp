#include "page.h"
#include <iostream>
#include <vector>
using namespace std;
page::page(int a)
{
    left = nullptr;
    right = nullptr;
    page_size = a;
    count_of_records=0;
}

void page::add_record(int r,int r_size){
    records.push_back(r);
    records_size.push_back(r_size);

    count_of_records++;
}

int page::search_record(int val){
    int index = 0 ;
    for(int i : records){
        if(i == val){
            return index;
        }
        index++;
    }
    return -1;
}

int page::size_remaining(){
    int a = records.size() * 4;
    for(int i: records_size){
        a += i;
    }
    a += 16; // free space pointer + counter

    cout <<"Size remaining: "<< page_size - a << endl;
    return page_size-a;
}

page::~page()
{
    //dtor
}
