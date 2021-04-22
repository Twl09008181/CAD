
#ifndef Prime_Implicant_Chart_H
#define Prime_Implicant_Chart_H

//-------------------------------------------------------S T L----------------------------------------------------
#include <vector>
#include <map>

//----------------------------------------------------Data strcure------------------------------------------------
#include "Implicant.hpp"
#include "Function.hpp"
struct min_term;
class Prime_Implicant_Chart;



//Introduction : A Datastructrue using in Prime_Implcant_chart, each min_term record the prime_implcant's index ,every index recorded can cover this min_term. 
//a public interface get_prime_index can help to indentify which prime implicant can cover this min_term.
struct min_term{
public:
    min_term(unsigned int v)
        :val{v},be_coverd{false}
    {}
    void push(int index){prime_index.push_back(index);}
    void mark(){be_coverd = true;}
    unsigned int get_val()const{return val;}
    bool is_covered()const {return be_coverd;}
    const std::vector<int>& get_prime_index()const{return prime_index;}
private:
    unsigned int val;
    bool be_coverd =  false;
    std::vector<int> prime_index;
};



//functionality:
//1. Finding Essential prime implicants 
//2. cover min_term by Essential prime implicants
class Prime_Implicant_Chart{
public:
    Prime_Implicant_Chart(const Function &f,const std::vector<Implicant>&prime)
    {
        init_table(f,prime);
        draw(prime);
    }
    void cover_terms_by_ESPI();
    std::vector<min_term>get_un_converd_Min_term()const;
    const std::vector<unsigned int>& get_Essential_prime(){
        Find_Essential();
        return Essential_prime;
    }
private:
    void init_table(const Function &f,const std::vector<Implicant>&prime);
    void draw(const std::vector<Implicant>&prime);
    void Find_Essential();

    std::vector<min_term>Min_term_vec;//each minterm save the prime_index that can cover this min_term.
    std::vector<std::vector<int>>Prime_vec;//each prime save the Min_term index that can be cover by this prime.


    //term_val in function f is not start from 1, and it may be unorderd,so we need a way to record the min_term's index.
    //use to map min_term's value into index in Min_term_vec
    std::map<unsigned int ,unsigned int>term_index_mapping;

    std::vector<unsigned int> Essential_prime;//save the index of prime which is essential.
};

inline void Prime_Implicant_Chart::Find_Essential()
{
    if(Essential_prime.empty())//only when Essential_prime is empty,we do a search.
    {
        Essential_prime.reserve(Prime_vec.size());
        for(const auto& term : Min_term_vec)
            if(term.get_prime_index().size() == 1)
                Essential_prime.push_back(term.get_prime_index().front());
    }
}

inline void Prime_Implicant_Chart:: cover_terms_by_ESPI()//use essential prime implicant to cover terms.
{
    Find_Essential();
    for(auto p_i : Essential_prime)
        for(auto terms_index : Prime_vec.at(p_i))
            Min_term_vec.at(terms_index).mark();
}

inline std::vector<min_term> Prime_Implicant_Chart::get_un_converd_Min_term()const{
    std::vector<min_term> un_cover;un_cover.reserve(Min_term_vec.size());
    for(auto &m : Min_term_vec)
        if(!m.is_covered())
            un_cover.push_back(m);
    return un_cover;
}
#endif
