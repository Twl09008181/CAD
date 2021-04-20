#include "SAT.hpp"
#include "vector"
#include <iostream>

void SAT_solver(int i,std::vector<bracket>&SAT,std::vector<bool*>&implicant,std::vector<int>&ans,std::vector<int>current)
{

    if(i==implicant.size())//end 
    {   
        if(evaulate_SAT(SAT))//if it can sove SAT
        {
            if(ans.size() > current.size())//see whether this is a better  answer.
                ans = current;
        }
    }
    else {
        *implicant[i] = false;
        SAT_solver(i+1,SAT,implicant,ans,current);//set implicant[i] = false
        
        *implicant[i] = true;
        current.push_back(i+1);
        SAT_solver(i+1,SAT,implicant,ans,current);//set implicant[i] = true
    }
}


