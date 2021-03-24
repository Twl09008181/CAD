

CC = g++
FLAG = -std=c++11
LIBSRC += ../../lib/UC_Schler.cpp 
LIBSRC += ../../lib/List_Schler.cpp
LIBSRC += ../../lib/DFG.cpp
LIBOBJ = $(patsubst %.cpp,%.o,$(LIBSRC))
H_dependency = $(patsubst %.cpp,%.h,$(LIBSRC))
H_dependency+=../../lib/Schler_prototype.h


all:ML_RCS MR_LCS

ML_RCS: ML_RCS.o $(LIBOBJ)
	$(CC) $(FLAG)  $^ -o ML_RCS.exe
ML_RCS.o:ML_RCS.cpp $(H_dependency)
	$(CC) $(FLAG) $< -c 

MR_LCS: MR_LCS.o $(LIBOBJ)
	$(CC) $(FLAG)  $^ -o MR_LCS.exe
MR_LCS.o:MR_LCS.cpp $(H_dependency)
	$(CC) $(FLAG) $< -c 

%.o:%.cpp %.h
	$(CC) $(FLAG) -c $< -o $@
run:
	./main.exe test.txt
clean:
	rm *.exe *.o
