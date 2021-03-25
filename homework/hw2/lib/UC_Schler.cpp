#include "UC_Schler.h"
void UC_schler::run()
{
    int cur_index = Schedule_Q.front();Schedule_Q.pop_front();//get index from Queue
    un_lock(cur_index);
}
void UC_schler::un_lock(DFG::index i)
{
    const auto &check_list = par.check_list(_dfg->get_node_vector().at(i));
     for(DFG::node_val n:check_list)//check_list save  "node_val"
        {
            
            DFG::index chck_index = _dfg->get_index(n);//check_list save  "node_val", not index.so we need get index use method in dfg class.

            //設定schedule_time不代表被schedule,只是用來記錄目前最大/最小的開始時間而已,真的schedule要等到degree = 0
            int min_or_max_time = par.schedule_time(schedule_time[i],delay[i],delay[chck_index],schedule_time[chck_index]);//callback
            schedule_time[chck_index] = min_or_max_time;
            degree[chck_index]--;
            if(!degree[chck_index])wake_up(chck_index);
        }
}
void UC_schler::wake_up(DFG::index i)
{
    Schedule_Q.push_front(i);
}
void UC_schler::init_Input()//由Input開始schedule
{
    for(const auto& i:_dfg->get_input_index())
        un_lock(i);
}
void UC_schler::init_Output()//由Input開始schedule
{
    for(const auto& i:_dfg->get_output_index())
        un_lock(i);
}
vector<int> ASAP(DFG*dfg){

    UC_schler SCH(dfg);
    SCH.init_Input();//ASAP要由Input端開始Schedule
    //start schedule
    while(!SCH.is_done())
    {
        SCH.run();
    }
    return SCH.Schedule_result();
}

vector<int> ALAP(DFG*dfg,int latency){
    UC_schler SCH(dfg,false,latency);
    SCH.init_Output();//ALAP要由Output端開始Schedule
    //start schedule
    while(!SCH.is_done())
    {
        SCH.run();
    }
    return SCH.Schedule_result();   
}
