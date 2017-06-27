CC=g++
all: main.cpp Game.cpp Player.cpp
	$(CC) main.cpp Game.cpp Player.cpp -o main

