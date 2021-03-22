#include<iostream>
#include<fstream>
#include<string>
#include<forward_list>
#include<list>
using namespace std;
#include "./lib/DFG.h"
#include "./lib/UC_schler.h"




DFG *get_DFG(char *file_name);



bool sch_end(const vector<DFG::index>&Output,vector<int>&schedule)
{
    for(auto o:Output)
    {
        if(schedule[o]==0)return false;//有一個output還沒被schedule到
    }
    return true;
}




vector<int>ML_RCS(DFG *dfg,vector<int>&resource)
{
    const vector<DFG_node>& V = dfg->get_node_vector();
    vector<int>degree(V.size(),-1);//到時候給ready_queue使用的
    for(int i = 0;i<V.size();i++)degree[i] = V.at(i).get_parent_num();
    
    int type_num = resource.size();//excluding 'i','o' 的操作數量


    //Queue init
    using R = forward_list<int>;
    struct ongoing_node
    {
        DFG::index i;
        int t;
    };
    
    using O = list<ongoing_node>;//越早加入的會被放在越後面,然而要pop掉越後面的就只能透過雙向list,如果透過單向會很花時間,而且雙向list的size()是const time.
    vector<R>ready_state_Q(type_num,R{});//ready queue
    vector<O>Ongoing_Q(type_num,O{});//ongoing queue 裡面放delay,等等用扣的,扣到0就釋放資源

    //start from input
    vector<DFG::index>Input_index = dfg->get_input_index();
    for(auto i:Input_index)
    {
        auto chck_list = V.at(i).get_child_list();//check child
        for(DFG::node_val n :chck_list)
        {
            DFG::index chck_index = dfg->get_index(n);
            
            if(!--degree[chck_index]){
                int t = V.at(chck_index).type_index()-2;//得到該child的type類型
                ready_state_Q.at(t).push_front(chck_index);//放入適當的ready_queue當中
            }
        }
        
    }
    
    // for(int i = 0;i<type_num;i++){
    //     cout<<"type :"<<i<<endl;
    //     for(auto c:ready_state_Q.at(i))
    //     {
    //         cout<<"val = "<<V.at(c).get_val()<<endl;
    //     }
    // }

   

        vector<int>schedule_time(V.size(),0);
    int l = 0;
    while(!sch_end(dfg->get_output_index(),schedule_time))//有output node還沒被schedule到
    {
        cout<<"l = "<<l<<endl;
        vector<O>next_stage(type_num,O{});
        for(int t = 0;t < type_num;t++)//每一種type
        {   
            auto &curr_q = Ongoing_Q.at(t);//該type的ongoning Q
            
            vector<decltype(curr_q.begin())> trash;
            
            for(auto it = curr_q.begin();it != curr_q.end();it++)//扣掉,且如果扣完是0下一步驟會釋放
            {   
                if(--(*it).t==0)
                {
                    
                    trash.push_back(it);
                    DFG::index index= (*it).i;
                    const forward_list<DFG::node_val>& chck_list = V.at(index).get_child_list();
                    
                    for(auto n:chck_list)
                    {
                        DFG::index chck_index = dfg->get_index(n);
                        if(--degree[chck_index]==0)
                        {
                            
                            int t = V.at(chck_index).type_index()-2;
                            
                            if(t>=0)
                                ready_state_Q.at(t).push_front(chck_index);
                            else
                                schedule_time[chck_index] = l;
                            cout<<"node: "<<V.at(index).get_val()<<" put "<<V.at(chck_index).get_val()<<" into ready"<<endl;
                        }
                    }
                }
                
            }

            for(auto &it:trash)//釋放
            {
                curr_q.erase(it);
            }

            
            
            

            for(int t = 0;t<type_num;t++){
                int on_going_num = Ongoing_Q.at(t).size();//Tk
                cout<<"type : "<<t<<endl;
                while(on_going_num<resource.at(t))//ak-TK
                {   
                    
                    if(!ready_state_Q.at(t).empty()){//schedule

                        DFG::index index = ready_state_Q.at(t).front();ready_state_Q.at(t).pop_front();
                        cout<<"node = "<<V.at(index).get_val()<<endl;//schedule
                        //現在的index要schedule了,先取得執行時間
                        //Ongoing_Q.at(t).push_back({index,V.at(index).get_delay()});//ongoing queue裡面放這個op的delay
                        next_stage.at(t).push_front({index,V.at(index).get_delay()});
                        schedule_time[index] = l;//schedule this node in t = l
                        on_going_num++;
                    }
                    else{
                        break;
                    }
                }
            }
            
           
        
        }
        for(int i = 0;i<type_num;i++)
        {
            for(auto it = next_stage.at(i).begin();it!=next_stage.at(i).end();it++)
                Ongoing_Q.at(i).push_front(*it);
        }
        l++;
    }
    cout<<"latency = "<<l-1<<endl;
    return schedule_time;

   
}



int main(int argc,char*argv[])
{   
    DFG *dfg = get_DFG(argv[1]);
    vector<int>R{1,1};
    ML_RCS(dfg,R);


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
