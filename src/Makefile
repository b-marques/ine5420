FILES = $(wildcard ./*.cpp)
all:
	g++ -o paint_manco $(FILES) `pkg-config --libs --cflags gtk+-3.0` -Wall -Werror -std=c++11 -rdynamic