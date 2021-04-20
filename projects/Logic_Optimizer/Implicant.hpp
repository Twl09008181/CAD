#ifndef Imp_hpp
#define Imp_hpp

#include <vector>
#include <iostream>
class Implicant
{
public:
    using type = unsigned int ;
    Implicant(type v,type dash_part = 0)
        :val{v},cover{dash_part}
        {}
    std::vector<type> get_cover_terms()const;//return all minterms which this implicant can cover.
    bool operator<(const Implicant&rhs)const
    {
        if(val < rhs.val)return true;
        else if (val==rhs.val && cover < rhs.cover)return true;
        return false;
    }
    type get_val()const{return val;}
    type get_cover()const{return cover;}
private:
    type val; // val without consider dash_part, for example :  0b10-1  means   0b1001 + 0b00-0(dash-part), and val = 0b1001 = 9  
    type cover; // use to store dash part, for example  0b10-1 means cover = 0b0010(dash-part) = 2
};

#endif
