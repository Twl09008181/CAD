
CC = g++ 
FLAG = -std=c++11

LIBSRC += $(wildcard ../lib/*.cpp)
LIBOBJ = $(patsubst %.cpp,%.o,$(LIBSRC))
H = $(wildcard ../lib/*.hpp)


$(NAME) :$(LIBOBJ) $(NAME).cpp
	$(CC) $(FLAG) $^ -o $@ 
$(NAME).o : $(NAME).cpp $(H)
	$(CC) $(FLAG) -c $<
%.o : %.cpp %.hpp
	$(CC) $(FLAG) -c $< -o $@ 
clean:
	rm *.exe $(LIBOBJ) *.o
