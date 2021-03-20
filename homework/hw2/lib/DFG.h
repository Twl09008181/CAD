#ifndef DFG_H
#define DFG_H

#include<iostream>
#include<vector>
#include<map>
#include<forward_list>
#include <string>
using namespace std;

class DFG_node{
public:
    using node_val = unsigned int;
    using operation_type = char;
    DFG_node(node_val  v,operation_type t)
        :val{v},T{t}{}
    void add_child(node_val n){child.push_front(n);}
    void add_parent(node_val n){parent.push_front(n);}
    string get_child()const{return get_list(child);}
    string get_parent()const{return get_list(parent);}
    operation_type get_type()const{return T;}
    node_val get_val()const{return val;}
private:
    node_val val;
    operation_type T;
    forward_list<node_val> parent,child;
    string get_list(const forward_list<node_val>&l)const
    {
        string _l;
        for(auto it = l.cbegin();it!=l.cend();++it)
            _l=_l + to_string(*it)+" ";
        return _l;
    }
};

class DFG{
public:
    using index = unsigned;
    using node_val = DFG_node::node_val;
    DFG(int n){V.reserve(n);}
    ~DFG(){}
    void add_node(node_val n,char t);
    void add_edge(node_val n1,node_val n2);
    void show_node()const{
        for(auto n:V)
            cout<<"type = "<<n.get_type()<<" val = "<<n.get_val()<<endl;
    }
    void show_DFG()const;
private:
    map<node_val,index>Decode;
    vector<DFG_node>V;
};


#endif

