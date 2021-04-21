#include "SAT.hpp"
void SAT::SAT_solver(int i,std::vector<int>&ans,std::vector<int>current)
{

    if(i == literals.size()) 
    {   
        if(evaulate_SAT())//if it can sove SAT
        {
            if(ans.size() > current.size())//see whether this is a better  answer.
                ans.swap(current);//swap is more efficient.
        }
    }

    else {
        literals[i].val = false;    
        SAT_solver(i+1,ans,current);//set li = false
        
        literals[i].val  = true;
        current.push_back(literals[i].id);
        SAT_solver(i+1,ans,current);//set li = true
    }
}

void SAT::add_bracket(const bracket &br)
{
    bracket new_br;
    new_br.reserve(br.size());

    for(auto l : br)
    {
        if(lit_id.find(l)==lit_id.end())//l is a new literal
        {
            lit_id.insert({l,literals.size()});
            literals.push_back({l});
        }
        new_br.push_back(lit_id[l]);//put index of l in std::vector<literal>literals into bracket. used in bool SAT::evaulate_one_bracket(const bracket& br).
    }
    brackets.push_back(new_br);
}
