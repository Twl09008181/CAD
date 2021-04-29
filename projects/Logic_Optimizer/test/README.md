# 	HowToBuild

```
$make NAME=TestUnitName
```

## EXAMPLE 	

```
$ make NAME=QuineMcCluskey
g++  -std=c++11 -c ../src/Implicant.cpp -o ../src/Implicant.o
g++    -c -o ../src/QuineMcCluskey.o ../src/QuineMcCluskey.cpp
g++  -std=c++11 -c ../src/Prime_Implicant_Chart.cpp -o ../src/Prime_Implicant_Chart.o
g++  -std=c++11 -c ../src/SAT.cpp -o ../src/SAT.o
g++  -std=c++11 ../src/Implicant.o ../src/QuineMcCluskey.o ../src/Prime_Implicant_Chart.o ../src/SAT.o QuineMcCluskey/QuineMcCluskey.o -o ./QuineMcCluskey.exe
build complete :  QuineMcCluskey
```



