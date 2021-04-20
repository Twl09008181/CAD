
#ifndef QU_MC_hpp
#define QU_MC_hpp

#include <vector>
#include <set>
#include "Implicant.hpp"

using Function = std::vector<std::vector<int>>;
//need to classify by number of ones in each terms,like Function[0] store all terms which have zero ones,and Function [1] store all terms have one 1.
//
//ex : F = {
// {0},     // has zero 1
// {1,2},    // has one 1 
// {3,9,12},  //has two 1
// {11,13,14},  //has three 1 
// {15} };  //has four 1


std::set<Implicant> Prime_Generate(Function &f);//Input function , return Prime_implicants.
std::set<Implicant> Min_Cover(Function &f,std::set<Implicant>&prime);//Use smallest prime_implicants to cover function f,and return those implicants. 
inline std::set<Implicant> QuineMcCluskey(Function&f)
{
    std::set<Implicant> prime = Prime_Generate(f);//generate prime implicants
    return Min_Cover(f,prime);//cover
}

#endif
