#ifndef SAT_HPP
#define SAT_HPP

#include <vector>
using bracket = std::vector<bool*>;

inline bool evaulate_one_bracket(const bracket& br);
inline bool evaulate_SAT(std::vector<bracket>&SAT);
inline std::vector<int> min_cover_SAT(std::vector<bracket>&SAT,std::vector<bool*>&implicant);
void SAT_solver(int i,std::vector<bracket>&SAT,std::vector<bool*>&implicant,std::vector<int>&ans,std::vector<int>current={});



inline bool evaulate_one_bracket(const bracket& br)
{
    for(const auto p : br)//USE OR
    {
        if(*p)return true;
    }
    return false;
}

inline bool evaulate_SAT(std::vector<bracket>&SAT)
{
    for(auto &br:SAT)
        if(!evaulate_one_bracket(br))
            return false;
    
    return true;
}

inline std::vector<int> min_cover_SAT(std::vector<bracket>&SAT,std::vector<bool*>&implicant)
{
    int min_one = implicant.size();
    std::vector<int>ans(implicant.size());
    for(int i = 0;i < ans.size();i++)
        ans[i] = i+1;
    SAT_solver(0,SAT,implicant,ans);
    return ans;
}



#endif
