# Makefile for netcalc project

# Compiler and flags
CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -g

# Project name and output directory
NAME = netcalc
BUILD_DIR = build

# Source files and object files
SRC_DIR = src
SRCS = $(SRC_DIR)/netcalc.c \
       $(SRC_DIR)/pollserver.c \
       $(SRC_DIR)/process_file.c \
       $(SRC_DIR)/evaluate.c \
       $(SRC_DIR)/shared_mutex.c \
       $(SRC_DIR)/math_utils.c

OBJS = $(SRCS:.c=.o)

# Default target
all: $(BUILD_DIR)/$(NAME)

# Create output directory if it doesn't exist and link objects
$(BUILD_DIR)/$(NAME): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(SRC_DIR)/*.o
	rm -rf $(BUILD_DIR)

.PHONY: all clean

