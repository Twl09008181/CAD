#include "./lib/DFG.h"
#include "./lib/UC_schler.h"

// vector<int>label(DFG*dfg,const vector<DFG::index>&Output)
// {
//     const vector<DFG_node>&V = dfg->get_node_vector();
//     vector<int>distance(V.size(),0);
//     forward_list<int> Q;
//     for(auto o:Output)Q.push_front(o);//output maybe a lot....

//     while(!Q.empty())
//     {
//         DFG::index curr = Q.front();Q.pop_front();
//         const forward_list<DFG::node_val>&check_list = V.at(curr).get_parent_list();
//          for(DFG::node_val n:check_list)
//         {
//             DFG::index chck_index = dfg->get_index(n);//check_list save  node_val, not index.so we need get index use method in dfg class.
//             distance[chck_index] = max(distance[curr]+1,distance[chck_index]);
//             Q.push_front(chck_index);
//         }
//     }
//     return distance;
// }


// vector<int>Hu_s_alg(DFG*dfg,int resource)
// {
//     vector<int>distance = label(dfg,dfg->get_output_index());
//     const vector<DFG_node>&V = dfg->get_node_vector();
//     vector<int>degree(V.size(),0);
   

//     for(int i = 0;i<V.size();i++){
//         degree[i] = V.at(i).get_parent_num();

//         if(!degree[i])
//         {
//         }
//     }

//     return d;
// }
