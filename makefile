#Variables
CC = g++	#change to gcc for C
CFLAGS = -c -Wall
OBJS = wordcount.cpp	#more .o here

#run as 'make'
all: wordcount.o

wordcount.o: $(OBJS)
	#GNU compile wordcount.cpp into wordcount
	g++ wordcount.cpp -o wordcount -std=c++11 -lpthread

#run as 'make clean'
clean:
	$(RM) wordcount #remove object