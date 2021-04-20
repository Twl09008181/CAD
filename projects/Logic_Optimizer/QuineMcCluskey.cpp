
#include "QuineMcCluskey.hpp"
#include <iostream>


//helper function 
inline bool can_be_merge(const Implicant&I1,const Implicant&I2);
inline bool try_merge(Implicant_table &Col,std::vector<Implicant>&prime);




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

// std::vector<Implicant> Min_Cover(Function &f,std::vector<Implicant>&prime)
// {
//     //
//     //
//     //
//     //we can use Implicant.get_cover_terms() to generate all cover by this term

//     create colum_cover_table ;
//     for each p_imp in prime:
//         cover = p_imp.get_cover_terms();
//         colum_cover_table.draw(cover);
    
//     while(we can find EP):
//         choose the essential prime implicant EP from colum_cover_table ;
//         colum_cover_table.erase(EP);

//     //Change to SAT problem find remain prime implicant to cover all minterms in f
// }



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
    std::cout << Col << std::endl;//show table
    Col.swap(Next_Col);
    return not_done;
}





// int main()
// {
//     Function F = {
//         {0},     // has zero 1
//         {1,2},    // has one 1 
//         {3,9,12},  //has two 1
//         {11,13,14},  //has three 1 
//         {15} 
//     };  //has four 1

//     auto Prime = Prime_Generate(F);
//     std::cout << "Prime implicants : " << std::endl;
//     for(const auto &p : Prime)
//     {
//         std::cout << "val = " << p.get_val() << " , cover = " << p.get_cover() << std::endl;
//     }

//     return 0;
// }

