
#include "CS_Schler.h"

bool Schler::is_done()
{
    const auto& Output = _dfg->get_output_index();
    for(auto o:Output)
        if(schedule_time[o]==0)return false;//若有一個output還沒被schedule到,就代表沒schedule完成
    return true;
}

void List_Schler::run(unsigned int type)
{
    if(type>=W_Q.size()){cerr<<"working_Q_type num : "<<W_Q.size()<<"resource type_num is over";exit(1);}
    auto &w_q_t = W_Q.at(type);
    vector<decltype(w_q_t.begin())> Recycle;//等等要回收iterator
    for(auto it = w_q_t.begin();it != w_q_t.end();it++)
    {   
        if(!(--it->t))//執行該operation,並且如果執行完成就去做un_lock
        {
            un_lock(it->i);
            Recycle.push_back(it);
        }
    }
    for(auto &it:Recycle)//在外部回收iterator
        w_q_t.erase(it);
}
void List_Schler::init_Input()//由Input開始schedule
{
    for(const auto& i:_dfg->get_input_index())
        un_lock(i);
}
void List_Schler::un_lock(DFG::index i)
{
    int now_time = schedule_time.at(i) + delay.at(i);//計算一下現在的時間是當初被放入的時間+該op的delay time
    const auto &curr_node = _dfg->get_node_vector().at(i);//get current node
    const auto &chck_list = curr_node.get_child_list();//check curr_node's child_list
    for(DFG::node_val n :chck_list){
        DFG::index chck_index = _dfg->get_index(n);//chck_lisst存的是node_val,必須轉成index
        if(!--degree[chck_index])
            wake_up(chck_index,now_time);
    }
}
void List_Schler::wake_up(DFG::index i,int now_time)
{
    int tp = _dfg->get_node_vector().at(i).get_type_index_ex_I_O();//得到該node的operation 類型
    if(tp>=0)
        set_state_Ready(i,tp);//放入ready_q
    else //is I/O 
        schedule_time.at(i) = now_time;//是output就直接schedule,不用放入ready_q
}



//將資源分配給readyQ中當中的工作:dispatch
void List_Schler::dispatch(unsigned int type,int now_time)
{
    auto &w_q_t = W_Q.at(type);
    auto &r_q_t = R_Q.at(type);

    //ak-TK>0 && RQ不為空 註:C++ 11 list.size()是const method
    while(Resource_available(type) && !R_Q_is_empty(type))
    {   
        DFG::index index = r_q_t.front();r_q_t.pop_front();//從R_Q當中取出
        w_q_t.push_back({index,_dfg->get_node_vector().at(index).get_delay()});//放入working queue當中
        schedule_time[index] = now_time;
    }
}


void List_Schler::dispatch_if(unsigned int type,int now_time,const vector<int>&ALAP_schedule,bool(*cd)(int,int))
{
    auto & r_q_t = R_Q.at(type);
    auto & w_q_t = W_Q.at(type);
    vector<int>Recycle;
    for(auto index : r_q_t)
    {   
        if(cd(ALAP_schedule.at(index),now_time))//slack = 0
        {
            if(!Resource_available(type))
                resource.at(type)++;
            w_q_t.push_back({index,_dfg->get_node_vector().at(index).get_delay()});//放入working queue當中
            schedule_time[index] = now_time;//dispatch
            Recycle.push_back(index);
        }
        
    }
    for(auto i:Recycle)//在外部回收
        r_q_t.remove(i);
}







