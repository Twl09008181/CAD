target = PA1_106303010
file_name = c880

test_name = main.o  #更改測試單元
TESTSRC = ./TestUnit
TESTOBJ = $(TESTSRC)/$(test_name)


LIBSRC += $(wildcard ./source/*.cpp)#wildcard才能列出所有相同形式的檔案,單單用*不行
LIBOBJ = $(patsubst %.cpp,%.o,$(LIBSRC))

H_file = ./header/*.h

#執行
run: $(target).out
	./$< $(file_name).bench  $(file_name).v 
	
#產生執行檔案
$(target).out:$(LIBOBJ) $(TESTOBJ)
	g++ $^ -o $@

#產生.o檔案
%.o:%.cpp $(H_file)
	g++ $< -c -o $@
clear:
	rm *.v *.out



