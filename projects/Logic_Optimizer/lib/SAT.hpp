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

    void add_bracket(const bracket &br);//interface,but not efficent.
    inline std::vector<int> min_cover_SAT();
    
private:
    inline bool evaulate_one_bracket(const bracket& br);
    inline bool evaulate_SAT();
    void SAT_solver(int i,std::vector<int>&ans,std::vector<int>current={});


    std::map<int,int>lit_id;//every literal in SAT is unique, use id mapping into the index in std::vector<literal>literals.
    std::vector<literal>literals;
    std::vector<bracket> brackets;//overall Product of sum of literals.
};

inline std::vector<int> SAT::min_cover_SAT()//return the minimum solution that can SAT.
{
    int min_one = literals.size();
    std::vector<int>ans(literals.size());
    for(int i = 0;i < ans.size(); i++)//set the worst solution : all literals = 1
        ans[i] = literals[i].id;
    
    SAT_solver(0,ans);
    return ans;
}

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
