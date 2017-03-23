CC=clang++-3.8
CFLAGS=-Wall -std=c++11 -g -Iinclude
LDFLAGS=
BIN=./bin
SRC=./src
OBJ=./obj
RES=./results
TXT=./txt
vpath %.cpp src
vpath %.h include

all:program1 program2


git:
	git add -A
	git commit -m "Modifiations to the program."
	git push -u origin master


program1: $(SRC)/program1.cpp
	$(CC) $(LDFLAGS) $(CFLAGS) -o $(BIN)/$@ $^

program2: $(SRC)/program2.cpp
	$(CC) $(LDFLAGS) $(CFLAGS) -o $(BIN)/$@ $^



clean:
	rm $(BIN)/* $(OBJ)/* $(RES)/*
