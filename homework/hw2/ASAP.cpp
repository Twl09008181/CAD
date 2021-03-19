#include<iostream>
#include<fstream>
#include<vector>
#include<map>
using namespace std;

class node{
public:
    node(int v,node*next_node=nullptr)
        :val(v),next(next_node){}
private:
    int val;
    node* next;
};


class DFG_node{
public:
    using operation_type = unsigned;

    DFG_node(int v,operation_type t)
        :vertex(v),T{t}{}
    
    void add_child(int n);
    void add_parent(int n);
private:
    node vertex;
    operation_type T;
    node *parent;
};


class graph{

public:
    using operation_type = unsigned;
    using index = unsigned;
    graph(int n)
    {
        V.reserve(n);
    }

    void add_node(int n,operation_type t)
    {
        DFG_node *node = new DFG_node{n,t};
        V.push_back(node);
    }
    void add_edge(int n1,int n2)
    {
        index i = Decode[n1];
        V[i]->add_child(n2);
        index j = Decode[n2];
        V[j]->add_parent(n1); 
    }
    
private:
    map<int,int>Decode;
    vector<DFG_node*> V;
};




