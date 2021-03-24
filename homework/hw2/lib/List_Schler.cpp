#include "List_Schler.h"


void error_op_type_msg(int s1,int s2)
{
    cerr<<"resource size invalid!! "<<"DFG's op kind = "<<s1<<" but "<<"resource size = "<<s2<<endl;
}
vector<int>ML_RCS(DFG *dfg,vector<int>&resource)
{
    //step 0 : check 資源的數量對得上dfg當中操作的數量---------------------------------------------
    int type_num = resource.size();//取得operation(excluding 'i','o')的種類數
    if(type_num!=dfg->get_op_type_num()){error_op_type_msg(dfg->get_op_type_num(),resource.size());exit(1);}//種類數不合
    
    //初始化SCH
    List_Schler SCH(resource,dfg);
    SCH.init_Input();//由input開始進行schedule,並將能放入ready_q的操作放入
    int l = 0;
    while(!SCH.is_done())
    {
        for(unsigned int tp = 0;tp < type_num;tp++)
            SCH.run(tp);//去執行 type = tp 的working_q當中的operation
        for(unsigned int tp = 0;tp<type_num;tp++)
           SCH.dispatch(tp,l);//由ready queue當中取出事件加入working queue
        l++;
    }
    return SCH.Schedule_result();
}


vector<int>MR_LCS(DFG *dfg,int latency)
{
    int type_num = dfg->get_op_type_num();
    vector<int>resource(type_num,1);//初始化為1
    vector<int>ALAP_schedule = ALAP(dfg,latency);

    //任何一個input的schedule時間必須小於0
    for(auto i:dfg->get_input_index())
        if(ALAP_schedule.at(i)<0)
            return {-1};//該latency無解
    
        //初始化SCH
    List_Schler SCH(resource,dfg);
    SCH.init_Input();//由input開始進行schedule,並將能放入ready_q的操作放入
    int l = 0;
    while(!SCH.is_done())
    {
        for(unsigned int tp = 0;tp < type_num;tp++)
            SCH.run(tp);//去執行 type = tp 的working_q當中的operation
        for(unsigned int tp = 0;tp < type_num;tp++)
            SCH.dispatch_if(tp,l,ALAP_schedule,Urgent);
         for(unsigned int tp = 0;tp<type_num;tp++)
           SCH.dispatch(tp,l);//由ready queue當中取出事件加入working queue
        l++;
    }
    return resource;
}
