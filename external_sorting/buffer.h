#ifndef BUFFER_H
#define BUFFER_H

#include "page.h"
#include <vector>
#include <iostream>

using namespace std;

class buffer
{
    public:
        buffer(int, int);
        int B, pagesize;
        int B_used;
        vector <page *> bufferpages;
        vector<int> sort_existing_pages();
        void clearpages();
        void add_page(page *);
        void add_record(int);
        page *head = nullptr;
        virtual ~buffer();

    protected:

    private:
};

#endif // BUFFER_H
