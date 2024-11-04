BIN=a.out

all: $(BIN)
	
$(BIN): main.cpp board.hpp
	clang++ -std=gnu++2b -o $(BIN) main.cpp
