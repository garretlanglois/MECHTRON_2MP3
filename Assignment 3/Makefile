# Makefile for VADER Sentiment Analysis Assignment

# Compiler
CC = gcc

# Compiler Flags
CFLAGS = -O3 -Wall

# Target executable name
TARGET = vader_sentiment

# Source files
SRCS = main.c vaderSentiment.c

# Build the executable
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

# Clean up build files
clean:
	rm -f $(TARGET)
