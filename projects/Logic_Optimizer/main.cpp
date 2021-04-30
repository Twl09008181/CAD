#include "include/QuineMcCluskey/QuineMcCluskey.hpp"
#include "include/Input/Input.hpp"
#include "include/Output/Output.hpp"

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <utility>

std::pair<std::string,std::string>get_input(std::string file_name);
std::string get_function_str(const std::vector<Implicant>imps,unsigned int Fan_in);

int main(int argc,char *argv[])
{   

    auto info = get_input(argv[1]); 
    std::string literals = info.first;
    std::string origin_function_str = info.second; 

    unsigned int Fan_in = literals.size();
    Function F = get_function(origin_function_str,Fan_in);
    auto implicants = QuineMcCluskey(F);


    std::string opt_function_str = get_function_str(implicants,Fan_in);
    
    std::string literals_with_space;
    for(char lit:literals)
    {
        literals_with_space+=lit;
        literals_with_space+=' ';
    }

    std::ostringstream output_os;
    output_os << "INORDER = " << literals_with_space << ";\n"<<"OUTORDER = output;\n";
    output_os<<"output = "<<opt_function_str;

    std::ofstream output_file{argv[2]};
    output_file << output_os.str();
    output_file.close();
    return 0;
}

std::string get_function_str(const std::vector<Implicant>imps,unsigned int Fan_in)
{
    std::ostringstream os;
    for(const auto&imp : imps)
    {
        if(!os.str().empty())os << "+";
        os << "(" << Implicant_to_str(imp.get_val(),imp.get_cover(),Fan_in) << ")";
    }  

    return os.str();
}
std::pair<std::string,std::string>get_input(std::string file_name)
{

    std::ifstream input_file{file_name};

    if(!input_file.is_open())
    {
        std::cerr<<"cann't open testcase : " << file_name << std::endl;
        exit(1);
    }

    std::ostringstream os_content;
    for(std::string tmp;input_file >> tmp;)
        os_content << tmp;
    
    //get literals
    std::string content = os_content.str();
    auto input_start = std::find(content.cbegin(),content.cend(),'=');input_start++;
    auto input_end = std::find(input_start,content.cend(),';');
    std::string input_literals = std::string(input_start,input_end);

    //get F_str
    auto F_str_start = std::find(input_end,content.cend(),'(');
    std::string F_str =  std::string(F_str_start,content.cend());
    input_file.close();
    return {input_literals,F_str};
}
