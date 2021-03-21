CC = g++ 
FLAG = -std=c++11

LIBSRC += $(wildcard ./lib/*.cpp)
LIBOBJ = $(patsubst %.cpp,%.o,$(LIBSRC))
H = $(wildcard ./lib/*.h)

prog :$(LIBOBJ) main.o
	$(CC) $(FLAG) $^ -o $@ 
main.o : main.cpp $(H)
	$(CC) $(FLAG) -c $<
%.o : %.cpp %.h
	$(CC) $(FLAG) -c $< -o $@ 
clean:
	rm *.exe $(LIBOBJ) *.o
