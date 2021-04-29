#ifndef QU_MC_hpp
#define QU_MC_hpp

//--------------------------------------S T L -------------------------------------------------
#include <vector>
#include <map>

//--------------------------Data structure this lib use--------------------------
#include "../../src/Function.hpp"
#include "../../src/Implicant.hpp"
using Implicant_Combine_table = std::vector<std::map <Implicant,bool>>;//use in phase 1 : find prime_implicants
#include "../../src/Prime_Implicant_Chart.hpp"//use in phase2: find essential prime implcaints and cover terms by ESPI.


//--------------------------Petrick’s Method-------------------------------------
#include "../../src/SAT.hpp"

//--------------------------print_depedency--------------------------------------
#include <iostream>
#include <iomanip>

//-----------------------------Interface-------------------------------------------
std::vector<Implicant> Prime_Generate(const Function &f,const Function &dont_care = {},bool show_procedure = false);//phase 1 : Input function , return Prime_implicants.
std::vector<Implicant> Min_Cover(const Function &f,std::vector<Implicant>&prime);//phase 2 : Use smallest prime_implicants to cover function f,and return those implicants. 
inline std::vector<Implicant>  QuineMcCluskey(const Function&f,const Function&dont_care = {})
{
    std::vector<Implicant> prime = Prime_Generate(f,dont_care);//generate prime implicants
    return Min_Cover(f,prime);//cover , only passing f without passing dont_care
}

#endif
