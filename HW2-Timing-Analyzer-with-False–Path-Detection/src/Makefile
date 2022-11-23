CC = g++
CPPFLAGS = -g -std=c++11 -Wall -Werror -Wextra

all:	a111204.o

a111204.o:	a111204_hw2.cpp	ta.o
	$(CC) $(CPPFLAGS) a111204_hw2.cpp ta.o -o a111204.o

ta.o:	header.h ta.h ta.cpp 
	$(CC) -c $(CPPFLAGS) ta.cpp

clean:
	rm *.o *.txt


