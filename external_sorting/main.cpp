#include <iostream>
#include "file.h"
using namespace std;

int main()
{
    int b,s,total;
    cin >> b >> s >> total;

    file heapfile(s,total,b);

    bool a = true;
    /*while(a){
        int command;
        cin >> command;
        int v1;
        switch(command){
            case 1: cin >> v1; heapfile.insert_record(v1); break;
            case 2: heapfile.status(); break;
            case 3: cin >> v1; heapfile.search_for_record(v1); break;
            case 4: a=false; break;
        }

    }*/

    while(total--){
        int v1;
        cin >> v1;
        heapfile.insert_record(v1);
        //heapfile.status();
    }
    heapfile.sorting();
    heapfile.status();

    cout << "Hello world!" << endl;
    return 0;
}
