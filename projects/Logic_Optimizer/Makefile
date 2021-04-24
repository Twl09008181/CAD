
CC = g++ 
FLAG = -std=c++11

LIBSRC += $(wildcard ./lib/*.cpp)
LIBOBJ = $(patsubst %.cpp,%.o,$(LIBSRC))
H += $(wildcard ./lib/*.hpp)
H += ./Output_Interface/Output.hpp
H += ./Intput_Interface/Input.hpp

main :$(LIBOBJ) main.cpp
	$(CC) $(FLAG) $^ -o $@ 
main.o : $(NAME).cpp $(H)
	$(CC) $(FLAG) -c $<
%.o : %.cpp %.hpp
	$(CC) $(FLAG) -c $< -o $@ 
clean:
	rm *.exe $(LIBOBJ) *.o
