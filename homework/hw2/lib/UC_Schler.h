
#ifndef UC_Schler_H
#define UC_Schler_H

#include<forward_list>
#include"DFG.h"
using namespace std;


int ASAP_start_time(int dummy);
int ALAP_start_time(int latency);

int get_degree_parent(const DFG_node&v);//看parent方向的degree
int get_degree_child(const DFG_node&v);//看child方向的degree
vector<int>get_degree(const vector<DFG_node>&V,int(*f)(const DFG_node&v));
const forward_list<DFG_node::node_val>&get_child_list(const DFG_node&v);
const forward_list<DFG_node::node_val>&get_parent_list(const DFG_node&v);

int ASAP_schedule_time(int current_time,int delay1,int delay2,int now_time);
int ALAP_schedule_time(int current_time,int delay1,int delay2,int now_time);

struct UC_Schler                //Unconstrained_Scheduling
{
    int(*start_time)(int);
    int (*get_degree)(const DFG_node&);
    const forward_list<DFG_node::node_val>&(*check_list)(const DFG_node&);
    int (*schedule_time)(int,int,int,int);
};

const UC_Schler S[]=
{
    {ASAP_start_time,get_degree_parent,get_child_list,ASAP_schedule_time},
    {ALAP_start_time,get_degree_child,get_parent_list,ALAP_schedule_time},
};
vector<int> ncsch(DFG*dfg,UC_Schler par,int latency=0);//generic function used by ASAP/ALAP
vector<int> ASAP(DFG*dfg);
vector<int> ALAP(DFG*dfg,int latency);
#endif
