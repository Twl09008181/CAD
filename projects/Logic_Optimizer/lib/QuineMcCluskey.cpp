
#include "QuineMcCluskey.hpp"
#include "SAT.hpp"
#include "Colum_table.hpp"
#include "map"
#include <iostream>
#include <iomanip>



//----------------------------------------------Prime_Generate part------------------------------------------------
using Implicant_table = std::vector<std::map <Implicant,bool>>;
inline bool can_be_merge(const Implicant&I1,const Implicant&I2);
inline bool try_merge(Implicant_table &Col,std::vector<Implicant>&prime);
std::ostream & operator<<(std::ostream& os, Implicant_table &table);

std::vector<Implicant> Prime_Generate(Function &f)//Input function , return Prime_implicants
{
    std::vector<Implicant> prime;
    //init 
    Implicant_table table(f.size());
    for(int i = 0; i < f.size(); i++)
        for(auto &terms : f.at(i))
            table.at(i).insert({terms,false});
    //start run merge
    bool not_done = true;
    while(not_done)
    {
        not_done = try_merge(table,prime);
    }

    return prime;
}
//----------------------------------------------Prime_Generate part------------------------------------------------






//----------------------------------------------Min_Cover part------------------------------------------------




std::vector<Implicant> Min_Cover(Function &f,std::vector<Implicant>&prime)
{

    colum_table table{f,prime};
    auto& ESPI = table.get_Essential_prime();//get essential implicant's index in std::vector<Implicant>&prime.
    table.cover_terms_by_ESPI();//Step4 : cover min_term by essential implicant

    //Step5 : Change to SAT problem find remain prime implicants to cover all minterms in f
    size_t remain_prime_num = prime.size() - ESPI.size();
    size_t max_bracket_num = f.size();
    //convert to SAT
    SAT sat{max_bracket_num,remain_prime_num};
    auto un_coverd = table.get_un_converd_Min_term();//GET un_coverd min_terms
    for(auto &m : un_coverd)
    {
                                                    //change each minterm into one bracket form.
        SAT::bracket br;
        br.reserve(m.get_prime_index().size());
        for(auto p_i : m.get_prime_index())
        {
            br.push_back(p_i);
        }
        
        sat.add_bracket(br);//add this min_term's bracket into SAT problem
    }

    auto sat_result = sat.min_cover_SAT();//use sat to solve this problem,return is index of implicants.

    //union ESPI and sat_result
    std::vector<Implicant>Final_ans;
    Final_ans.reserve(sat_result.size() + ESPI.size());
    for(int i = 0;i < sat_result.size();i++)
        Final_ans.push_back(prime.at(sat_result.at(i)));

    for(int i = 0;i < ESPI.size();i++)
        Final_ans.push_back(prime.at(ESPI.at(i)));

    return Final_ans;
}

//----------------------------------------------Min_Cover part------------------------------------------------











//----------------------------------------------Prime_Generate helper function------------------------------------------------


inline bool can_be_merge(const Implicant&I1,const Implicant&I2)
{
    if(I1.get_cover()!=I2.get_cover())return false;//different cover

    unsigned int diff = I1.get_val() ^ I2.get_val();//do xor , we can get difference
    
    return ((diff)&(diff-1))==0;//diff is power of 2
}

inline bool try_merge(Implicant_table &Col,std::vector<Implicant>&prime)
{
    int max_num_of_one = Col.size();
    bool not_done = false;
    Implicant_table Next_Col(max_num_of_one);

    for(int i = 0;i < max_num_of_one - 1; i++)//merge Col[i],Col[i+1]
    {
        for(auto &term1 : Col[i])
        {
            for(auto &term2 : Col[i+1])
            {
                if(can_be_merge(term1.first,term2.first))
                {
                    unsigned int cover = term1.first.get_val() ^ term2.first.get_val() + term1.first.get_cover();//cover = diff + cover1
                    Next_Col[i].insert({Implicant{term1.first.get_val(),cover},false});//Next_Col insert,and set it as false.
                    term1.second  = term2.second = true;
                }
            }
            if(term1.second)//be merge.
                not_done = true;
            else //it is a prime implicant
                prime.push_back(term1.first);
        }
    }
    //std::cout << Col << std::endl;//show table
    Col.swap(Next_Col);
    return not_done;
}
//for debug
std::ostream & operator<<(std::ostream& os, Implicant_table &table)
{
    os << std::setw(10) <<"Term value|"<<std::setw(5) << "Cover\n";
    for(int i = 0;i < table.size();i++)
    {
        for(auto& term : table[i])
            os << std::setw(10) <<term.first.get_val() <<"|" << std::setw(5) <<term.first.get_cover()<<"\n";
        os << "\n";
    }
    return os;
}
//----------------------------------------------Prime_Generate helper function------------------------------------------------




