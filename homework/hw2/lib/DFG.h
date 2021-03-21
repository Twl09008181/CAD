#ifndef DFG_H
#define DFG_H

#include<iostream>
#include<vector>
#include<map>
#include<forward_list>
#include <string>
using namespace std;

class DFG;
class DFG_node{
    friend class DFG;
public:
    using node_val = unsigned int;
    using operation_type = char;
    DFG_node(node_val  v,operation_type t)
        :val{v},T{t}{}
    void add_child(node_val n){child.push_front(n);child_size++;}
    void add_parent(node_val n){parent.push_front(n);parent_size++;}
    
    const forward_list<node_val>&get_child_list()const{return child;}
    const forward_list<node_val>&get_parent_list()const{return parent;}
    int get_child_num()const{return child_size;}
    int get_parent_num()const{return parent_size;}
    operation_type get_type()const{return T;}
    node_val get_val()const{return val;}
   
private:
    node_val val;
    operation_type T;
    
    forward_list<node_val> parent,child;
    int parent_size = 0;
    int child_size = 0;

    string get_child()const{return get_list(child);}
    string get_parent()const{return get_list(parent);}
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
 
    using OP_type_counter = map<DFG_node::operation_type,int>;
    DFG(int n){V.reserve(n);}
    ~DFG(){}
    void add_node(node_val n,char t);
    void add_edge(node_val n1,node_val n2);


    void show_DFG()const;
    const vector<DFG_node>&get_node_vector()const{return V;}//return all node_vector
    vector<DFG_node>get_input_vector()const
    {
        vector<DFG_node>Input;Input.reserve(Input_index.size());
        for(auto i:Input_index)Input.push_back(V.at(i));
        return Input;
    }
    vector<DFG_node>get_output_vector()const
    {
        vector<DFG_node>Output;Output.reserve(Output_index.size());
        for(auto i:Output_index)Output.push_back(V.at(i));
        return Output;
    }
    const vector<index> &get_input_index()const{return Input_index;}//Input node's index
    const vector<index> &get_output_index()const{return Output_index;}//Output node's index
    const DFG_node&get_node(index i)const{return V.at(i);}//enter index ,then return the DFG_node&
    index get_index(node_val v){
        if(Decode.find(v)!=Decode.end())
            return Decode[v];
        else 
            return -1;
    }
    
    const OP_type_counter&get_op_type()const{return op;}
private:
    map<node_val,index>Decode;
    OP_type_counter op;
    vector<DFG_node>V;
    vector<index> Input_index;
    vector<index> Output_index;
};


#endif

