CC = g++
CFLAGS = -Wall -Werror -std=c++20
INC= -I/Users/jake/Documents/Jake/computer-science/cpp/quantum_chess/include -I/opt/homebrew/include -I/usr/local/include -I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks 

test: main input.txt
	/usr/bin/time ./main <input.txt

main: main.cpp
	${CC} ${INC} ${CFLAGS} -o main main.cpp

example: main example.txt
	./main <example.txt
