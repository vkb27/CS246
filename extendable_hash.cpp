#include "extendable_hash.h"
#include <iostream>
#include <algorithm>
#include "bucket.h"
#include <math.h>
using namespace std;

extendable_hash::extendable_hash(int gd,int b_capacity)
{
    globaldepth = gd;
    bucket * bb = nullptr;
    for(int i = 0; i < pow(2,globaldepth) ;i++){
        bb = new bucket(b_capacity,gd);

        directory.push_back(bb);
        bytime.push_back(bb);
    }
    total_buckets = (int) pow(2,globaldepth);
}

void extendable_hash::add(int n){
    string binaryNumber = "1";
    for (int i=1; i<globaldepth;i++)
        binaryNumber += "1";
    int g = stoi(binaryNumber, 0, 2);
    bucket * bb = nullptr;
    int index = n & g;
    //cout << index << endl;

    if (!directory[index]->isFull()){
        vector <int> vec = directory[index]->contents;
        if( vec.empty() || (find(vec.begin(), vec.end(), n) == vec.end()) )
            directory[index]->contents.push_back(n);
        else
            cout << "element already exists in the hash" << endl;
    }
    else if(directory[index]->localdepth == globaldepth){
        vector<int> temp;
        for(int i : directory[index]->contents){
            temp.push_back(i);
        }
        double_directory(index);
        globaldepth++;
        total_buckets++;
        //show_status();
        for(int i : temp)
            add(i);
        add(n);
    }
    else{ // localdepth < globaldepth
        cout << "localdepth < globaldepth" << endl;
        string bn2 = "1";
        int ld = directory[index]->localdepth;

        for (int i=1; i<ld;i++)
            bn2 += "1";

        int g2 = stoi(bn2, 0, 2);
        int index2 = n&g2;

        bn2 += "1";
        int gd2 = stoi(bn2, 0, 2);

        bb = new bucket(directory[index]->capacity,ld+1);
        bytime.push_back(bb);
        directory[index2]->localdepth++;
        int index3 = index2 + (int) pow(2,ld) ;

        while(index3 < pow(2,globaldepth)){
            directory[index3] = bb;
            index3 += pow(2,ld+1);
        }

        vector <int> v ;

        for(int j : directory[index2]->contents){
            v.push_back(j);
        }

        directory[index2]->contents.clear();

        total_buckets++;

        for(int i : v)
            add(i);
        add(n);
    }

}

void extendable_hash::double_directory(int index){
    int s = (int) directory.size();
    int j=0;
    bucket * bb = nullptr;
    for(int i=s;i<s*2;i++){
        if (j==index){
            j++;
            bb = new bucket(directory[index]->capacity,globaldepth);
            directory.push_back(bb);
            bytime.push_back(bb);
            directory[index]->localdepth++;
            directory[i]->localdepth++;
        }
        else directory.push_back(directory[j++]);
    }
    directory[index]->contents.clear();

}

bool extendable_hash::search_val(int n){
    string binaryNumber = "1";
    for (int i=1; i<globaldepth;i++)
        binaryNumber += "1";
    int g = stoi(binaryNumber, 0, 2);
    bucket * bb = nullptr;
    int index = n & g;

    for(int i: directory[index]->contents){
        if(i == n) {cout << "true\n"; return true;}
    }
    cout << "false\n";
    return false;
}

void extendable_hash::show_status(){
    int i =0;
    cout << "globaldepth: " << globaldepth << " no of buckets: "<<total_buckets<<endl;
    for(auto g: directory){
        cout << "ld is " << g->localdepth << "| " <<  i++ << ": " ;
        for(auto k:g->contents)
            cout << k << " ";
        cout << endl;
    }

    cout << "Buckets should be ordered in the ascending order of creation time" << endl;
    for(auto g: bytime){
        cout << "ld is " << g->localdepth << "| "
                << g->contents.size() << ": " ;
        for(auto k:g->contents) // later comment it out
            cout << k << " ";
        cout << endl;
    }
}

void extendable_hash::delete_val(int n){
    string binaryNumber = "1";
    for (int i=1; i<globaldepth;i++)
        binaryNumber += "1";
    int g = stoi(binaryNumber, 0, 2);
    bucket * bb = nullptr;
    int index = n & g;
    int flag=0;

    int ld = directory[index]->localdepth;
    string b2 = "1";
    for (int i=1; i<ld;i++)
        b2 += "1";
    int g2 = stoi(b2, 0, 2);
    int index2 = n & g2;

    int jump = pow(2,ld);

    int t = pow(2,ld-1);

    for(auto i= directory[index]->contents.begin(); i!=directory[index]->contents.end();i++){
        if(*i == n) {
            directory[index]->contents.erase(i);
            //if (! directory[index]->contents.empty() ) return;
            cout << "Ss " << directory[index]->contents.size() << " " << directory[index2 ^ t]->contents.size() << directory[index]->capacity << endl;
            if(directory[index]->contents.size() + directory[index2 ^ t]->contents.size() <= directory[index]->capacity ){
                flag = 2;

            }

            else if ( directory[index]->contents.empty() ) flag=1;
            else return;

            break;
        }
    }
    if (ld == 1) return;
    if (flag == 0) return;

    bucket * addr = directory[index2 ^ t] ;

    if(addr->localdepth > ld) return;
    cout << index2<<" " <<flag << endl;

    addr->localdepth--;

    vector<int>temp;
    if(flag == 2){
        for(int i: directory[index]->contents)
            addr->contents.push_back(i);
    }

    for(int i= 0; i<bytime.size();i++){
        if(bytime[i] == directory[index2]) {
            bytime.erase(bytime.begin()+i);
            break;
        }
    }

    for(int j =index2;j<pow(2,globaldepth);j+=jump){
        directory[j] = addr;
    }

    /*for(int j =index;j>=0;j-=jump){
        directory[j] = addr;
    }*/

    for(auto i : directory){
        if( i->localdepth == globaldepth) return;
    }

    globaldepth -= 1;

    for(int i=0;i<pow(2,globaldepth);i++){
        directory.pop_back();
    }

}

extendable_hash::~extendable_hash()
{
    //dtor
}
