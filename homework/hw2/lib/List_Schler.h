
#ifndef LIST_SCHLER_H
#define LIST_SCHLER_H
#include "DFG.h"
#include "UC_Schler.h"
#include<vector>
#include<forward_list>
#include<list>
using namespace std;


//Queue init
struct working_node
{
    DFG::index i;
    int t;
};
using R_Q = forward_list<DFG::index>;
using W_Q = list<working_node>;
/*R_Q:可被schedule的操作都放在此queue   W_Q:正在進行的操作都放在此queue*/
void put_RQ(DFG*dfg,vector<int>&schler_t,vector<int>&degree,int now_time,int curr_index,vector<R_Q>&ready_Q);
void error_op_type_msg(int s1,int s2);
vector<int>ML_RCS(DFG *dfg,vector<int>&resource);
vector<int>MR_LCS(DFG *dfg,int latency);


#endif
