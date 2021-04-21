
#include "Implicant.hpp"
#include <vector>



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
