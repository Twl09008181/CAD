
#ifndef Colum_table_H
#define Colum_table_H

#include "Implicant.hpp"
#include "Function.hpp"
#include <iostream>
#include <vector>
#include <map>

struct min_terms{
public:
    min_terms(unsigned int v)
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

class colum_table{
public:
    colum_table(const Function &f,const std::vector<Implicant>&prime)
    {
        init_table(f,prime);
        draw(prime);
        Essential_prime.reserve(prime.size());
    }
    void show_un_coverd()const;
    void cover_terms_by_ESPI();
    const std::vector<unsigned int>& get_Essential_prime(){
        Find_Essential();
        return Essential_prime;
    }
private:
    void Find_Essential();
    void init_table(const Function &f,const std::vector<Implicant>&prime);
    void draw(const std::vector<Implicant>&prime);
    std::vector<min_terms>Min_term_vec;//each minterm save the prime_index that can cover this min_terms.
    std::vector<std::vector<int>>Prime_vec;//each prime save the Min_term index that can be cover by this prime.
    std::map<unsigned int ,unsigned int>term_index_mapping;//use to map min_term's value into index in Min_term_vec
    std::vector<unsigned int> Essential_prime;//save the index of prime which is essential.
};

inline void colum_table::Find_Essential()
{
    if(Essential_prime.empty())//only when Essential_prime is empty,we do a search.
    {
        for(const auto& term : Min_term_vec)
        {
            if(term.get_prime_index().size() == 1)
                Essential_prime.push_back(term.get_prime_index().front());
        }
    }
}
inline void colum_table::show_un_coverd()const
{
    for(auto &m : Min_term_vec)
    {
        if(!m.is_covered())
        {
            std::cout << "m" << m.get_val() << " : ";
            for(const auto &p : m.get_prime_index())
            {
                std::cout << p << " ";
            }
            std::cout << std::endl;
        }
    }
}

inline void colum_table:: cover_terms_by_ESPI()//use essential prime implicant to cover terms.
{
    Find_Essential();
    
    for(auto p_i : Essential_prime)
    {
        for(auto terms_index : Prime_vec.at(p_i))
        {
            Min_term_vec.at(terms_index).mark();
        }
    }
}

#endif
