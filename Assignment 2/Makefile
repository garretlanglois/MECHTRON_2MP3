#include the flags mentioned in the assignment description
CC = gcc
CFLAGS = -O3 -fPIC -shared

#make a shared library
TARGET = libmysort.so

#the source file for the code
SRCS = mySort.c

#build the shared library
all:
    $(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

#include a clean if they want to remove the shared library
clean:
	rm -f $(TARGET)
