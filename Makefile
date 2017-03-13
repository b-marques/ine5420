FILES = $(wildcard ./src/**/*.cpp)
all:
	g++ -o exec $(FILES) `pkg-config --libs --cflags gtk+-3.0` -Wall -Werror -std=c++11
	./exec