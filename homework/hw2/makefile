
CC = g++ 
FLAG = -std=c++11

LIBSRC += $(wildcard ./source/*.cpp)#wildcard才能列出所有相同形式的檔案,單單用*不行
LIBOBJ = $(patsubst %.cpp,%.o,$(LIBSRC))
H_file += $(wildcard ./header/*.h)


TAGET_NAME = main.exe
all:$(TAGET_NAME)

$(TAGET_NAME):main.o $(LIBOBJ)
	$(CC) $(FLAG) $^ -o $@

%.o:%.cpp $(H_file)
	$(CC) $(FLAG) -c main.cpp

DFG.o:DFG.cpp DFG.h
	$(CC) $(FLAG) -c DFG.cpp

clear:
	rm *.o *.exe
