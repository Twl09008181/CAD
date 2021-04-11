# Resource Constrained Scheduler    


[Input/Output](#io) 

[LIB_Introduction](#lib_introduction) 

[DFG_node](#DFG_node) 

[DFG](#dfg)     

[Schler_prototype](#schler_prototype)

[UC_Schler (ASAP/ALAP)](#UC_Schler)  

[List_Schler (ML_RCS/MR_LCS)](#List_Schler)  

[TimeComplexity](#TimeComplexity) 

[experiment](#experiment)   


## io
本次Project是要將data flow graph/硬體的delay/硬體的resource當作input輸入，並根據resource constraint的狀況下將latency盡可能的減少。  

輸出的格式:
1.	得出的latency結果
2.	每一個時間被schedule的node清單
 
 ![image](https://user-images.githubusercontent.com/52790122/114300684-1fbb5300-9af4-11eb-8471-1b83af91867b.png)

以上圖DFG為例，
輸入的硬體
1.	型態為[+,*]
2.	數量為[1,1]
3.	delay為[1,3]

經過我使用的List scheduling演算法得出的結果為  
7 

4

6 7

5 6

6

8 9

9 10

9

## LIB_Introduction       

本Lib共實作四種演算法base on DFG

包含UC_Schler當中的

1.	ASAP
2.	ALAP  

以及包含List_Schler當中的
1.	ML_RCS
2.	MR_LCS  


### DFG_node   

主要data member:  

1.	Val (型別為node_val) : 
用以紀錄node的數值  
2.	T(型別為Operation_type)   
3.	Parent,child (forward_list):使用單向list實作   
4.	Parent_size/child_size :因為forward_list取得size是線性時間，因此額外花費一點記憶體代價去紀錄長度。     
![DFG node示意圖](https://user-images.githubusercontent.com/52790122/114302918-e7207700-9afd-11eb-968b-2f172cfc3f41.png)


### DFG 
主要data_member:
1.	V : 用來存放整張圖的node val
2.	Decode : 用來記錄不同的node val對應到V當中的index,可以達到不照順序輸入node val

核心功能(Method):
1.	讀取INPUT時會用到的
1.	add_node 
2.	add_edge
3.	debug用的show_DFG
2.	ASAP/ML_RCS/MR_LCS實作時需要快速的get_input_index
3.	ALAP 實作時需要快速的get_Output_index
4.	Schler_protype設定delay時需要的get_node_vector
5.	get_index : 因為存在DFG_node當中parent/child存的是node_val而不是node_index,因此無法直接指向V,需要先透過Decode將node_val轉成node_index.  

![V資料結構示意圖](https://user-images.githubusercontent.com/52790122/114302968-2222aa80-9afe-11eb-81fa-0c476708a1f4.png)


### Schler_prototype    
觀察到那幾種Scheduler都會需要
1.	schedule_time 
2.	degree
3.	delay
4.	dfg

等四種資料來做排程，因此封裝在一起，之後UC_Schler(ASAP/ALAP)以及List_Schler(ML_RCS/MR_LCS)可以透過繼承來減少代碼的重複性，也更加好維護。

主要method:
1.	建構子:用來設定schedule_time /degree/delay。
2.	回傳排程結果


### UC_Schler   

![image](https://user-images.githubusercontent.com/52790122/114303022-6f9f1780-9afe-11eb-8fd3-75304709c5a7.png) 
![不同的參數](https://user-images.githubusercontent.com/52790122/114303028-7594f880-9afe-11eb-92a0-82d03266495d.png) 

主要data_memer:
1.	Schedule_Q: 用來做排程的QUEUE
2.	Par:設定不同的參數(針對ASAP/ALAP)
例如在跑ASAP需要檢查的degree是往parent檢查
在跑ALAP時需要檢查的degree則是往child檢查
(這邊就是用到DFG_node裡面的get_child_list/get_parent_list) 

![image](https://user-images.githubusercontent.com/52790122/114303044-82b1e780-9afe-11eb-8058-a838a06e7a0b.png) 

以及不同的時間計算方式:
ASAP的每個節點排程時間為:MAX(父節點+父delay)
ALAP的每個節點排程時間為:MIN(子節點時間-自己delay)

主要method:
1.	Init_Input():ASAP的排程由INPUT端開始 
(剛剛DFG當中的get_input_index就可以快速使用)
2.	Init_Output():ALAP的排程由OUTPUT端開始
3.	(剛剛DFG當中的get_output_index就可以快速使用)
4.	Run : 開始排程
5.	Is_done : 排程是否完成
6.	Un_lock : 會被run呼叫，用來對child/parent做degree釋放(un_lock)
7.	Wake_up : 會被Un_lock呼叫，如果degree扣除後剛好為0,將叫醒他並放入Q當中。 

![ASAP/ALAP](https://user-images.githubusercontent.com/52790122/114303052-90676d00-9afe-11eb-8c47-6f7edf9d9bd3.png)


## List_Schler
![image](https://user-images.githubusercontent.com/52790122/114303080-c3116580-9afe-11eb-9498-2c3cbeb6e1ed.png) 

主要data_memer:
1.	W_Q:working Queue : 還在進行操作的operation會被放在此
2.	R_Q:Ready Queue:degree為0,等待被放入W_Q的operation
3.	Resource:用來記錄/調整硬體資源

主要method:
1.	Run : 負責執行W_Q內的operation,並若該operation完成(delay時間結束)
會呼叫un_lock,釋放對child的資源。
2.	Dispatch:由R_Q當中挑選operation放入W_Q的動作
3.	Dispath_if:若是urgernt(slack = 0),則調整resource並將op由R_Q放入W_Q
4.	Init_Input():由input開始進行Schedule
5.	Is_done:檢查所有output是否被schedule,若是則回傳true   

     

![ML_RCS實作](https://user-images.githubusercontent.com/52790122/114303085-cdcbfa80-9afe-11eb-853f-c4e6cae6a670.png)  
![MR_LCS實作](https://user-images.githubusercontent.com/52790122/114303090-d7556280-9afe-11eb-9a53-3192c7a1c345.png)  



## TimeComplexity

使用到的演算法是List Scheduling Algorithm: ML-RCS。  

1.	前置作業:
跑ALAP(criticality)/產生Ready_Q/Working_Q以及degree設定  

![image](https://user-images.githubusercontent.com/52790122/114303136-1edbee80-9aff-11eb-9f06-fa76b0b51989.png)


2.	Schedule流程   

![image](https://user-images.githubusercontent.com/52790122/114303144-2bf8dd80-9aff-11eb-8ae7-61e9e9a3d54e.png)

時間複雜度分析:
定義n = |V|為DFG_node個數。
定義m = |E|為DFG邊數,DFG為DAG,分析  

![image](https://user-images.githubusercontent.com/52790122/114303146-331feb80-9aff-11eb-84a6-e7c673a83c74.png)   

最大邊數為N+N-1+N-2+…+1 = O(n^2) 

1.	前置作業:
ALAP/產生Ready_Q/Working_Q以及degree設定 : O(n+m) 

2.	Schedule  

  * Run():虛擬碼中working_q檢查的部分
  * 對於每個op的工作: working_node.t –=1 :時間複雜度為所有的node的delay總和 :O(K*n),(K理論上可視為常數)

  *   check所有的child:  O(m)*查到child在V的真實位置
    NODE_NUM不須按照順序輸入，所以我設計了decode去轉真實index，但是我後來看測資發現都是按照順序(1開始)輸入，因此我用Deocde(紅黑樹)去查找(O(lgn)會比較吃虧，我後面會將Decode功能開啟以及關閉來做時間上的測試。
    O(m) * 查找時間。  
  *   放入所有DFG_node進Ready_Q :  Ready_Q實作方式為STL:priority_queue,因此插入是O(lgn),時間複雜度為O(nlgn)
  *   釋放working_node  : 因為實作上不應該在遍歷容器的時候進行刪除。 所以我利用一個vector回收那些iterator,遍歷完後才刪除 因為STL的forward_list沒有提供可以操作內部Node->next的介面，因此只有remove可以使用(查找到相同值後刪除，需要時間複雜度為O(list長度)，因此我使用stl:list(雙向list)並使用erase(O(1))。所以時間複雜度為O(n).

      這邊會選擇用STL來完成實作是因為我不想再額外去寫linked_list的操作，操作本身並不難寫，但是要自己做記憶體管理，我認為單純用head的架構去做linked_list會有管理記憶體的問題(dangling pointer)，勢必需要容器去負責管理這些NODE，但我覺得太麻煩了,因為還要處理解構子的部分。不如使用STL這樣簡便的介面。

      不過後續使用STL的時候才發現,如果對於效率錙銖必較，或是彈性有特別的需求 那就得自己寫了。

總結:

1.	前置作業(ALAP/設定degreee) 的複雜度為O(m+n)  
2. Run的時間複雜度為 
  * 使用Decode  
  O(K*n)+ O(m)*O(lgn)+O(nlgn)+O(n) = O((m+n)lgn) + O(Kn)  
  * 不使用Decode 
		O(K*n)+ O(m)*O(1)+O(nlgn)+O(n) = O(m+nlgn) + O(Kn)    
    
3.Dispatch():虛擬碼中Ready_q檢查的部分
  O(n) * release的時間(priority_q的pop:logn) = O(nlgn)



分析整體複雜度
將decode功能拿掉:整體複雜度為 O((m+n)lgn) + O(Kn)
保留decode功能:整體複雜度為O(m+nlgn) + O(Kn)



## experiment 

### 實驗Decode對於整體效率的影響 
![image](https://user-images.githubusercontent.com/52790122/114303576-6a8f9780-9b01-11eb-8dc8-6a8617ec52ed.png)
  
 我讓ML_RCS執行一百萬次，並用clock來觀察時間(主要是想測演算法時間，因此這部分不包含input/output)要關掉Decode功能只要更改下列
 ![image](https://user-images.githubusercontent.com/52790122/114303586-77ac8680-9b01-11eb-9cf7-85f6e218162d.png)

為
	 ![image](https://user-images.githubusercontent.com/52790122/114303589-7a0ee080-9b01-11eb-9ebc-388f17fb3ea0.png)

即可。(不過如果input也考慮的話就要改add_edge那個method)  

前面複雜度提到過的
將decode功能拿掉:整體複雜度為 O((m+n)lgn) + O(Kn)
保留decode功能:整體複雜度為O(m+nlgn) + O(Kn)
為了用excel簡單的畫圖(x,y)數據
由測資(by case)可以發現EDGE數量大約為K n,K=1~2.1	 = O(n)
這樣就簡化成n跟time之間的關係圖了。

![image](https://user-images.githubusercontent.com/52790122/114303602-85faa280-9b01-11eb-9b6c-f1b69daf5ad4.png) 

結論是:decode的確有影響到效率，因此我最後提交的版本是沒有decode的。

### 實驗二:ML_RCS/MR_LCS的可逆性	

我在testUnit內有放每個schedule的測試單元。
MR_LCS.cpp內是利用ML_RCS的結果(latency)輸入MR_LCS得到RESOURCE  
![image](https://user-images.githubusercontent.com/52790122/114303615-9579eb80-9b01-11eb-8caa-e4d0f029fb29.png)   

可以由testacse3得知，得出來的資源不一定會比較差，但也不一定會比較好，MR_LCS跟ML_RCS兩者是獨立的。

用一個簡單的道理解釋:
一開始設的資源數太少會導致有些時間點會有很多的slack=0的工作 
因此會一瞬間大量增加資源，
所以不可能透過慢慢增加資源保證找到最佳解。
簡單的例子如下
將作業類比成工作OP數量/每天努力的最大程度為資源
1.	有10份作業,Deadline是三天後
2.	努力程度:
* 如果一開始設為1  

那就是1，1，8，最大資源就是8。
但如果是一開始努力一點
* 一開始設為2

2，2，6，最大資源就是6 
* 再努力一點設為3

3，3，4，所有最大資源就變4了

要證明MR_LCS無法透過慢慢增加資源得到跟ML_RCS的值的證明如下:只要證明這些不同的資源狀態起始值最後得出的結果會不同
這樣就可以證明MLRCS MRLCS不可逆了
因為MLRCS就是屬於其中的那個case。


