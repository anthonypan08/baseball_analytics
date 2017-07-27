CC = g++
CCFLAGS = -pedantic -std=c++11 -Werror $(debug_or_optimize)
all: main.cpp Game.cpp Player.cpp
	$(CC) $(CCFLAGS) main.cpp Game.cpp Player.cpp -o main

