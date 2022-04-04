#include <iostream>
#include "bucket.h"
#include "extendable_hash.h"
using namespace std;

int main()
{
    int globaldepth, bucket_capacity;
    cin >> globaldepth >> bucket_capacity;
    extendable_hash hashtab(globaldepth,bucket_capacity);
    bool a=true;
    while(a){
        int command;
        cin >> command;
        int val;
        switch(command){
            case 2: cin >> val; hashtab.add(val); break;
            case 3: cin >> val; hashtab.search_val(val); break;
            case 4: cin >> val; hashtab.delete_val(val); break;
            case 5: hashtab.show_status(); break;
            case 6: a=false; break;
        }
    }
    cout << "Hello world!" << endl;
    return 0;
}
