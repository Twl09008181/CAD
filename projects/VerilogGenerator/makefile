target = PA1_106303010
file_name = c880

test_name = main.o  #更改測試單元
TESTSRC = ./TestUnit
TESTOBJ = $(TESTSRC)/$(test_name)

CC = g++ 
FLAG = -std=c++11

LIBSRC += $(wildcard ./source/*.cpp)#wildcard才能列出所有相同形式的檔案,單單用*不行
LIBOBJ = $(patsubst %.cpp,%.o,$(LIBSRC))

H_file = ./header/*.h

#產生執行檔案
$(target).out:$(LIBOBJ) $(TESTOBJ)
	$(CC) $(FLAG) $^ -o $@
#產生.o檔案
%.o:%.cpp $(H_file)
	$(CC) $(FLAG) $< -c -o $@
clear:
	rm *.v *.out $(LIBOBJ) $(TESTOBJ)
#執行
tool:
	source /usr/cad/cadence/CIC/incisiv.cshrc
	source /usr/cad/synopsys/CIC/verdi.cshrc
run: $(target).out 
	./$< $(file_name).bench  $(file_name).v 


