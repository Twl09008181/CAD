#include "include/QuineMcCluskey/QuineMcCluskey.hpp"
#include "include/Input/Input.hpp"
#include "include/Output/Output.hpp"

#include <string>
#include <sstream>
#include <iostream>


void print(const std::vector<Implicant>imps,unsigned int Fan_in);

int main()
{

    //----------------------------------------------------EXAMPLE 1 ---------------------------------------------------

    //---------------------------------------------------INPUT------------------------------------------------------------
    unsigned int Fan_in  = 4;
    
    std::string F_str = "(!a*b*!c*!d)+(a*!b*!c*!d)+(a*!b*c*!d)+(a*!b*c*d)+(a*b*!c*!d)+(a*b*c*d)";
    std::string Dont_Care_str = "(a*!b*!c*d)+(a*b*c*!d)";

    Function F = get_function(F_str,Fan_in);
    Function Dont_Care = get_function(Dont_Care_str,Fan_in);

    ////---------------------------------------------------QuineMcCluskey------------------------------------------------------------
    auto implicants = QuineMcCluskey(F,Dont_Care);

    
    ///---------------------------------------------------Output------------------------------------------------------------
    print(implicants,Fan_in);




    std::cout<<"\n\n";
    
    //-------------------------------------------------------------EXAMPLE2---------------------------------------------------------
    unsigned int Fan_in2 = 4;
    std::string F2_str = "(!a*!b*!c*!d)+(!a*b*!c*d)+(!a*b*c*!d)+(a*!b*!c*d)+(a*!b*c*!d)+(a*b*!c*d)+(a*b*c*!d)+(a*b*c*d)+(!a*b*c*d)";
    Function F2 = get_function(F2_str,Fan_in2);
    auto implicants2 = QuineMcCluskey(F2);
    print(implicants2,Fan_in2);


    return 0;
}
void print(const std::vector<Implicant>imps,unsigned int Fan_in)
{
    std::ostringstream os;
    for(const auto&imp : imps)
    {
        if(!os.str().empty())os << "+";
        os << "(" << Implicant_to_str(imp.get_val(),imp.get_cover(),Fan_in) << ")";
    }  

    std::cout << os.str();
}
