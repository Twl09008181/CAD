
#include "List_Schler.h"

bool List_Schler::is_done()
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







void error_op_type_msg(int s1,int s2)
{
    cerr<<"resource size invalid!! "<<"DFG's op kind = "<<s1<<" but "<<"resource size = "<<s2<<endl;
}
vector<int>ML_RCS(DFG *dfg,vector<int>&resource)
{
    //step 0 : check 資源的數量對得上dfg當中操作的數量---------------------------------------------
    int type_num = resource.size();//取得operation(excluding 'i','o')的種類數
    if(type_num!=dfg->get_op_type_num()){error_op_type_msg(dfg->get_op_type_num(),resource.size());exit(1);}//種類數不合
    
    //初始化SCH
    List_Schler SCH(resource,dfg);
    SCH.init_Input();//由input開始進行schedule,並將能放入ready_q的操作放入
    int l = 0;
    while(!SCH.is_done())
    {
        for(unsigned int tp = 0;tp < type_num;tp++)
            SCH.run(tp);//去執行 type = tp 的working_q當中的operation
        for(unsigned int tp = 0;tp<type_num;tp++)
           SCH.dispatch(tp,l);//由ready queue當中取出事件加入working queue
        l++;
    }
    return SCH.Schedule_result();
}


vector<int>MR_LCS(DFG *dfg,int latency)
{
    int type_num = dfg->get_op_type_num();
    vector<int>resource(type_num,1);//初始化為1
    vector<int>ALAP_schedule = ALAP(dfg,latency);

    //任何一個input的schedule時間必須小於0
    for(auto i:dfg->get_input_index())
        if(ALAP_schedule.at(i)<0)
            return {-1};//該latency無解
    
        //初始化SCH
    List_Schler SCH(resource,dfg);
    SCH.init_Input();//由input開始進行schedule,並將能放入ready_q的操作放入
    int l = 0;
    while(!SCH.is_done())
    {
        for(unsigned int tp = 0;tp < type_num;tp++)
            SCH.run(tp);//去執行 type = tp 的working_q當中的operation
        for(unsigned int tp = 0;tp < type_num;tp++)
            SCH.dispatch_if(tp,l,ALAP_schedule,Urgent);
         for(unsigned int tp = 0;tp<type_num;tp++)
           SCH.dispatch(tp,l);//由ready queue當中取出事件加入working queue
        l++;
    }
    return resource;
}
