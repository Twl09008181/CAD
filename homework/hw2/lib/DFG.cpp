
#include"DFG.h"
void DFG::add_node(node_val n,DFG_node::operation_type t)
{
    
    if(Decode.find(n)==Decode.end()){
        Decode[n] = V.size();//加入map當中
        V.push_back({n,t});
        if(t=='i')Input_index.push_back(V.size()-1);//方便做ASAP
        else if(t=='o')Output_index.push_back(V.size()-1);//方便做ALAP

        else{//operation 
            if(op.find(t)==op.end())//計算每種operation的出現次數
                op[t] = 1;
            else
                op[t]++;
        }
    }
    else{
        cerr<<"repeat node number : "<<n<<"in DFG"<<endl;
        exit(1);
    }
}
void DFG::add_edge(node_val n1,node_val n2)
{
    index i = Decode[n1];V[i].add_child(n2);
    index j = Decode[n2];V[j].add_parent(n1); 
}
void DFG::show_DFG()const{

    for(auto n:V)
    {
       string parent = n.get_parent();
       string child = n.get_child();
       cout<<"node : "<<n.get_val()<<" is type : "<<n.get_type()<<"\n"
       <<"child_list : "<<child<<" parent_list : "<<parent<<endl;
    }
}


