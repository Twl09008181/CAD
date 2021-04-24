
CC = g++ 
FLAG = -std=c++11

LIBSRC += $(wildcard ../lib/*.cpp)
LIBOBJ = $(patsubst %.cpp,%.o,$(LIBSRC))
H += $(wildcard ../lib/*.hpp)
H += $(wildcard ./*.hpp)

Ouput_example :$(LIBOBJ) Ouput_example.cpp
	$(CC) $(FLAG) $^ -o $@ 
Ouput_example.o : $(NAME).cpp $(H)
	$(CC) $(FLAG) -c $<
%.o : %.cpp %.hpp
	$(CC) $(FLAG) -c $< -o $@ 
clean:
	rm *.exe $(LIBOBJ) *.o
