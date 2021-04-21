#include "../lib/SAT.hpp"
#include <vector>
#include <iostream>

int main()
{
    std::vector<SAT::bracket> brs = {
        {1,6},   //(p1+p6)
        {6,7},   //(p6+p7)
        {6},     //(p6)
        {2,3,4}, //(p2+p3+p4)
        {3,5},   //(p3+p5)
        {4},    //(p4)
        {5,7}   //(p5+p7)
    };


    SAT S(brs.size(),7);
    for(auto& br:brs)
    {
        S.add_bracket(br);
    }
    auto ans = S.min_cover_SAT();
    std::cout << "the minimum solution is : \n";
    
    for(auto t:ans)
        std::cout << "p" <<t <<" = 1" <<std::endl;

}
