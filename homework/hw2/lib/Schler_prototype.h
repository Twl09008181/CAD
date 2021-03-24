

#ifndef SCHLER_PROTOTYPE_H
#define SCHLER_PROTOTYPE_H
#include "DFG.h"
#include <vector>
using namespace std;
class Schler{    
public:
    Schler(int n,int init_time)
        :degree{vector<int>(n,-1)},schedule_time{vector<int>(n,init_time)},delay{vector<int>(n,-1)}{}
    Schler(DFG*dfg,int start_time = 0,bool degree_is_parent=true)
        :Schler(dfg->get_node_vector().size(),start_time)
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
    vector<int>Schedule_result(){return schedule_time;}
protected:
    vector<int>schedule_time;
    vector<int>degree;
    vector<int>delay;
    DFG*_dfg;
};
#endif 
