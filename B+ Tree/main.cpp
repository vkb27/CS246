#include <iostream>
#include "bplustree.h"
using namespace std;

int main()
{
    int t,d;
    cin >> d >> t;
    bplustree tree(t,d);
    bool a = true;
    while(a){
        int command;
        cin >> command;
        int val;
        switch(command){
            case 1: cin >> val; tree.add(val); break;
            case 2: tree.status(); break;
            case 3: a=false; break;
        }

    }
    cout << "Hello world!" << endl;
    return 0;
}
