#include "bplustree.h"
#include "node.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bplustree::bplustree(int T, int D)
{
    //ctor
    t = T;
    d =D;
    root = nullptr;
    leaves = nullptr;
    cc = 0;
}

void bplustree::add(int val){
    if(root == nullptr){
        if(leaves == nullptr){
            node *curr;
            curr = new node(t,d);
            curr->contents.push_back(val);
            sort(curr->contents.begin(),curr->contents.end());
            leaves = curr;
        }
        else{
            leaves->contents.push_back(val);
            sort(leaves->contents.begin(),leaves->contents.end());

            if(leaves->isFull()){
                //cout << "1st leaf is full\n";
                root = new node(t,d,1);
                node *curr1;node *curr2;
                curr1 = new node(t,d); curr2 = new node(t,d);
                vector<int> temp2 = slicing(leaves->contents,d,2*d);

                curr2->contents.insert(curr2->contents.end(), temp2.begin(), temp2.end());
                vector<int> temp1 = slicing(leaves->contents,0,d-1);
                curr1->contents.insert(curr1->contents.end(), temp1.begin(), temp1.end());
                curr1->right = curr2; curr2->left=curr1;

                leaves = curr1;
                root->contents.push_back(curr2->contents[0]);
                root->pointer.push_back(curr1); root->pointer.push_back(curr2);
                cc++;
            }
        }
    }
    else{
        node *next = root;
        node *parent = root;
        int index=-1;
        vector<node *> ancestors;
        while(! next->isleaf){
            parent = next;
            ancestors.push_back(parent);
            if(val >= parent->contents[parent->contents.size()-1]){
                next = parent->pointer[parent->pointer.size()-1];
                index = parent->pointer.size()-1;
            }
            else
                for(int i=0; i<parent->contents.size();i++){
                    if(val<parent->contents[i]){
                        //cout << parent->contents[i] << " crying\n";
                        next = parent->pointer[i];
                        index = i;
                        break;
                    }
                }
        }
        add_in_leaf(val,next,parent,index,ancestors);
    }
}

int bplustree::add_in_leaf(int val, node *leaf, node *parent,int index,vector<node*> ancestors){
    leaf->contents.push_back(val);
    sort(leaf->contents.begin(),leaf->contents.end());
    int a = -1;
    if(leaf->isFull()){
        node *curr1;node *curr2;
        curr1 = new node(t,d); curr2 = new node(t,d);
        vector<int> temp2 = slicing(leaf->contents,d,2*d);
        curr2->contents.insert(curr2->contents.end(), temp2.begin(), temp2.end());
        vector<int> temp1 = slicing(leaf->contents,0,d-1);
        curr1->contents.insert(curr1->contents.end(), temp1.begin(), temp1.end());
        curr1->right = curr2; curr2->left=curr1;

        node *t1 = leaf->left; node *t2 = leaf->right;
        if(t1 == nullptr){
            leaves =curr1;
        }
        else{
            t1->right = curr1;
            curr1->left = t1;
        }
        curr2->right = t2;
        if(t2 != nullptr){
            t2->left = curr2;
        }
        a = curr2->contents[0];
        //cout << "pushing up "<<a<< "\n";
        add_in_index(a,curr1,parent,index,ancestors);
    }
    //return a;
}

int bplustree::add_in_index(int val,node* first, node* parent, int index, vector<node *> ancestors){
    ancestors.pop_back();
    if(first->isleaf){
        parent->pointer[index] = first;
        parent->pointer.insert( parent->pointer.begin() + index + 1, first->right);
    }

    parent->contents.push_back(val);
    sort(parent->contents.begin(),parent->contents.end());

    if(! parent->isFull() ){
        return 1;
    }
    else{
        /*for(auto i:parent->contents){
            cout << i << " " ;
        }cout<<endl;
        for(auto i:ancestors){
            for(auto j:i->contents){
                cout << j << " " ;
            }cout<<endl;
        }cout<<endl;*/

        node *p1,*p2;

        p1 = new node(t,d,1);
        p2 = new node(t,d,1);

        vector<int> temp1 = slicing(parent->contents,0,t-1);
        p1->contents.insert(p1->contents.end(), temp1.begin(), temp1.end());

        vector<int> temp2 = slicing(parent->contents,t+1,2*t+1);
        p2->contents.insert(p2->contents.end(), temp2.begin(), temp2.end());

        vector<node *> ptemp1 = slicing_pointer(parent->pointer,0,t);
        p1->pointer.insert(p1->pointer.end(), ptemp1.begin(), ptemp1.end());

        vector<node *> ptemp2 = slicing_pointer(parent->pointer,t+1,2*t+2);
        p2->pointer.insert(p2->pointer.end(), ptemp2.begin(), ptemp2.end());

        if (ancestors.size() == 0){
            root = new node(t,d,1);
            root->contents.push_back(parent->contents[t]);
            root->pointer.push_back(p1);
            root->pointer.push_back(p2);
            cc+=2;
        }
        else{
            int index2=-1;
            node * grandparent = ancestors.back();
            for(int i=0;i<grandparent->pointer.size();i++){
                if(grandparent->pointer[i] == parent){
                    //cout << "0\n";
                    index2=i;
                    //cout << "1\n";
                    grandparent->pointer[i] = p1;
                    //cout << "2\n";
                    grandparent->pointer.insert( grandparent->pointer.begin() + index2 + 1, p2);
                }
            }
            cc++;
            add_in_index(parent->contents[t],parent,grandparent,index2,ancestors);
        }
    }

}

vector<int> bplustree::slicing(vector<int>& arr,int X, int Y)
{

    // Starting and Ending iterators
    auto start = arr.begin() + X;
    auto end = arr.begin() + Y + 1;

    // To store the sliced vector
    vector<int> result(Y - X + 1);

    // Copy vector using copy function()
    copy(start, end, result.begin());

    // Return the final sliced vector
    return result;
}

vector<node *> bplustree::slicing_pointer(vector<node *>& arr,int X, int Y)
{

    // Starting and Ending iterators
    auto start = arr.begin() + X;
    auto end = arr.begin() + Y + 1;

    // To store the sliced vector
    vector<node *> result(Y - X + 1);

    // Copy vector using copy function()
    copy(start, end, result.begin());

    // Return the final sliced vector
    return result;
}

void bplustree::status(){
    int c_nodes=0,c_leaves=0;
    cout<<"no of index nodes "<<cc;
    node * curr = leaves;
    while(curr != nullptr){
        for(auto i:curr->contents) {
            c_leaves++;
            //cout<<i<<" ";
        }
        c_nodes++;
        curr = curr->right;
        //cout << "| ";
    }
    cout <<" no of data nodes "<< c_nodes <<" | ";
    cout << "in root: ";
    if(root != nullptr)
        for(auto i:root->contents){
            cout << i << " " ;
        }
    else{
        //cout << "root is null ";
        for(auto i:leaves->contents){
            cout << i << " " ;
        }
    }
    cout << endl;
}
bplustree::~bplustree()
{
    //dtor
}
