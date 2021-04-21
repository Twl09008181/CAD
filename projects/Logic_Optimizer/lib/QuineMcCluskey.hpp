
#ifndef QU_MC_hpp
#define QU_MC_hpp

#include <vector>
#include <map>
#include "Implicant.hpp"
#include "Function.hpp"

std::vector<Implicant> Prime_Generate(Function &f);//Input function , return Prime_implicants.
std::vector<Implicant> Min_Cover(Function &f,std::vector<Implicant>&prime);//Use smallest prime_implicants to cover function f,and return those implicants. 
inline std::vector<Implicant>  QuineMcCluskey(Function&f)
{
    std::vector<Implicant> prime = Prime_Generate(f);//generate prime implicants
    return Min_Cover(f,prime);//cover
}

#endif
