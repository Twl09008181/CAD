

#ifndef UC_SCHLER_H
#define UC_SCHLER_H
#include "DFG.h"
#include "Schler_prototype.h"
#include <forward_list>
#include <vector>
using namespace std;


inline const forward_list<DFG_node::node_val>&get_child_list(const DFG_node&v){return v.get_child_list();}
inline const forward_list<DFG_node::node_val>&get_parent_list(const DFG_node&v){return v.get_parent_list();}
inline int ASAP_schedule_time(int current_time,int delay1,int delay2,int now_time){return max(current_time+delay1,now_time);}//delay傳入current_delay
inline int ALAP_schedule_time(int current_time,int delay1,int delay2,int now_time){return min(current_time-delay2,now_time);}//delay傳入next_delay

struct UC_Schler_par
{
    const forward_list<DFG_node::node_val>&(*check_list)(const DFG_node&);
    int (*schedule_time)(int,int,int,int);
};

class UC_schler:public Schler{
public:
    UC_schler(DFG*dfg)
        :UC_schler(dfg,true,0)
    {}
    UC_schler(DFG*dfg,bool ASAP,int start_time)
        :Schler(dfg,ASAP,start_time)
    {   
        if(ASAP)
            par = {get_child_list,ASAP_schedule_time};
        else //ALAP
            par = {get_parent_list,ALAP_schedule_time};
    }
    void init_Input();
    void init_Output();
    void run();
    bool is_done(){return Schedule_Q.empty();}
private:
    void un_lock(DFG::index i);
    void wake_up(DFG::index i);
    forward_list<int>Schedule_Q;
    UC_Schler_par par;
};



vector<int> ASAP(DFG*dfg);
vector<int> ALAP(DFG*dfg,int latency);
#endif
