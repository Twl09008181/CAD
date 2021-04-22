#ifndef QU_MC_hpp
#define QU_MC_hpp

//--------------------------------------S T L -------------------------------------------------
#include <vector>
#include <map>

//--------------------------Data structure this lib use--------------------------
#include "Function.hpp"
#include "Implicant.hpp"
#include "Prime_Implicant_Chart.hpp"
using Implicant_Combine_table = std::vector<std::map <Implicant,bool>>;

//--------------------------Petrick’s Method-------------------------------------
#include "SAT.hpp"

//--------------------------print_depedency--------------------------------------
#include <iostream>
#include <iomanip>

std::vector<Implicant> Prime_Generate(Function &f);//Input function , return Prime_implicants.
std::vector<Implicant> Min_Cover(Function &f,std::vector<Implicant>&prime);//Use smallest prime_implicants to cover function f,and return those implicants. 
inline std::vector<Implicant>  QuineMcCluskey(Function&f)
{
    std::vector<Implicant> prime = Prime_Generate(f);//generate prime implicants
    return Min_Cover(f,prime);//cover
}

#endif
