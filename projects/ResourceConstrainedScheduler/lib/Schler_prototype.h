

#ifndef SCHLER_PROTOTYPE_H
#define SCHLER_PROTOTYPE_H
#include "DFG.h"
#include <vector>
using namespace std;


class Schler{    
public:
    Schler(DFG*dfg)
        : Schler(dfg,true,0)
        {}
    Schler(DFG*dfg,bool degree_is_parent,int start_time)
        :_dfg{dfg}
    {
        int n = dfg->get_node_vector().size();
        schedule_time.reserve(n);
        degree.reserve(n);
        delay.reserve(n);
        if(degree_is_parent){
            set_degree_p(n);
        }else {set_degree_c(n);}
        set_time(n,start_time);
        set_delay(n);
    }
    vector<int>Schedule_result(){return schedule_time;}
protected:
    vector<int>schedule_time;
    vector<int>degree;
    vector<int>delay;
    DFG*_dfg;

private:
    void set_degree_c(int n){
        const auto&V = _dfg->get_node_vector();
        for(int i = 0;i<n;i++)
            degree.push_back(V.at(i).get_child_num());
    }
    void set_degree_p(int n)
    {
        const auto&V = _dfg->get_node_vector();
        for(int i = 0;i<n;i++)
            degree.push_back(V.at(i).get_parent_num());
    }
    void set_delay(int n)
    {
        const auto&V = _dfg->get_node_vector();
        for(int i = 0;i<n;i++)
            delay.push_back(V.at(i).get_delay());
    }
    void set_time(int n,int t)
    {
        for(int i = 0;i<n;i++)
            schedule_time.push_back(t);
    } 
};
#endif 
