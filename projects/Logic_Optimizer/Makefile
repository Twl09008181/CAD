
CC = g++ 
FLAG = -std=c++11

LIBSRC += $(wildcard ./src/*.cpp)
LIBOBJ = $(patsubst %.cpp,%.o,$(LIBSRC))

private_H += $(wildcard ./src/*.hpp)

public_H  = ./include/Input/Input.hpp
public_H  += ./include/Output/Output.hpp
public_H += ./include/QuineMcCluskey/QuineMcCluskey.hpp

main :$(LIBOBJ) main.cpp 
	$(CC) $(FLAG) $^ -o $@

main.o : main.cpp $(private_H) $(public_H) 
	$(CC) $(FLAG) -c $<

./src/QuineMcCluskey.o : ./src/QuineMcCluskey.cpp ./include/QuineMcCluskey/QuineMcCluskey.hpp
	$(CC) $(FLAG) -c $< -o $@

%.o : %.cpp %.hpp
	$(CC) $(FLAG) -c $< -o $@ 
clean:
	rm *.exe $(LIBOBJ) *.o
