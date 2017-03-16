CC=clang++-3.8
CFLAGS=-c -Wall -std=c++11
LDFLAGS=
BIN=./bin
SRC=./src
OBJ=./obj
RES=./results
TXT=./txt
vpath %.cpp src
vpath %.h include

all:
	mkdir $(BIN) $(RES) $(TXT) $(SRC) $(OBJ)

git:
	git add -A
	git commit -m "Modifiations to the program."
	git push -u origin master



program1: $(OBJ)/program1.o
	$(CC) $(LDFLAGS) -o $(BIN)/$@ $^

$(OBJ)/%.o : $(SRC)/%.cpp
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm $(BIN)/* $(OBJ)/* $(RES)/*