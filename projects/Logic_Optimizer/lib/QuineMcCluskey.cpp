#include "QuineMcCluskey.hpp"




//----------------------------------------------Prime_Generate part------------------------------------------------
bool can_be_merge(const Implicant&I1,const Implicant&I2);
bool try_merge(Implicant_Combine_table &Col,std::vector<Implicant>&prime);
std::ostream & operator<<(std::ostream& os, Implicant_Combine_table &table);

std::vector<Implicant> Prime_Generate(Function &f,bool show_procedure)//Input function , return Prime_implicants
{
    std::vector<Implicant> prime;
    //init 
    Implicant_Combine_table table(f.size());
    for(int i = 0; i < f.size(); i++)
        for(auto &terms : f.at(i))
            table.at(i).insert({terms,false});
    //start run merge
    bool not_done = true;
    while(not_done)
    {
        if(show_procedure)std::cout << table << std::endl;//show table

        not_done = try_merge(table,prime);
    }

    return prime;
}
//----------------------------------------------Prime_Generate part------------------------------------------------






//----------------------------------------------Min_Cover part------------------------------------------------
std::vector<int>Petrick_Method(Prime_Implicant_Chart &table,size_t remain_prime_num,size_t max_bracket_num);



std::vector<Implicant> Min_Cover(Function &f,std::vector<Implicant>&prime)
{

    Prime_Implicant_Chart table{f,prime};
    auto& ESPI = table.get_Essential_prime();//get essential implicant's index in std::vector<Implicant>&prime.
    table.cover_terms_by_ESPI();//cover min_term by essential implicants.

    auto P_M_sol = Petrick_Method(table,prime.size()-ESPI.size(),f.size());
    
    //union ESPI and Petrick_Method's answer
    std::vector<Implicant>Final_ans;

    Final_ans.reserve(P_M_sol.size() + ESPI.size());

    for(int i = 0;i < P_M_sol.size();i++)Final_ans.push_back(prime.at(P_M_sol.at(i)));

    for(int i = 0;i < ESPI.size();i++)Final_ans.push_back(prime.at(ESPI.at(i)));

    return Final_ans;
}




std::vector<int>Petrick_Method(Prime_Implicant_Chart &table,size_t remain_prime_num,size_t max_bracket_num)
{

    SAT sat{max_bracket_num,remain_prime_num};
    for(auto &m : table.get_un_converd_Min_term())
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

    return sat.min_cover_SAT();//use sat to solve this problem.each element in return is a prime_implicant's index. 
}
//----------------------------------------------Min_Cover part------------------------------------------------







//----------------------------------------------Prime_Generate helper function------------------------------------------------


bool diff_one_bit(const Implicant&I1,const Implicant&I2)
{
    if(I1.get_cover()!=I2.get_cover())return false;//different cover

    unsigned int diff = I1.get_val() ^ I2.get_val();//do xor , we can get difference
    
    return ((diff)&(diff-1))==0;//diff is power of 2
}

bool try_merge(Implicant_Combine_table &Col,std::vector<Implicant>&prime)
{
    int max_num_of_one = Col.size();
    bool not_done = false;
    Implicant_Combine_table Next_Col(max_num_of_one);

    for(int i = 0;i < max_num_of_one - 1; i++)//merge Col[i],Col[i+1]
    {
        for(auto &term1 : Col[i])
        {
            for(auto &term2 : Col[i+1])
            {
                if(diff_one_bit(term1.first,term2.first))
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
    Col.swap(Next_Col);
    return not_done;
}
//for debug
std::ostream & operator<<(std::ostream& os, Implicant_Combine_table &table)
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




