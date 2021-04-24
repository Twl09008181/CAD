
#ifndef INPUT_H
#define INPUT_H

#include "../lib/Function.hpp"

#include <vector>
#include <string>
#include <algorithm>
#include <utility>

// inline std::pair<unsigned int,unsigned int> str_to_implicant_val(std::string::const_iterator &s,std::string::const_iterator &e)
// {
//     unsigned int val = 0;
//     while(s != e)
//     {
//         auto literal_cut = find(s,e,'*');
//         auto literal = find(s,literal_cut,'!');
        
//         if(literal!=literal_cut)//need add
//             ;
        
//         s = literal_cut + 1;

//     }
// }

inline Function get_function(const std::string&str,int Fan_in)
{
    Function F;F.resize(Fan_in + 1);//also need 0 one's field.
    unsigned int max_num_of_one = 0;


    auto open = find(str.begin(),str.end(),'(');

    while(open != str.end())
    {
        auto close = find(open,str.end(),')');
        
        auto result = str_to_implicant_val(open, close);//return val and the number of bits which are 1 in val.
        
        F.at(result.second).push_back(result.first);

        max_num_of_one = std::max(result.second, max_num_of_one);

        open = find(close,str.end(),'(');
    }
    
    //reduce 
    for(int i = 0; i < Fan_in - max_num_of_one;i++)
    {
        F.pop_back();
    }
    return F;
}

// int main()
// {



// }
#endif
