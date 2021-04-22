# Logic Optimizer using Quine-McCluskey and Petrick_Method  

[Demo](#demo)
* [QuineMcCluskey_demo](#quinemccluskey_demo)
* [Prime_Implicant_Chart_demo](#prime_implicant_chart_demo)
* [Prime_generate_demo](#prime_generate_demo)
* [SAT_demo](#sat_demo)   

[FolderStructure](#folderstructure)  
* [Lib](#lib)
* [demo](#demo_cpp)  

[DataStructure](#datastructure) 
* [Function](#function)   
* [Implicant](#implicant)
* [Implicant_Combine_table](#implicant_combine_table)
* [Prime_Implicant_Chart](#prime_implicant_chart)  
* [SAT_interface](#sat_interface ) 

## Introduction 
A Lib base on   

1. [Quine–McCluskey algorithm](https://en.wikipedia.org/wiki/Quine%E2%80%93McCluskey_algorithm)     
2. [Petrick's method](https://en.wikipedia.org/wiki/Petrick%27s_method) 

I optimize the prime_implicant finding part,And it can be validated in simple way.  
check  [Implicant](#implicant) 


## How to Use 

## Demo    

### QuineMcCluskey_demo

### Prime_Implicant_Chart_demo

### Prime_generate_demo  

### SAT_demo    

## FolderStructure    

### Lib  
  * `QuineMcCluskey.hpp : Final interface, Include Generate prime implicants/min cover. `
  * `Function.hpp       : A input format for kernel lib.`
  * `Implicant.hpp      : A kernel part in Generate prime implicants.`
  * `Prime_Implicant_Chart.hpp  : A kernel part in min cover.`
  * `SAT.hpp  : A kernel part in min cover used to implement Petrick's method.`


### demo_cpp 
  * `QuineMcCluskey_demo.cpp  `
  * `Prime_generate_demo.cpp  `
  * `Prime_Implicant_Chart_demo.cpp `
  * `SAT_demo.cpp `


## DataStructure   


### Function  

A standard function format in all Lib  
``` using Function = std::vector<std::vector<int>>; ``` 

The format example:
```
Function F = {
        {},     // has zero 1 , if empty,still need a {}
        {4,8},    // has one 1 
        {9,10,12},  //has two 1
        {11,14},  //has three 1 
        {15} };  //has four 1
```
<img src = "https://user-images.githubusercontent.com/52790122/115750138-6baaa980-a3ca-11eb-869d-bb69d74b4107.png" width = "200">

### Implicant   
A kernel part in Generate prime implicant by combine.    

Constructor 
```
 Implicant(type v,type dash_part = 0)
       :val{v},cover{dash_part}
      {}
```
Important data members

```
type val; // val without consider dash_part, for example :  0b10-1  means   0b1001 + 0b00-0(dash-part), and val = 0b1001 = 9  
type cover; // use to store dash part, for example  0b10-1 means cover = 0b0010(dash-part) = 2
```
take the same example  :  
<img src = "https://user-images.githubusercontent.com/52790122/115751707-02c43100-a3cc-11eb-9cff-acb20f278cbd.png" width = "500">

```
m4	0100  : val = 0100 (base part:4)  , cover = 0000 (dash part : 0)                so it can cover m4
m(4,12)	-100* : val = 100 (base part : 4) , cover : -000 (dash part : 8)            so it can cover m4,m12 ( base + 1000)
m(8,9,10,11)	10--  :  val = 1000 (base part : 8) , cover : 00-- (dash part : 3)    so it can cover m8,m9(base + 0001),m10(base + 0010),m11(base + 0011)
```

Implicants can combine each other iff  
1. differ by 1 bit.    
2. has same dash part : cover must be same. 

```
bool diff_one_bit(const Implicant&I1,const Implicant&I2)
{
    if(I1.get_cover()!=I2.get_cover())return false;//different cover

    unsigned int diff = I1.get_val() ^ I2.get_val();//do xor , we can get difference
    
    return ((diff)&(diff-1))==0;//diff is power of 2
}
```
With cover , we can compare two implicants without iterating all characters and  check fastly.

### Implicant_Combine_table  

It is defined in  QuineMcCluskey.hpp 


```
using Implicant_Combine_table = std::vector<std::map <Implicant,bool>>;//use in phase 1 : find prime_implicants
```

<img src = "https://user-images.githubusercontent.com/52790122/115758701-0064d580-a3d2-11eb-9e72-431e2bf2e115.png" width = "500"> 

I use std::map <Implicant,bool> for two reasons 
```
1. The new implicant durring combining may duplicate.   
2. The implcant in table need a record to indentify whether it is  a prime implicant (*). 
```

### Prime_Implicant_Chart


### SAT_interface 

