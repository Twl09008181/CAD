

CC = g++
FLAG = -std=c++11
LIBSRC += ../../lib/UC_Schler.cpp 
LIBSRC += ../../lib/DFG.cpp
LIBOBJ = $(patsubst %.cpp,%.o,$(LIBSRC))
H_dependency = $(patsubst %.cpp,%.h,$(LIBSRC))
H_dependency+=../../lib/Schler_prototype.h

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
