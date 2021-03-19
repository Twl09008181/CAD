
#include "../header/DFG_node.h"


//DFG_node
void DFG_node::add_child(node_value n)
{
    if(!child_number){
        this->vertex.next = new node(n);
    }
    else{
        this->vertex.next = new node(n,this->vertex.next);
    }
    child_number++;
}


void DFG_node::add_parent(node_value n)
{
    if(!parent_number){
        parent = new node(n);
    }
    else{
        parent = new node(n,parent);//加在第一位
    }
    parent_number++;
}

