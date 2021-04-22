#include "../lib/Prime_Implicant_Chart.hpp"
#include "../lib/Function.hpp"
#include "../lib/Implicant.hpp"
#include "../lib/QuineMcCluskey.hpp"
#include "../lib/SAT.hpp"
#include <algorithm>
#include <vector>
#include <iostream>


void show_un_coverd(const std::vector<min_terms> &table)
{
    for(auto &m : table)
    {
        if(!m.is_covered())
        {
            std::cout << "m" << m.get_val() << " : ";
            for(const auto &p : m.get_prime_index())
            {
                std::cout << p << " ";
            }
            std::cout << std::endl;
        }
    }
}
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
    Function fnct = {
        {0},     // has zero 1
        {4,8},    // has one 1 
        {5,6,9,10},  //has two 1
        {7,13},  //has three 1 
        {15} 
    };  //has four 1

    ////------------------------------------------Phase 1------------------------------------------
    auto Prime = Prime_Generate(fnct);

    std::cout << "prime implicants are" << std::endl;
    for(int i = 0;i < Prime.size(); i++)
    {
        std::cout << i <<" : "<<Prime[i].get_cover_terms() << std::endl;
    }

    //------------------------------------------Phase 2------------------------------------------
    std::cout << "\ncreate table : \n";
    Prime_Implicant_Chart table{fnct,Prime};
    show_un_coverd(table.get_un_converd_Min_term());std::cout <<"\n";

    auto &ESPI = table.get_Essential_prime();//index in Prime
    std::cout << "ESPI index : ";
    for(auto &espi:ESPI)
        std::cout << espi <<" ";
    std::cout<<"\n\n";

    std::cout << "After use ESPI to cover terms : \n";
    table.cover_terms_by_ESPI();
    show_un_coverd(table.get_un_converd_Min_term());std::cout <<"\n";

    
    std::cout << "\nUse SAT to choose remain prime implicants\n";
    size_t remain_prime_num = Prime.size() - ESPI.size();
    size_t max_bracket_num = fnct.size();
    //convert to SAT
    SAT sat{max_bracket_num,remain_prime_num};

    auto un_coverd = table.get_un_converd_Min_term();
    for(auto &m : un_coverd)
    {
        SAT::bracket br;
        br.reserve(m.get_prime_index().size());
        for(auto p_i : m.get_prime_index())
        {
            br.push_back(p_i);
        }
        sat.add_bracket(br);
    }

    auto ans = sat.min_cover_SAT();
    std::cout << "choose ";
    for(auto p:ans)
        std::cout << p <<" ";


    std::cout << "\nThe final ans is : \n";
    std::vector<int>Final_ans;
    Final_ans.resize(ans.size() + ESPI.size());
    auto iter = std::copy(ans.begin(),ans.end(),Final_ans.begin());
    std::copy(ESPI.begin(),ESPI.end(),iter);
    for(auto a:Final_ans)
        std::cout <<"p"<<a <<" "; 
    //------------------------------------------Phase 2------------------------------------------
    return 0;
}
