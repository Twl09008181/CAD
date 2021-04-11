#include<vector>
#include"../header/String_Process.h"
#include"../header/gate.h"
#include<iostream>
using namespace std;


int main(int argc,char *argv[])
{

    //test for gat.h format
    // string s = "20 = Nand(  1, 123  ,5  23,5  )";
    // gate g{s};
    // cout<<g.get_output()<<endl;
    // cout<<g.get_name()<<endl;
    // show_vector(g.get_input());

    // string s = "  ";
    // cout<<get_first_of_line(s).empty();



    string input = "abc(1,2,3  5,4  sa)";
    show_vector(split(input,',',4,-1,-1,' '));

    return 0;
}
