#include<iostream>
#include<fstream>
#include<string>
using namespace std;
#include "./lib/DFG.h"
#include "./lib/UC_schler.h"


DFG *get_DFG(char *file_name);
int main(int argc,char*argv[])
{   
    DFG *dfg = get_DFG(argv[1]);
    vector<int>schedule_result1 = ASAP(dfg);
    vector<int>schedule_result2 = ALAP(dfg,11);
    

    return 0;
}


DFG *get_DFG(char *file_name)
{

    ifstream input_file{file_name};
    if(!input_file)
    {
        cerr<<"cann't open"<<file_name<<endl;
        exit(1);
    }   

    string line;
    int add_num,mul_num,node_num,edge_num;
    add_num = mul_num = node_num = edge_num = 0;

    if(getline(input_file,line))add_num = stoi(line);
    else cerr<<"get add_num error"<<endl;
    if(getline(input_file,line))mul_num = stoi(line);
    else cerr<<"get nul_num error"<<endl;
    if(getline(input_file,line))node_num = stoi(line);
    else cerr<<"get node_num error"<<endl;
    if(getline(input_file,line))edge_num = stoi(line);
    else cerr<<"get edge_num error"<<endl;
    
    //cout<<add_num<<mul_num<<node_num<<edge_num<<endl;

    DFG *dfg = new DFG(node_num);


    // //add   node------------------------------------------------------------

    while(node_num&&getline(input_file,line))
    {
        if(line.empty())continue;
        
        auto last_non_space = line.end()-1;
        while(isspace(*last_non_space)&&last_non_space!=line.begin())
            --last_non_space;

        auto T = *last_non_space; 
    
        int num = 0;
        for(auto iter = line.begin();iter!=last_non_space;iter++)//累加
            if(isdigit(*iter))
                num = num*10+(*iter-48);
        
        dfg->add_node(num,T);//添加node
        node_num--;
    }
    if(node_num){cerr<<"get node error"<<endl;exit(1);}
    
 
    // //add  node------------------------------------------------------------


    //add edges
    while(edge_num&&getline(input_file,line))
    {
        if(line.empty())continue;

        int n1 = 0;
        int n2 = 0;

        auto iter = line.begin();
        while (isspace(*iter)&&iter!=line.end())
            iter++;
        
        while(isdigit(*iter)&&iter!=line.end())
        {
            n1 = n1*10 + *iter-48;
            iter++;
        }
        while (isspace(*iter)&&iter!=line.end())
            iter++;
        while(isdigit(*iter)&&iter!=line.end())
        {
            n2 = n2*10 + *iter-48;
            iter++;
        }
        dfg->add_edge(n1,n2);
        edge_num--;
    }
    if(edge_num){cerr<<"get edges error"<<endl;exit(1);}
    //dfg->show_DFG();



    input_file.close();

    return dfg;
}
