#ifndef EXTENDABLE_HASH_H
#define EXTENDABLE_HASH_H

#include <iostream>
#include "bucket.h"

using namespace std;

class extendable_hash
{
    public:
        extendable_hash(int,int);
        vector <bucket * > directory;
        vector <bucket * > bytime;
        int globaldepth;
        void add(int);
        bool search_val(int);
        void show_status();
        void delete_val(int);
        virtual ~extendable_hash();
        int total_buckets;

    protected:

    private:
        void double_directory(int);

};

#endif // EXTENDABLE_HASH_H
