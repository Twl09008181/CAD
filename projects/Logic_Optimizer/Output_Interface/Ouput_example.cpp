#include "../lib/QuineMcCluskey.hpp"
#include "../lib/Function.hpp"
#include "Output.h"


#include <sstream>
#include <iostream>

int main()
{
    Function F = {
            {},     
            {4,8},   
            {10,12},  
            {11},   
            {15} };  
    Function Dont_care = {
            {},
            {},
            {9},
            {14}  
    };

    int Fan_in = std::max(F.size(),Dont_care.size()) - 1;
    auto implicants = QuineMcCluskey(F,Dont_care);
    

    std::ostringstream os;
    for(const auto&imp : implicants)
    {
        if(!os.str().empty())os << "+";
        os << "(" << Implicant_to_str(imp.get_val(),imp.get_cover(),Fan_in) << ")";
    }  

    std::cout << os.str();

    return 0;
}
