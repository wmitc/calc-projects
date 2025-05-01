CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -g

SRC = $(wildcard src/*c)
OBJ = $(SRC:src/%.c=build/%.o)
TARGET = build/filecalc

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^
	rm -rf build/*.o

build/%.o: src/%.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

debug: CFLAGS = -Iinclude -Wall -Wextra -Wpedantic -Waggregate-return -Wwrite-strings -Wvla -Wfloat-equal -g
debug: clean all

clean:
	rm -rf build

.PHONY: all clean debug

