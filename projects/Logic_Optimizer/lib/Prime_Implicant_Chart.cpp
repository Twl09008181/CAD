#include "Prime_Implicant_Chart.hpp"



void Prime_Implicant_Chart::init_table(const Function &f,const std::vector<Implicant>&prime)
{
    //f contain the min_terms we need to cover
    //but f groups min_terms according to the num_of_ones in each min_term.
    //first create the mapping between term_val -> index ,and we can init the Min_term_vec.
    int index = 0;
    for(auto &terms : f)
    {
        for(auto &term : terms)
        {
            term_index_mapping.insert({term,index});
            index++;
        }
    }

    //init Min_ter_vec
    Min_term_vec.reserve(index);
    for(auto &terms : f)
        for(auto &term : terms)
            Min_term_vec.push_back(min_terms{term});

    //init Prime_vec
    Prime_vec.resize(prime.size());
}




void Prime_Implicant_Chart::draw(const std::vector<Implicant>&prime)
{
    //scan prime , and draw the table 
    for(size_t p_i = 0; p_i < prime.size(); p_i++)
    {
        auto cover_Lst = prime.at(p_i).get_cover_terms();
        for(auto &term : cover_Lst)
        {
            if(term_index_mapping.find(term) == term_index_mapping.end())
            {
                std::cerr << "error mapping failed" << std::endl;
                exit(1);
            }

            auto t_i = term_index_mapping[term];//get term_index from mapping
            Min_term_vec.at(t_i).push(p_i);//term point to this prime 
            Prime_vec.at(p_i).push_back(t_i);//prime  point to this term 
        }
    }
}

