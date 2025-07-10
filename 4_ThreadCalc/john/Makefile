# Makefile for testing tpool.c with test.c

CC = gcc
CFLAGS = -Wall -Wextra -g #-fsanitize=address
LDFLAGS = -lpthread
TARGET = test_tpool

SRCS = tpool.c test.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

