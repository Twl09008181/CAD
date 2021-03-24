
#ifndef CS_SCHLER_H    //constrained schler
#define CS_SCHLER_H
#include "DFG.h"
#include<vector>
#include <list>
#include <forward_list>
using namespace std;

class Schler{    
public:
    
    Schler(int n,int init_time)
        :degree{vector<int>(n,-1)},schedule_time{vector<int>(n,init_time)},delay{vector<int>(n,-1)}{}
    Schler(int n):Schler(n,0){}

    Schler(DFG*dfg,bool degree_is_parent=true)
        :Schler(dfg->get_node_vector().size())
    {
        _dfg = dfg;
        auto V = _dfg->get_node_vector(); 
        if(degree_is_parent)
            for(int i = 0;i<degree.size();i++)
                degree[i] = V.at(i).get_parent_num();
        else 
            for(int i = 0;i<degree.size();i++)
                degree[i] = V.at(i).get_child_num();
        

        for(int i = 0;i<dfg->get_node_vector().size();i++){
            delay.at(i) = _dfg->get_node_vector().at(i).get_delay();
        }

    }
    bool is_done();
    vector<int>Schedule_result(){return schedule_time;}
protected:
    vector<int>schedule_time;
    vector<int>degree;
    vector<int>delay;
    DFG*_dfg;
};

struct working_node
{
    DFG::index i;
    int t;
};
inline bool Urgent(int Latest,int now_time){return Latest == now_time;}
class List_Schler:public Schler{
public:
    using W_Q_type = list<working_node>;
    using R_Q_type = forward_list<DFG::index>;

    List_Schler(vector<int>&RS,DFG  *dfg)
        :Schler{dfg},//schedule_time/delay_time/degree setting
        resource{RS},
        W_Q{vector<W_Q_type>(RS.size(),W_Q_type{})},//working Q
        R_Q{vector<R_Q_type>(RS.size(),R_Q_type{})} //Ready Q
    {}
    void run(unsigned int type);
    void dispatch(unsigned int type,int now_time); 
    void dispatch_if(unsigned int type,int now_time,const vector<int>&,bool(*condition)(int,int));
    void init_Input();
private:
    vector<W_Q_type>W_Q;
    vector<R_Q_type>R_Q;
    void un_lock(DFG::index);//un_lock is called by run,it used to release the degree of child 
    void wake_up(DFG::index,int time);//called by un_lock.
    void set_state_Ready(DFG::index i,unsigned int type){R_Q.at(type).push_front(i);}
    bool R_Q_is_empty(unsigned int type){return R_Q.at(type).empty();}
    bool Resource_available(unsigned int type){return W_Q.at(type).size()<resource.at(type);}
    vector<int>&resource;
};
#endif
