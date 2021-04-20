
#include "Implicant.hpp"
#include <vector>
#include <iostream>


//gernerate_all_combination that used only power of 2 
void combination(std::vector<Implicant::type>&terms, Implicant::type cover_num, int acc = 0,int acc_exp = 1)
{
    while(cover_num)//scan this cover_num
    {
        //AND(cover_num,0b01) to get the lsb of cover_num 
        bool lsb = cover_num & 1;

        if(lsb)//if lsb is one , then we can choose to accumulate 2^(acc_exp) 
        {
            combination(terms,cover_num>>1, acc + acc_exp, acc_exp*2);
        }
        //or we can not choose ,just shift and increase to another stage.
        cover_num>>=1;
        acc_exp*=2;
    }
    terms.push_back(acc);//get the accumulation.
}


std::vector<Implicant::type> Implicant::get_cover_terms()const 
{
    std::vector<Implicant::type>terms;
    combination(terms,cover,val);
    return terms;
}


//demo

// std::ostream& operator<<(std::ostream &os, const std::vector<Implicant::type>&terms)
// {
//     os << "m(";

//     for(int i = 0; i < terms.size(); i++)
//     {
//         if(i!=0)
//             os << ",";
//         os << terms.at(i);
//     }
//     os << ")";
//     return os;
// }

 
// #include <set>
// int main()
// {
//     std::vector<Implicant> imps= 
//     {
//         {0,3},            //this term can cover (0,1,2,3)
//         {1,10},          //this term can cover (1,3,9,11)
//         {9,6},           //this term can cover (9,11,13,15)
//         {12,3}           ////this term can cover (12,13,14,15)
//     };
//     // for(const auto &imp:imps)
//     // {
//     //     auto terms = imp.get_cover_terms();
//     //     std::cout << terms << std::endl;
//     // }

//     std::set<Implicant>Set;
//     for(const auto &imp:imps)
//     {
//         Set.insert(imp);
//     }
//     Set.insert(Implicant{12,3});
//     for(auto imp:Set)
//     {
//         std::cout<<imp.val<<std::endl;
//     }
//     return 0;
// }
