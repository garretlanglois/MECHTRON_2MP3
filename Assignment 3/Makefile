CC = gcc

CFLAGS = -Wall -Wextra -std=c11 -lm -fsanitize=address

TARGET = vaderSentiment

SRCS = main.c vaderSentiment.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(CFLAGS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJS) $(TARGET)
