
#ifndef List_Schler_H    
#define List_Schler_H

#include "DFG.h"
#include "Schler_prototype.h"//Schler prototype
#include "UC_Schler.h" //ALAP
#include "Ready_Q.h"
#include<vector>
#include <list>
#include <forward_list>
using namespace std;
struct working_node
{
    DFG::index i;
    int t;
};

class List_Schler:public Schler{
public:
    using W_Q_type = list<working_node>;
    using R_Q_type = _R_Q;

    List_Schler(vector<int>&RS,DFG  *dfg,vector<int>&Cr)
        :Schler{dfg},//schedule_time/delay_time/degree setting
        resource{&RS},
        criticality{&Cr},
        W_Q{vector<W_Q_type>(RS.size(),W_Q_type{})},//working Q
        R_Q{vector<R_Q_type>(RS.size(),R_Q_type{})} //Ready Q
    {}
    void run(unsigned int type);
    void dispatch(unsigned int type,int now_time); 
    void dispatch_if(unsigned int type,int now_time);
    void init_Input();
    bool is_done();
private:
    vector<W_Q_type>W_Q;
    vector<R_Q_type>R_Q;
    void un_lock(DFG::index);//un_lock is called by run,it used to release the degree of child 
    void wake_up(DFG::index,int time);//called by un_lock.
    void set_state_Ready(DFG::index i ,unsigned int type){R_Q.at(type).push_front({i,criticality->at(i)});}
    bool R_Q_is_empty(unsigned int type){return R_Q.at(type).empty();}
    bool Resource_available(unsigned int type){return W_Q.at(type).size()<resource->at(type);}
    vector<int>*resource;
    vector<int>*criticality;
};


//interface
vector<int>ML_RCS(DFG *dfg,vector<int>&resource);
vector<int>MR_LCS(DFG *dfg,int latency);
#endif
