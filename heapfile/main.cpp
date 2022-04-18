#include <iostream>
#include "file.h"
using namespace std;

int main()
{
    int s;
    cin >> s;
    file heapfile(s);
    bool a = true;
    while(a){
        int command;
        cin >> command;
        int v1,v2;
        switch(command){
            case 1: cin >> v1 >> v2; heapfile.insert_record(v2,v1); break;
            case 2: heapfile.status(); break;
            case 3: cin >> v1; heapfile.search_for_record(v1); break;
            case 4: a=false; break;
        }

    }
    cout << "Hello world!" << endl;
    return 0;
}
