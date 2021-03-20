CC = g++ 
FLAG = -std=c++11

LIBSRC += $(wildcard ./lib/*.cpp)
LIBOBJ = $(patsubst %.cpp,%.o,$(LIBSRC))
H = $(patsubst %.cpp,%.h,$(LIBSRC))

prog :$(LIBOBJ) main.o
	$(CC) $(FLAG) $^ -o $@ 
main.o : main.cpp $(H)
	$(CC) $(FLAG) -c $<
%.o : %.cpp %.h
	$(CC) $(FLAG) -c $<
clean:
	rm *.exe *o
