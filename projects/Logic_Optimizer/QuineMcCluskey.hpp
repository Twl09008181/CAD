
#ifndef QU_MC_hpp
#define QU_MC_hpp

#include <vector>
#include <map>
#include <iomanip>
#include "Implicant.hpp"

using Function = std::vector<std::vector<int>>;
using Implicant_table = std::vector<std::map <Implicant,bool>>;
//need to classify by number of ones in each terms,like Function[0] store all terms which have zero ones,and Function [1] store all terms have one 1.
//
//ex : F = {
// {0},     // has zero 1
// {1,2},    // has one 1 
// {3,9,12},  //has two 1
// {11,13,14},  //has three 1 
// {15} };  //has four 1


std::vector<Implicant> Prime_Generate(Function &f);//Input function , return Prime_implicants.
std::vector<Implicant> Min_Cover(Function &f,std::vector<Implicant>&prime);//Use smallest prime_implicants to cover function f,and return those implicants. 
inline std::vector<Implicant>  QuineMcCluskey(Function&f)
{
    std::vector<Implicant> prime = Prime_Generate(f);//generate prime implicants
    return Min_Cover(f,prime);//cover
}

inline std::ostream & operator<<(std::ostream& os, Implicant_table &table)
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
#endif