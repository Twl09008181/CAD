#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include<vector>
#include <algorithm>
using namespace std;

#include"../header/gate.h"
#include"../header/String_Process.h"

/*
Function :
    string extract_num(const string&I_O);
description:
    input string with format ( ),like 10=NAND(10,20,30) or Input(10)
    the function will return the first number in (),in above  case is both 10
warning:
    you'r string need have ().
*/
string extract_num(const string&I_O);
bool binary_search(const vector<int>&V,int target);
ostringstream& get_N(ostringstream&ostrm,const string&N);

void read(char *argv[],vector<gate>&Gate,vector<int>&Output_V,ostringstream&Input_N,ostringstream&Output_N,ostringstream&Wire_N);
void print(char *argv[],vector<gate>&Gate,vector<int>&Output_V,ostringstream&Input_N,ostringstream&Output_N,ostringstream&Wire_N);


int main(int argc,char *argv[])
{   
    vector<gate>Gate;
    vector<int>Output_V;//為了二元搜尋,int type
    ostringstream Input_N,Wire_N,Output_N;//sstrm
    read(argv,Gate,Output_V,Input_N,Output_N,Wire_N);
    print(argv,Gate,Output_V,Input_N,Output_N,Wire_N);
    return 0;
}

void read(char *argv[],vector<gate>&Gate,vector<int>&Output_V,ostringstream&Input_N,ostringstream&Output_N,ostringstream&Wire_N)
{
    ifstream benchmark{argv[1]};
    if(!benchmark)
    {
        cerr<<"Benchmark file cann't' open!"<<endl;
        exit(1);
    }
    string line;
    int count_line = 0;
    bool un_sort = true;
    while(getline(benchmark,line))
    {   
        count_line++;
        string keyword = get_first_of_line(line);//get the first nonempty words. 
        if(keyword.empty()||keyword.front()=='#')continue;//# or empty line.

        if(keyword.find("INPUT")==0)//is INPUT
        {   
            get_N(Input_N,extract_num(line));
        }
        else if (keyword.find("OUTPUT")==0)//is OUTPUT
        {
            string n = extract_num(line);
            get_N(Output_N,n);

            Output_V.push_back(stoi(n));
            un_sort  = true;//假設不一定會照順序排
        }
        else if(isdigit(keyword.at(0)))//is gate
        {   

            Gate.push_back(line);
            auto g = *(Gate.end()-1);
            if(un_sort)//sort output
            {
                sort(Output_V.begin(),Output_V.end());
                un_sort = false;
            }
            if(!binary_search(Output_V,stoi(g.get_output())))////if this gate's output is wire,we shouldn't put it to wire_n.
                get_N(Wire_N,g.get_output());      
        }
        else cerr<<"Line:"<<count_line<<"\nundefind input:\n"<<keyword<<endl;//undefined input
    }
    benchmark.close();
}

void print(char *argv[],vector<gate>&Gate,vector<int>&Output_V,ostringstream&Input_N,ostringstream&Output_N,ostringstream&Wire_N)
{
    ofstream output_v{argv[2]};
    if(!output_v)
    {
        cerr<<"cann't open "<<argv[2]<<endl;
        exit(1);
    }
    output_v<<"module "<<split(argv[1],'.').at(0)<<" ("<<Input_N.str()<<","<<Output_N.str()<<");\n"<<endl;
    output_v<<"input "<<Input_N.str()<<";\n"<<endl<<"output "<<Output_N.str()<<";\n"<<endl<<"wire "<<Wire_N.str()<<";\n"<<endl;

    for(int i = 0;i<Gate.size();++i)
    {
        const gate & g = Gate.at(i);
        output_v<<lower(g.get_name())<<" "<<g.get_name()<<g.get_input().size()<<"_"<<i+1<<" (N"<<g.get_output();
        for(const auto &input:g.get_input())
            output_v<<" ,N"<<input;
        output_v<<");"<<endl;
    }
    output_v<<"\nendmodule"<<endl;
    output_v.close();
}
string extract_num(const string&I_O)
{
    int i = I_O.find('(')+1;
    int j = I_O.find(')');
    vector<string> tmp = split(I_O,',',i,j,-1,' ');//忽略空格,允許INPUT(   1)
    return tmp.at(0);
}
ostringstream& get_N(ostringstream&ostrm,const string&N)
{
    if(N!=""){
        if(!ostrm.str().empty())
            ostrm<<",";
        ostrm<<"N"<<N;
    }
    return ostrm;
}
bool binary_search(const vector<int>&V,int target)
{
    int l = 0;
    int r = V.size() - 1;
    while(l<=r)
    {
        int mid = (l+r)/2;
        if(V.at(mid)==target)return true;
        else if (V.at(mid)>target)r = mid-1;
        else l = mid+1;
    }
    return false;
}
