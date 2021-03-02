#include"../header/gate.h"
#include"../header/String_Process.h"
#include<string>
#include<vector>
#include<iostream>
using namespace std;


/*
Function :vector<string> split(const string&str,char symbol,int l,int r,int num,const char omit)
description:
    input a string and symbol,the function will split the string by the symbol and form a new string vector,and return .
    l : the start index you want to check,default is 0
    r : the end index you want to check,default is -1,means str.size();
    check range is = [l,r)

    num: the time you want to split by symbol,this means your return size is num+1
    omit:you can choose another character type to omit.
    example:
    symbol =','
    omit = ' ' //means space
    l = 4
    r = -1
    num = -1
    input = abc(1,2,3  5,4  sa)
    then output : [1,2,35,4sa)]

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
