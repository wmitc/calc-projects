# Define the C compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g

# Find all .c files in the current directory
SOURCES = $(wildcard *.c)

# Generate a list of executable names by removing the .c extension
TARGETS = src/$(SOURCES:.c=)

# Default target: compile all executables
all: $(TARGETS)

# Rule to compile each .c file into an executable
%: %.c
	$(CC) $(CFLAGS) -o $@ $<

# Clean rule: remove all executables
clean:
	rm -f $(TARGETS)

.PHONY: all clean

