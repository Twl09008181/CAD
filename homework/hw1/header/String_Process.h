#ifndef String_Process_H
#define String_Process_H

#include<string>
#include<vector>
#include<sstream>
using namespace std;
void show_vector(const vector<string>&V);
vector<string> split(const string&str,char symbol=' ',int l = 0,int r = -1,int num = -1,const char omit='\0');
string get_first_of_line(const string&str);
const string lower(const string&str);
#endif
