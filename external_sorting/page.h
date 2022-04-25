#ifndef PAGE_H
#define PAGE_H


#include <vector>
using namespace std;
class page
{
    public:
        page(int);
        page *left;
        page *right;
        int get_no_records(){ return records.size(); }; // summation of Ri + 4 * number_of_records
        int count_of_records; // 4 bytes
        int page_size;
        vector <int> records;
        vector <int> records_size;
        int size_remaining();
        int search_record(int);
        void add_record(int);

        void sort_and_remove_duplicates();
        // every pointer -> 4 bytes
        virtual ~page();

    protected:

    private:
};


#endif // PAGE_H
