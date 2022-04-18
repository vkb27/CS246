#ifndef FILE_H
#define FILE_H
#include "page.h"

#include <vector>
using namespace std;
class file
{
    public:
        file(int);
        int page_size;
        page *head;
        int total_pages;
        void status();
        void search_for_record(int);
        void insert_record(int,int);
        virtual ~file();

    protected:

    private:
};

#endif // FILE_H
