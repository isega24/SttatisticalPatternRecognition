CC=clang++-3.8
CFLAGS=-Wall -std=c++11 -g -Iinclude
LDFLAGS=
BIN=./bin
SRC=./src
OBJ=./obj
vpath %.cpp src
vpath %.h include

all:program1 program2 program3 program4 program5


git:
	git add -A
	git commit -m "Modifiations to the program."
	git push -u origin master


program1: $(SRC)/program1.cpp
	$(CC) $(LDFLAGS) $(CFLAGS) -o $(BIN)/$@ $^

program2: $(SRC)/program2.cpp
	$(CC) $(LDFLAGS) $(CFLAGS) -o $(BIN)/$@ $^

program3: $(SRC)/program3.cpp
	$(CC) $(LDFLAGS) $(CFLAGS) -o $(BIN)/$@ $^

program4: $(SRC)/program4.cpp
	$(CC) $(LDFLAGS) $(CFLAGS) -o $(BIN)/$@ $^

program5: $(SRC)/program5.cpp
	$(CC) $(LDFLAGS) $(CFLAGS) -o $(BIN)/$@ $^

clean:
	rm $(BIN)/* $(OBJ)/* $(RES)/*
