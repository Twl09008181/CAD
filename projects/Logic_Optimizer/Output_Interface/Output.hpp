#ifndef OUTPUT_H
#define OUTPUT_H

#include <string>
#include <bitset>

using align = std::bitset<26>;
char literals[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'}; 

inline std::string Implicant_to_str(unsigned int val,unsigned int cover,unsigned int Fan_in)
{
    align val_align{val};     std::string val_str = val_align.to_string();
    align cover_align{cover}; std::string cover_str = cover_align.to_string();


    std::string choose_literal;choose_literal.reserve(Fan_in);  
    for(int i = 0;i < Fan_in; i ++)choose_literal.push_back(literals[i]);


    std::string ans;ans.reserve(Fan_in*3);

    int j = 26 - Fan_in;
    for(int i = 0; i < Fan_in; i++)
    {
        if((val_str.at(j+i)=='1' || cover_str.at(j+i)=='0')&&!ans.empty()){
            ans = ans + '*';
        }
        if(val_str.at(j+i) == '1'){ //positive literal   
            ans = ans + choose_literal[i];
        }
        else  if(cover_str.at(j+i) == '0'){ //negative literal
            ans = ans + '!' + choose_literal[i];
        }
    }

    return  ans;
}

#endif
