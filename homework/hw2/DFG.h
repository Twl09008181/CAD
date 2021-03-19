#include<iostream>
#include<vector>
#include<map>
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
        cout<<"node : "<<val<<"destructor"<<endl;
    }
    int get_val()const{return val;}
    void show_list()const;
private:
    int val;
    node* next;
};


class DFG_node{
    friend class DFG;
public:

    //class type
    using operation_type = char;
    using node_value = unsigned;

    //constructor    
    DFG_node(node_value v,operation_type t)
        :vertex(v),T{t}{}
    //destructor
    ~DFG_node()
    {
        ;
    }

    //get member
    int get_val()const{return vertex.get_val();}
    operation_type get_type()const{return T;}

    //add member
    void add_next(node* &head,unsigned int &len,node_value n);
    void add_child(node_value n){add_next(vertex.next,child_number,n);}//call add_next
    void add_parent(node_value n){add_next(parent,parent_number,n);}//call add_next
    
    //show member
    void show_child()const{vertex.show_list();};//call show_list
    void show_parent()const{//call show_list
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




