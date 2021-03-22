
#include "List_Schler.h"


bool is_schedule(const vector<DFG::index>&Output,const vector<int>&schedule)
{
    for(auto o:Output)
        if(schedule[o]==0)return false;//有一個output還沒被schedule到
    return true;
}
void put_RQ(DFG*dfg,vector<int>&schler_t,vector<int>&degree,int now_time,int curr_index,vector<R_Q>&ready_Q)
{
    const auto &V = dfg->get_node_vector();//get node_vector
    const auto &curr_node = V.at(curr_index);//get current node
    const auto &chck_list = curr_node.get_child_list();//check curr_node's child_list
    for(DFG::node_val n :chck_list)
    {
        DFG::index chck_index = dfg->get_index(n);//chck_lisst存的是node_val,必須轉成index
        if(!--degree[chck_index]){
            int tp = V.at(chck_index).get_type_index_ex_I_O();//得到該child的type類型
            if(tp>=0)
                ready_Q.at(tp).push_front(chck_index);//放入適當的ready_queue當中
            else //is I/O,t = -1
            {
                schler_t[chck_index] = now_time;//schedule
                //cout<<"schedule "<<V.at(chck_index).get_val()<<" at t = "<<now_time<<endl;
            }
        }
    }    
}

void error_op_type_msg(int s1,int s2)
{
    cerr<<"resource size invalid!! "<<"DFG's op kind = "<<s1<<" but "<<"resource size = "<<s2<<endl;
}
vector<int>ML_RCS(DFG *dfg,vector<int>&resource)
{
    //step 0 : check 資源的數量對得上dfg當中操作的數量---------------------------------------------
    int type_num = resource.size();//取得operation(excluding 'i','o')的種類數
    if(type_num!=dfg->get_op_type().size()){error_op_type_msg(dfg->get_op_type().size(),resource.size());exit(1);}//種類數不合
    //step 0 :-------------------------------------------------------------------------------------

    //step 1: setting Ready_Q & Working Q--------------------------------------------------------
    vector<R_Q>Ready_Q(type_num,R_Q{});//不同型態操作的R_Q
    vector<W_Q>Working_Q(type_num,W_Q{});//不同型態操作的W_Q
    //step 1: setting Ready_Q & Working Q--------------------------------------------------------


    //step2 : setting degree,schedule_time  並由input端開始進行第一次schedule()-------------------------------
    const vector<DFG_node>& V = dfg->get_node_vector();
    vector<int>schedule_time(V.size(),0);//schedule的結果
    vector<int>degree = get_degree(V,get_degree_parent);//set degree
    //由input開始進行schedule,並將能放入ready_q的操作放入
    for(auto inpt_index:dfg->get_input_index())
        put_RQ(dfg,schedule_time,degree,0,inpt_index,Ready_Q);
    //step2 : setting degree,schedule_time  並由input端開始進行第一次schedule()-------------------------------


    //step3 : Schedule()---------------------------------------------------------------------------------
    int l;
    while(!is_schedule(dfg->get_output_index(),schedule_time))//仍有output node還沒被schedule到
    {
    //第一階段Working_queue prepare:----------------------------------------------------------------------------
        //處理Working_queue當中的操作，如果該操作完成就去扣掉child的degree,並有機會將child加入ready_queue
        for(int tp = 0;tp < type_num;tp++)
        {   
            auto &w_q_t = Working_Q.at(tp);//該type的working q
            
            vector<decltype(w_q_t.begin())> Recycle;//回收 iterator
            
            for(auto it = w_q_t.begin();it != w_q_t.end();it++)//扣掉,且如果扣完是0下一步驟會釋放
            {   
                if(!(--it->t))//該操作執行完成
                {
                    put_RQ(dfg,schedule_time,degree,l,it->i,Ready_Q);//對child做檢查能否放入Ready_Q
                    Recycle.push_back(it);
                }
            }
            for(auto &it:Recycle)//在外部回收iterator
                w_q_t.erase(it);
        }
    //第一階段Working_queue prepare:----------------------------------------------------------------------------


    //第二階段:由Ready_Q當中找operation來schedule------------------------------------------------------------
        for(int tp = 0;tp<type_num;tp++){
           
           auto &w_q_t = Working_Q.at(tp);
           auto &r_q_t = Ready_Q.at(tp);
            while(w_q_t.size()<resource.at(tp) && !r_q_t.empty())//ak-TK>0 && RQ不為空 註:C++ 11 list.size()是const method
            {   
                DFG::index index = r_q_t.front();r_q_t.pop_front();//從R_Q當中取出
                w_q_t.push_back({index,V.at(index).get_delay()});//放入working queue當中
                schedule_time[index] = l;//schedule!
                //cout<<"schedule "<<V.at(index).get_val()<<" at t = "<<l<<endl;
            }
        }
    //第二階段:由Ready_Q當中找operation來schedule------------------------------------------------------------

        l++;//下一個時間
    }
    //step3 : Schedule()---------------------------------------------------------------------------------

    //cout<<"latency = "<<l-1<<endl;
    return schedule_time;
}






vector<int>MR_LCS(DFG *dfg,int latency)
{

    vector<int>resource(dfg->get_op_type().size(),1);//初始化為1

    vector<int>ALAP_schedule = ALAP(dfg,latency);

    //任何一個input的schedule時間必須小於0
    for(auto i:dfg->get_input_index())
        if(ALAP_schedule.at(i)<0)
        {
            return {-1};//該latency無解
        }
    


    //step 0 : check 資源的數量對得上dfg當中操作的數量---------------------------------------------
    int type_num = resource.size();//取得operation(excluding 'i','o')的種類數
    if(type_num!=dfg->get_op_type().size()){error_op_type_msg(dfg->get_op_type().size(),resource.size());exit(1);}//種類數不合
    //step 0 :-------------------------------------------------------------------------------------

    //step 1: setting Ready_Q & Working Q--------------------------------------------------------
    vector<R_Q>Ready_Q(type_num,R_Q{});//不同型態操作的R_Q
    vector<W_Q>Working_Q(type_num,W_Q{});//不同型態操作的W_Q
    //step 1: setting Ready_Q & Working Q--------------------------------------------------------


    //step2 : setting degree,schedule_time  並由input端開始進行第一次schedule()-------------------------------
    const vector<DFG_node>& V = dfg->get_node_vector();
    vector<int>schedule_time(V.size(),0);//schedule的結果
    vector<int>degree = get_degree(V,get_degree_parent);//set degree
    //由input開始進行schedule,並將能放入ready_q的操作放入
    for(auto inpt_index:dfg->get_input_index())
        put_RQ(dfg,schedule_time,degree,0,inpt_index,Ready_Q);
    //step2 : setting degree,schedule_time  並由input端開始進行第一次schedule()-------------------------------


    //step3 : Schedule()---------------------------------------------------------------------------------
    int l;
    while(!is_schedule(dfg->get_output_index(),schedule_time))//仍有output node還沒被schedule到
    {
    //第一階段Working_queue prepare:----------------------------------------------------------------------------
        //處理Working_queue當中的操作，如果該操作完成就去扣掉child的degree,並有機會將child加入ready_queue
        for(int tp = 0;tp < type_num;tp++)
        {   
            auto &w_q_t = Working_Q.at(tp);//該type的working q
            
            vector<decltype(w_q_t.begin())> Recycle;//回收 iterator
            
            for(auto it = w_q_t.begin();it != w_q_t.end();it++)//扣掉,且如果扣完是0下一步驟會釋放
            {   
                if(!(--it->t))//該操作執行完成
                {
                    put_RQ(dfg,schedule_time,degree,l,it->i,Ready_Q);//對child做檢查能否放入Ready_Q
                    Recycle.push_back(it);
                }
            }
            for(auto &it:Recycle)//在外部回收iterator
                w_q_t.erase(it);
        }
    //第一階段Working_queue prepare:----------------------------------------------------------------------------



    //第二階段,計算slacks
        for(int tp = 0;tp<type_num;tp++){
            auto &w_q_t = Working_Q.at(tp);
            auto &r_q_t = Ready_Q.at(tp);

            
            vector<int>release;
            for(auto index : r_q_t)
            {
                if(ALAP_schedule.at(index)==l)//slack = 0
                {
                    if(resource.at(tp)==w_q_t.size())
                        resource.at(tp)++;
                    
                    w_q_t.push_back({index,V.at(index).get_delay()});//放入working queue當中
                    schedule_time[index] = l;
                    release.push_back(index);
                }
            }
            for(int i:release)//釋放
                r_q_t.remove(i);
        }
    //第三階段:由Ready_Q當中找operation來schedule------------------------------------------------------------
        for(int tp = 0;tp<type_num;tp++){
           
           auto &w_q_t = Working_Q.at(tp);
           auto &r_q_t = Ready_Q.at(tp);
            while(w_q_t.size()<resource.at(tp) && !r_q_t.empty())//ak-TK>0 && RQ不為空 註:C++ 11 list.size()是const method
            {   
                DFG::index index = r_q_t.front();r_q_t.pop_front();//從R_Q當中取出
                w_q_t.push_back({index,V.at(index).get_delay()});//放入working queue當中
                schedule_time[index] = l;//schedule!
                //cout<<"schedule "<<V.at(index).get_val()<<" at t = "<<l<<endl;
            }
        }
    //第二階段:由Ready_Q當中找operation來schedule------------------------------------------------------------

        l++;//下一個時間
    }
    //step3 : Schedule()---------------------------------------------------------------------------------

    //cout<<"latency = "<<l-1<<endl;
    return resource;
}
