
CC = g++ 
FLAG = -std=c++11

LIBSRC += $(wildcard ../src/*.cpp)
LIBOBJ = $(patsubst %.cpp,%.o,$(LIBSRC))

private_H += $(wildcard ../src/*.hpp)

public_H  = ../include/Input/Input.hpp
public_H  += ../include/Output/Output.hpp
public_H += ../include/QuineMcCluskey/QuineMcCluskey.hpp


all : $(NAME)
	@echo "build complete : " $(NAME)

$(NAME) :$(LIBOBJ) ./$(NAME)/$(NAME).o 
	$(CC) $(FLAG) $^ -o ./$(NAME).exe

./$(NAME)/$(NAME).o : ./$(NAME)/$(NAME).cpp $(private_H) $(public_H) 
	$(CC) $(FLAG) -c $< -o $@

./src/QuineMcCluskey.o : ../src/QuineMcCluskey.cpp ../include/QuineMcCluskey/QuineMcCluskey.hpp
	$(CC) $(FLAG) -c $< -o $@

%.o : %.cpp %.hpp
	$(CC) $(FLAG) -c $< -o $@ 
clean:
	rm *.exe $(LIBOBJ) *.o
