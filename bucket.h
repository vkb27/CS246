#ifndef BUCKET_H
#define BUCKET_H

#include <vector>
using namespace std;
class bucket
{
    public:
        bucket(int,int);
        virtual ~bucket();
        bool isFull();
        int * getAddr();
        vector<int> contents;
        int localdepth;
        int capacity;

    protected:


    private:
};

#endif // BUCKET_H
