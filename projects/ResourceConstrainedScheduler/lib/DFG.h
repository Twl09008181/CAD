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
    //forward_list的size()是linear time,因此用變數紀錄比較有效率，使用時機:例如計算degree
    int get_child_num()const{return child_size;}
    int get_parent_num()const{return parent_size;}
    node_val get_val()const{return val;}
    operation_type get_type_char()const{return T;}


    //改硬體的特性改這邊-------------------------------------------------------------
    int get_type_index()const{
        switch (T)
        {
        case 'i':return 0;break;
        case 'o':return 1;break;
        case '+':return 2;break;
        case '*':return 3;break;
        default:
            break;
        }
        return -1;
    }
    int get_type_index_ex_I_O()const{
        switch (T)
        {
        case '+':return 0;break;
        case '*':return 1;break;
        default:
            break;
        }
        return -1;
    }
    
    int get_delay()const{
        switch (T)
        {
        case 'i':return 0;break;
        case 'o':return 0;break;
        case '+':return 1;break;
        case '*':return 3;break;
        default:
            break;
        }
        return -1;   
    }
   //改硬體的特性改這邊-------------------------------------------------------------
private:
    node_val val;
    operation_type T;
    
    forward_list<node_val> parent,child;
    int parent_size = 0;
    int child_size = 0;


    //debuger-------------------------------------------------------------------------
    string get_child()const{return get_list(child);}
    string get_parent()const{return get_list(parent);}
    string get_list(const forward_list<node_val>&l)const
    {
        string _l;
        for(auto it = l.cbegin();it!=l.cend();++it)
            _l=_l + to_string(*it)+" ";
        return _l;
    }
    //debuger-------------------------------------------------------------------------
};



class DFG{
public:
    using index = unsigned;
    using node_val = DFG_node::node_val;
    

    //some basic graph method
    DFG(int n){V.reserve(n);}
    ~DFG(){}
    void add_node(node_val n,char t);
    void add_edge(node_val n1,node_val n2);
    void show_DFG()const;
    const vector<DFG_node>&get_node_vector()const{return V;}//return all node_vector
    const DFG_node&get_node(index i)const{return V.at(i);}//enter index ,then return the DFG_node&
    index get_index(node_val v){return (Decode.find(v)!=Decode.end())? Decode[v]:-1;}//enter the DFG_node.val ,return the index in V
    
    //for find input/output rapidly
    const vector<index> &get_input_index()const{return Input_index;}//Input node's index in V
    const vector<index> &get_output_index()const{return Output_index;}//Output node's index in V
    int get_op_type_num()const{return op.size();}//return operation map type:frequency

private:
    map<node_val,index>Decode;
    map<DFG_node::operation_type,bool> op;
    vector<DFG_node>V;
    vector<index> Input_index;
    vector<index> Output_index;
};


#endif

