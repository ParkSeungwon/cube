CFLAG = -g -c -fmax-errors=1 -std=c++11
INCLUDE = -I../
CC = g++
OBJ = $(patsubst %.cc, ../obj/%.o, $(wildcard *.cc))
MAIN_OBJ = $(patsubst %.cpp, ../obj/%.x, $(wildcard *.cpp))

all : $(OBJ) $(MAIN_OBJ)

../obj/%.o : %.cc 
	$(CC)  $(INCLUDE) $(CFLAG) $< -o $@

../obj/%.x : %.cpp
	$(CC)  $(INCLUDE) $(CFLAG) $< -o $@
