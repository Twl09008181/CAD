#include"UC_Schler.h"
int ASAP_start_time(int dummy){return 0;}//更動input delay = 0之後,必須將ASAP的start從-1改回0
int ALAP_start_time(int latency){return latency;}
int get_degree_parent(const DFG_node&v){return v.get_parent_num();}
int get_degree_child(const DFG_node&v){return v.get_child_num();}
vector<int>get_degree_V(const vector<DFG_node>&V,int(*f)(const DFG_node&v))
{
    vector<int>degree(V.size(),-1);
    for(int i = 0;i<V.size();i++)
        degree[i] = f(V.at(i));
    return degree;
}
vector<int>get_delay_V(const vector<DFG_node>&V)
{
    vector<int>delay(V.size(),-1);
    for(int i = 0;i<V.size();i++)
        delay[i] = V.at(i).get_delay();
    return delay;
}
const forward_list<DFG_node::node_val>&get_child_list(const DFG_node&v){return v.get_child_list();}
const forward_list<DFG_node::node_val>&get_parent_list(const DFG_node&v){return v.get_parent_list();}
int ASAP_schedule_time(int current_time,int delay1,int delay2,int now_time){return max(current_time+delay1,now_time);}//delay傳入current_delay
int ALAP_schedule_time(int current_time,int delay1,int delay2,int now_time){return min(current_time-delay2,now_time);}//delay傳入next_delay
void show_result(const vector<DFG_node>&V,const vector<int>&schler_time);

vector<int> ASAP(DFG*dfg){return ncsch(dfg,S[0]);}
vector<int> ALAP(DFG*dfg,int latency){return ncsch(dfg,S[1],latency);}
vector<int> ncsch(DFG*dfg,UC_Schler par,int latency)
{

    //part1 設定所需要的資訊:每個node的degree/delay/以及根據ALAP/ASAP來設定schedule------------------------------------------------
    const vector<DFG_node>& V = dfg->get_node_vector();
    vector<int>degree = get_degree_V(V,par.get_degree);//according to different scheduler ways:ASAP/ASLA,degree will different.
    vector<int>delay = get_delay_V(V);//according to different operation,has different delay,ncsh designer must setting.
    vector<int>schedule_time(V.size(),par.start_time(latency));//callback function do determine the nodes with degree 0 start_time.
    //part1 設定所需要的資訊:每個node的degree/delay/以及根據ALAP/ASAP來設定schedule------------------------------------------------



    //part2 由input開始schedule---------------------------------------------------------------------

    forward_list<int>Schedule_Q;//use a forward_list to schedule
    //由input開始schedule
    for(auto i:dfg->get_input_index())
        Schedule_Q.push_front(i);
    //part2 由input開始schedule---------------------------------------------------------------------


    //part3 開始schedule---------------------------------------------------------------------
    //start schedule
    while(!Schedule_Q.empty())
    {
        int cur_index = Schedule_Q.front();Schedule_Q.pop_front();//get index from Queue
        const auto &check_list = par.check_list(V.at(cur_index));//use callback to get check_list,this is determine by what scheduler you use.
        
        for(DFG::node_val n:check_list)//check_list save  "node_val"
        {
            DFG::index chck_index = dfg->get_index(n);//check_list save  "node_val", not index.so we need get index use method in dfg class.

            //設定schedule_time不代表被schedule,只是用來記錄目前最大/最小的開始時間而已,真的schedule要等到degree = 0
            int min_or_max_time = par.schedule_time(schedule_time[cur_index],delay[cur_index],delay[chck_index],schedule_time[chck_index]);//callback
            schedule_time[chck_index] = min_or_max_time;
            degree[chck_index]--;
            if(!degree[chck_index])Schedule_Q.push_front(chck_index);//真的schedule
        }
    }

    //part3 開始schedule---------------------------------------------------------------------


    //show_result(V,schedule_time);//this cpp only


    return schedule_time;
}

void show_result(const vector<DFG_node>&V,const vector<int>&schler_time)
{
     for(int i = 0;i<V.size();i++)
        cout<<V.at(i).get_val()<<" : schedule at"<<schler_time.at(i)<<endl;
}
