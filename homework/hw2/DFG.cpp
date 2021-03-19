
#include"DFG.h"


//node
void node::show_list()const
{
    for(node*ptr = next;ptr;ptr=ptr->next)cout<<ptr->get_val()<<" ";
}

//DFG_node
void DFG_node::add_next(node*& head,unsigned int &len,node_value n)
{
    if(!head)
        head = new node(n);
    else
        head = new node(n,head);
    len++;
}
//DFG
void DFG::add_node(node_value n,operation_type t)
{
    DFG_node *node = new DFG_node{n,t};

    if(Decode.find(n)==Decode.end()){
        Decode[n] = V.size();//加入map當中
        V.push_back(node);
    }
    else{
        cerr<<"repeat node number : "<<n<<"in DFG"<<endl;
        exit(1);
    }
}
void DFG::add_edge(node_value n1,node_value n2)
{
    index i = Decode[n1];V[i]->add_child(n2);
    index j = Decode[n2];V[j]->add_parent(n1); 
}



//若member function可以call function pointer就好了
// void DFG::list_description()const{
// }


void DFG::show_DFG()const{

    cout<<"child part : "<<endl;
    for(auto n:V)
    {
        int child_number = n->child_number;
        if(child_number){
            cout<<"node : "<<n->get_val()<<" has "<<child_number<<" child : ";
            n->show_child();
        }
        else{
            cout<<"node : "<<n->get_val()<<" has no child";
        }
        cout<<endl;
    }

    cout<<"parent part : "<<endl;

    for(auto n:V)
    {
        int parent_number = n->parent_number;
        if(parent_number)
        {
            cout<<"node : "<<n->get_val()<<" has "<<parent_number<<" parent : ";
            n->show_parent();
        }
        else{
            cout<<"node : "<<n->get_val()<<" has no parent";
        }
        cout<<endl;
    }
}


