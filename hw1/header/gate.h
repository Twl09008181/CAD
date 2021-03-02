
#ifndef GATE_H
#define GATE_H
#include "String_Process.h"
#include<iostream>
using namespace std;
class gate{
public:
    friend vector<string> split(const string&str,char symbol,int i,int j,bool first);
    gate(const string&str)
    {
        vector<string> tmp1 = split(str,'=',0,-1,-1,' ');//omit space and split by '='
        output = tmp1.at(0);//leftside of =
        vector<string>tmp2 = split(tmp1.at(1),'(');//right side of = 
        gate_name = tmp2.at(0);//left side of (
        if(tmp2.at(1).find(')')==string::npos)
        {
            cerr<<"format error: "<<str<<endl;
            exit(1);
        }
        input = split(tmp2.at(1),',',0,tmp2.at(1).find(')'));
    }

    gate(const string&o,const string &g,vector<string>&i)
    :output(o),gate_name(g),input(i)
    {
    }
    const string& get_output()const{return output;}
    const string& get_name()const{return gate_name;}
    const vector<string>& get_input()const{return input;}
private:
    string gate_name;
    string output;
    vector<string>input;
};

#endif
