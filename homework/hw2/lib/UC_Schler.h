
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

extern UC_Schler S[];//use extern to get S in .cpp

void ncsch(DFG*dfg,UC_Schler par,int latency=0);//generic function used by ASAP/ALAP
void ASAP(DFG*dfg);
void ALAP(DFG*dfg,int latency);
#endif
