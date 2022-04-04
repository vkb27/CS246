#include "bucket.h"
#include <vector>
using namespace std;
bucket::bucket(int n,int ld)
{
    capacity = n;
    localdepth = ld;

}

bool bucket::isFull(){
    if(capacity == (int)contents.size()){
        return true;
    }
    return false;
}

int * bucket::getAddr(){
    return  contents.empty() ? nullptr : &contents[0];
}


bucket::~bucket()
{
    //dtor
}
