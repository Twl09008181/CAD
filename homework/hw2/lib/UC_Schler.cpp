#include"UC_Schler.h"
int ASAP_start_time(int dummy){return -1;}
int ALAP_start_time(int latency){return latency;}
int get_degree_parent(const DFG_node&v){return v.get_parent_num();}
int get_degree_child(const DFG_node&v){return v.get_child_num();}
vector<int>get_degree(const vector<DFG_node>&V,int(*f)(const DFG_node&v))
{
    vector<int>degree(V.size(),-1);
    for(int i = 0;i<V.size();i++)
        degree[i] = f(V.at(i));
    return degree;
}

const forward_list<DFG_node::node_val>&get_child_list(const DFG_node&v){return v.get_child_list();}
const forward_list<DFG_node::node_val>&get_parent_list(const DFG_node&v){return v.get_parent_list();}
int ASAP_schedule_time(int current_time,int delay1,int delay2,int now_time){return max(current_time+delay1,now_time);}//delay傳入current_delay
int ALAP_schedule_time(int current_time,int delay1,int delay2,int now_time){return min(current_time-delay2,now_time);}//delay傳入next_delay

vector<int> ASAP(DFG*dfg){return ncsch(dfg,S[0]);}
vector<int> ALAP(DFG*dfg,int latency){return ncsch(dfg,S[1],latency);}
vector<int> ncsch(DFG*dfg,UC_Schler par,int latency)
{
    const vector<DFG_node>& V = dfg->get_node_vector();
    vector<int>degree(V.size(),-1);//according to different scheduler ways:ASAP/ASLA,degree will different.
    vector<int>delay(V.size(),-1);//according to different operation,has different delay,ncsh designer must setting.
    vector<int>schedule_time(V.size(),par.start_time(latency));//callback function do determine the nodes with degree 0 start_time.
    forward_list<int>Schedule_Q;//use a forward_list to schedule

    //setting degree/delay
    for(int i = 0;i<V.size();i++)
    {
        const DFG_node& v = V.at(i);
        degree[i] = par.get_degree(v);//use callback 
      
        if(!degree[i]){Schedule_Q.push_front(i);}//i is index,not node_val
        
        delay.at(i) = v.get_delay();
    }    

    //start schedule
    while(!Schedule_Q.empty())
    {
        int cur_index = Schedule_Q.front();Schedule_Q.pop_front();//get index from Queue
        const forward_list<DFG_node::node_val>&check_list = 
                                par.check_list(V.at(cur_index));//use callback to get check_list,this is determine by what scheduler you use.
        
        for(DFG::node_val n:check_list)
        {
            DFG::index chck_index = dfg->get_index(n);//check_list save  node_val, not index.so we need get index use method in dfg class.
            schedule_time[chck_index] = 
                        par.schedule_time(schedule_time[cur_index],delay[cur_index],delay[chck_index],schedule_time[chck_index]);//callback
            
            degree[chck_index]--;
            if(!degree[chck_index])Schedule_Q.push_front(chck_index);//it can be schedule next time
        }
    }

    //show the schedule result
    // for(int i = 0;i<V.size();i++)
    // {
    //     cout<<V.at(i).get_val()<<" : schedule at"<<schedule_time.at(i)<<endl;
    // }


    return schedule_time;
}

