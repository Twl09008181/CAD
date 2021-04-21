#ifndef SAT_HPP
#define SAT_HPP
#include <map>
#include <vector>


struct literal
{
    literal(int i,bool v = false)
        :id{i},val{v}
        {}
    int id;
    bool val;
};

class SAT{
public:
    using bracket = std::vector<int>;
    
    SAT(size_t bracket_len, size_t literal_len){
        brackets.reserve(bracket_len);
        literals.reserve(literal_len);
    }

    void add_bracket(const bracket &br);//an interface for adding bracket like (p1+p2+p7), need input {1,2,7}
    std::vector<int> min_cover_SAT();
    
private:
    inline bool evaulate_one_bracket(const bracket& br);
    inline bool evaulate_SAT();
    void SAT_solver(int i,std::vector<int>&ans,std::vector<int>current={});//recursive solve.


    std::map<int,int>lit_id;//every literal in SAT is unique, use id mapping into the index in std::vector<literal>literals.
    std::vector<literal>literals;
    std::vector<bracket> brackets;//overall Product of sum of literals.
};



inline bool SAT::evaulate_one_bracket(const bracket& br)//OR
{
    for(auto i : br)//if any literal in this bracket is one,return true.
        if(literals.at(i).val)return true;
    
    return false;
}
inline bool SAT::evaulate_SAT()//AND
{
    for(auto &br : brackets)
        if(!evaulate_one_bracket(br))//if any bracket is false, return false.
            return false;
    
    return true;
}

#endif
