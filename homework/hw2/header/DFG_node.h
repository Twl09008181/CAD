

#ifndef DFG_NODE_H
#define DFG_NODE_H

#include<iostream>
using namespace std;
#include"node.h"

class DFG_node{
    friend class DFG;
public:
    using operation_type = char;
    using node_value = unsigned;
    DFG_node(node_value v,operation_type t)
        :vertex(v),T{t}{}
    
    void add_child(node_value n);
    void add_parent(node_value n);
    int get_val()const{return vertex.get_val();}
    operation_type get_type()const{return T;}
    void show_child()const{vertex.show_list();};
    void show_parent()const{
        if(parent){
            cout<<parent->get_val()<<" ";
            parent->show_list();
        }
    }

private:
    operation_type T;
    node vertex;
    node *parent = nullptr;
    unsigned int child_number = 0;
    unsigned int parent_number = 0;
    bool no_child(){return child_number == 0;}
    bool no_parent(){return parent_number == 0;}
};

#endif
