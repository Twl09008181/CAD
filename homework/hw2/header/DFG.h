
#ifndef DFG_H
#define DFG_H

#include<iostream>
#include<vector>
#include<map>
using namespace std;


#include"DFG_node.h"
class DFG{
public:
    using operation_type = char;
    using index = unsigned;
    using node_value = unsigned;
    DFG(int n){V.reserve(n);}
 
    void add_node(node_value n,operation_type t);
    void add_edge(node_value n1,node_value n2);
    void show_node()const{
        for(auto n:V)
            cout<<"type = "<<n->get_type()<<" val = "<<n->get_val()<<endl;
    }
    void show_DFG()const;
private:
    map<node_value,index>Decode;
    vector<DFG_node*> V;
};

#endif


