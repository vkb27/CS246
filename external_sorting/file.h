#ifndef FILE_H
#define FILE_H
#include "page.h"
#include "buffer.h"
#include <vector>
using namespace std;
class file
{
    public:
        file(int,int,int);
        int total_records;
        int B;
        buffer * b;
        vector <vector<page *>> runs;
        int page_size;
        page *head;
        int total_pages;
        void status();
        void search_for_record(int);
        void mergingkway(int pass, int N);
        void insert_record(int);
        virtual ~file();
        void sorting();

    protected:

    private:
};


#endif // FILE_H
