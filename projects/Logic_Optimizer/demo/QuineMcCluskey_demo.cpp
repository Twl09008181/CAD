#include "../lib/QuineMcCluskey.hpp"
#include "../lib/Implicant.hpp"
#include <vector>
#include <iostream>
#include <map>


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

bool validation(Function &F,std::vector<Implicant>&imps)
{
    std::map<int,bool>check;
    for(int i = 0;i < F.size(); i++)
    {
        for(auto &term:F[i])
            check.insert({term,false});
    }

    for(auto &imp:imps)
    {
        for(auto m:imp.get_cover_terms())
            check[m] = true;
    }

    for(auto c:check)
        if(c.second==false)
            return false;
    return true;
}
int main()
{
    Function F = {
            {},     // has zero 1 , if empty,still need a {}
            {4,8},    // has one 1 
            {10,12},  //has two 1
            {11},  //has three 1 
            {15} };  //has four 1

    Function Dont_care = {
            {},
            {},
            {9},
            {14}  
    };

    auto ans = QuineMcCluskey(F,Dont_care);

    std::cout <<"implicants : " << std::endl;
    for(auto& imp : ans)
    {
        std::cout <<"val = "<<imp.get_val()<<" dash = " <<imp.get_cover() <<" can cover :";
        std::cout <<imp.get_cover_terms()<<std::endl;
    }
    
    if(validation(F,ans))
    {
        std::cout << "ans is correct!!" << std::endl;
    }
    else{
        std::cout <<"ans is error!!" <<std::endl;
    }


    ans.pop_back();//if we delete a implicant,then answer will be error.
    if(validation(F,ans))
    {
        std::cout << "ans is correct!!" << std::endl;
    }
    else{
        std::cout <<"ans is error!!" <<std::endl;
    }
    return 0;
}
