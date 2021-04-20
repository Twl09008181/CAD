
#include "../lib/SAT.hpp"
#include <vector>
#include <iostream>

int main()
{
    
    bool p1,p2,p3,p4,p5,p6,p7;

    std::vector<bool*>implicant{&p1,&p2,&p3,&p4,&p5,&p6,&p7};
    bracket br1{&p1,&p6};//p1 + p6
    bracket br2{&p6,&p7};//p6 + p7
    bracket br3{&p6};//p6
    bracket br4{&p2,&p3,&p4};//p2 + p3 + p4
    bracket br5{&p3,&p5};// p3 + p5
    bracket br6{&p4};//p4 
    bracket br7{&p5,&p7};// p5 + p7
   

    //SAT = (p1 + p6)(p6 + p7)P6(p2 + p3 + p4)(p3 + p5)p4(p5 + p7)
    std::vector<bracket>SAT = {br1,br2,br3,br4,br5,br6,br7};
    
    auto ans = min_cover_SAT(SAT,implicant);
    for(auto p : ans)
    {
        std::cout << p << " ";
    }
    std::cout << std::endl;

    return 0;
}
