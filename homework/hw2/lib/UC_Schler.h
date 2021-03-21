
#ifndef UC_Schler_H
#define UC_Schler_H

#include<forward_list>
#include"DFG.h"
using namespace std;


int ASAP_start_time(int dummy);
int ALAP_start_time(int latency);

int ASAP_get_degree(const DFG_node&v);
int ALAP_get_degree(const DFG_node&v);
const forward_list<DFG_node::node_val>&ASAP_get_check_list(const DFG_node&v);
const forward_list<DFG_node::node_val>&ALAP_get_check_list(const DFG_node&v);

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
    {ASAP_start_time,ASAP_get_degree,ASAP_get_check_list,ASAP_schedule_time},
    {ALAP_start_time,ALAP_get_degree,ALAP_get_check_list,ALAP_schedule_time},
};
vector<int> ncsch(DFG*dfg,UC_Schler par,int latency=0);//generic function used by ASAP/ALAP
vector<int> ASAP(DFG*dfg);
vector<int> ALAP(DFG*dfg,int latency);
#endif
