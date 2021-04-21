#include "../lib/Colum_table.hpp"
#include "../lib/Function.hpp"
#include "../lib/Implicant.hpp"
#include "../lib/QuineMcCluskey.hpp"
#include <vector>
#include <iostream>




int main()
{
    Function fnct = {
        {0},     // has zero 1
        {4,8},    // has one 1 
        {5,6,9,10},  //has two 1
        {7,13},  //has three 1 
        {15} 
    };  //has four 1

    auto Prime = Prime_Generate(fnct);
    std::cout << "create table : \n";
    colum_table table{fnct,Prime};
    table.show_un_coverd();std::cout <<"\n";

    std::cout << "use ESPI to cover terms : \n";
    table.cover_terms_by_ESPI();
    table.show_un_coverd();

    return 0;
}
