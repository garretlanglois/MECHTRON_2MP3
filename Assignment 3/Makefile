
CC = gcc

CFLAGS = -O3 -Wall

TARGET = vader_sentiment

SRCS = main.c vaderSentiment.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)
