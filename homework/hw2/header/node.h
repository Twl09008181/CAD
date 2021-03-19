
#ifndef node_h
#define node_h

#include<iostream>
using namespace std;

class DFG_node;
class DFG;

class node{
    friend class DFG_node;
    friend class DFG;
public:
    node(int v,node*next_node=nullptr)
        :val(v),next(next_node){}

    ~node()
    {
        cout<<"node : "<<val<<"end"<<endl;
    }
    int get_val()const{return val;}
    void show_list()const;
private:
    int val;
    node* next;
};

#endif
