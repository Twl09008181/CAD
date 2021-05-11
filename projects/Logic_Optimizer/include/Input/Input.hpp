
#ifndef INPUT_H
#define INPUT_H

#include "../../src/Function.hpp"


#include <string>
#include <algorithm>
#include <utility>



inline std::pair<unsigned int,unsigned int> str_to_implicant_val(std::string::const_iterator s,std::string::const_iterator e,unsigned int exp)
{
    unsigned int val = 0;
    unsigned int num_of_one = 0;
    while(s != e)
    {
        s++;//we need ++ in case of infinite loop.

        auto literal_cut = find(s,e,'*');//each literal splited by '*'

        auto literal = find(s, literal_cut,'!');//if '!' is exist , it is a negative literal.
        
        if(literal == literal_cut)//it is a positive literal
        {
            num_of_one ++;
            val += exp;
        }
        exp/=2;
        s = literal_cut;// s is the position of '*'
    }
    return std::make_pair(val,num_of_one);
}
#include <set>
inline Function get_function(const std::string&str,int Fan_in)
{
    std::vector<std::set<int>>F;//use set to avoid duplicate terms.
    F.resize(Fan_in+1);
    unsigned int exp = 1;
    for(int i = 0;i<Fan_in - 1;i++)
        exp*=2;
 
    unsigned int max_num_of_one = 0;

    auto open = find(str.begin(),str.end(),'(');

    while(open != str.end())
    {
        auto close = find(open,str.end(),')');
      
        auto result = str_to_implicant_val(open, close,exp);//return val and the number of bits which are 1 in val.
        
        F.at(result.second).insert(result.first);

        max_num_of_one = std::max(result.second, max_num_of_one);

        open = find(close,str.end(),'(');
    }
    
    //reduce 
    for(int i = 0; i < Fan_in - max_num_of_one;i++)
    {
        F.pop_back();
    }
    
    Function F2(F.size());//copy to Function format
    for(int i = 0;i<F2.size();i++)
    {
        for(auto m:F[i])
            F2[i].push_back(m);
    }

    return F2;
}


#endif
