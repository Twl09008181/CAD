#include "../lib/QuineMcCluskey.hpp"
#include "../lib/Implicant.hpp"
#include <iostream>

std::ostream& operator<<(std::ostream &os, const std::vector<Implicant::type>&terms)
{
    os << "m(";

    for(int i = 0; i < terms.size(); i++)
    {
        if(i!=0)
            os << ",";
        os << terms.at(i);
    }
    os << ")";
    return os;
}

int main()
{
    // Function F1 = {
    //     {0},     // has zero 1
    //     {1,2},    // has one 1 
    //     {3,9,12},  //has two 1
    //     {11,13,14},  //has three 1 
    //     {15} 
    // };  //has four 1

    // auto Prime = Prime_Generate(F1);
    // std::cout << "Prime implicants : " << std::endl;
    // for(const auto &p : Prime)
    // {
    //     std::cout << "val = " << p.get_val() << " , cover = " << p.get_cover() << std::endl;
    // }


    Function F2 = {
        {0},     // has zero 1
        {4,8},    // has one 1 
        {5,6,9,10},  //has two 1
        {7,13},  //has three 1 
        {15} 
    };  //has four 1

    auto Prime = Prime_Generate(F2);
    std::cout << "Prime implicants : " << std::endl;
    for(const auto &p : Prime)
    {
        std::cout << "val = " << p.get_val() << " , cover = " << p.get_cover() << "\n";
        auto cover_terms = p.get_cover_terms();
        std::cout << cover_terms << std::endl;
    }


    return 0;
}
