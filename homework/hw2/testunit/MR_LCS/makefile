

CC = g++
FLAG = -std=c++11
LIBSRC += ../../lib/UC_Schler.cpp 
LIBSRC += ../../lib/DFG.cpp
LIBSRC += ../../lib/MR_LCS.cpp
LIBOBJ = $(patsubst %.cpp,%.o,$(LIBSRC))
H_dependency = $(patsubst %.cpp,%.h,$(LIBSRC))
all: main.o $(LIBOBJ)
	$(CC) $(FLAG)  $^ -o main.exe

main.o:main.cpp $(H_dependency)
	$(CC) $(FLAG) main.cpp -c 
%.o:%.cpp %.h
	$(CC) $(FLAG) -c $< -o $@
run:
	./main.exe test.txt
clean:
	rm *.exe *.o
