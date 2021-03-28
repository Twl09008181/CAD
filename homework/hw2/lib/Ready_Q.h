
#ifndef READY_Q
#define READY_Q
#include <iostream>
#include <queue>
#include "DFG.h"
using namespace std;


struct Ready_node
{
    DFG::index i;//index
    int criticality;
};
class mycomparison
{
  bool reverse;
public:
  mycomparison(const bool& revparam=false)
    {reverse=revparam;}
  bool operator() (const Ready_node& n1, const Ready_node&n2) const
  {
    if (reverse) return  n1.criticality >= n2.criticality;
    else return n1.criticality > n2.criticality;
  }
};


class _R_Q
{
    using Q_TYPE = priority_queue<Ready_node,vector<Ready_node>,mycomparison>;
    
    using index = DFG::index;
public:
    bool empty(){return Ready_Q.empty();}
    int size(){return Ready_Q.size();}
    index front_index(){return Ready_Q.top().i;}
    int  front_critical(){return Ready_Q.top().criticality;}
    void push_front(Ready_node n){Ready_Q.push(n);}
    void pop_front(){Ready_Q.pop();}
private:
    Q_TYPE Ready_Q;
};

#endif
