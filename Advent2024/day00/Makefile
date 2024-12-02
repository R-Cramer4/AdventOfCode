CC = g++
CFLAGS = -Wall -Werror -std=c++20

test: main input.txt
	/usr/bin/time ./main <input.txt

main: main.cpp
	${CC} ${CFLAGS} -o main main.cpp

example: main example.txt
	./main <example.txt
