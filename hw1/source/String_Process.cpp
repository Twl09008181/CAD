#include"../header/gate.h"
#include"../header/String_Process.h"
#include<string>
#include<vector>
#include<iostream>
using namespace std;

//return the number list
//with the format ()
//range is str[start_i,end_i) 
/*
Function :vector<string> split(const string&str,char symbol,int i,int j,bool first)
description:
input a string and symbol,the function will split the string by the symbol and form a new vector,and return .
key: this function will omit all space character.
*/
vector<string> split(const string&str,char symbol,int l,int r,int num,const char omit)//[l,r)
{
    string tmp_str;
    vector<string> V;V.reserve(num+2);
    
    if(r==-1) r = str.size();

    auto ptr = str.begin()+l;
    auto end = str.begin()+r;

    for(;ptr!=end&&num!=0;++ptr)
    {
        

        if(*ptr==symbol)
        {
            if(!tmp_str.empty()){//symbol also be omit
                V.push_back(tmp_str);
                tmp_str.clear();
                num--;
            }   
        }
        else
        {
            if(*ptr!=omit)
                tmp_str+=*ptr;
        }
    }

    //collect the remainder
    for(;ptr!=end;++ptr)
    {
        if(*ptr!=omit)
            tmp_str+=*ptr;
    }

    V.push_back(tmp_str);

    return V;
}

void show_vector(const vector<string>&V)
{   
    string tmp;
    cout<<"[";
    
    for(auto&v:V){
        if(!tmp.empty())
            tmp+=",";
        tmp+="'";
        tmp+=v;
        tmp+="'";
    }
    cout<<tmp<<"]"<<endl;
}


/*
Function :string lower(const string&str);
description:
input a string,the function will return the capatalized one.
*/
const string lower(const string&str)
{
    string name;
    for(const auto&c:str)
        name+=tolower(c);
    return name;
}
/*
Function :string get_first_of_line(const string&str);
description:
input a line of string split by space,the function will return the first string in this line.
*/
string get_first_of_line(const string&str)
{
    vector<string>S = split(str,' ');
    return S.at(0);
}
