#include "../../include/Input/Input.hpp"
#include <iostream>
#include <string>
int main()
{


    //------------------------------------------str_to_implicant_val TEST-------------------------------------------

    //fA,B,C,D = A'BC'D' + AB'C'D' + AB'CD' + AB'CD + ABC'D' + ABCD.
    std::string str1 = "(!a*b*!c*!d)";//A'BC'D'
    std::string str2 = "(a*!b*!c*!d)";//AB'C'D'
    std::string str3 = "(a*!b*c*!d)";//AB'CD'
    std::string str4 = "(a*!b*c*d)";//AB'CD
    std::string str5 = "(a*b*!c*!d)";//ABC'D'
    std::string str6 = "(a*b*c*d)";//ABCD

    auto p = str_to_implicant_val(str1.begin(),str1.end(),8);
    std::cout << p.first <<"   " <<p.second << std::endl;

    p = str_to_implicant_val(str2.begin(),str2.end(),8);
    std::cout << p.first <<"   " <<p.second << std::endl;

    p = str_to_implicant_val(str3.begin(),str3.end(),8);
    std::cout << p.first <<"   " <<p.second << std::endl;

    p = str_to_implicant_val(str4.begin(),str4.end(),8);
    std::cout << p.first <<"   " <<p.second << std::endl;


    p = str_to_implicant_val(str5.begin(),str5.end(),8);
    std::cout << p.first <<"   " <<p.second << std::endl;

    
    p = str_to_implicant_val(str6.begin(),str6.end(),8);
    std::cout << p.first <<"   " <<p.second << std::endl;



    //------------------------------------------GET_FUNCTION TEST-------------------------------------------


    std::string str = "(!a*b*!c*!d)+(a*!b*!c*!d)+(a*!b*c*!d)+(a*!b*c*d)+(a*b*!c*!d)+(a*b*c*d)";

    auto F = get_function(str,4);//four is Fan_in.

    for(int num_of_ones = 0;num_of_ones < F.size();num_of_ones++)
    {
        std::cout << num_of_ones <<" : ";
        for(auto literal:F[num_of_ones])
            std::cout << literal <<"  ";
        std::cout << std::endl;
    }

}
