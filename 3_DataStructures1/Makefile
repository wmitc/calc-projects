# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

# Directories
SRC_DIR = src
INC_DIR = include
BIN_DIR = bin

# Source and target discovery
SOURCES = $(wildcard $(SRC_DIR)/*.c)
BASENAMES = $(notdir $(SOURCES:.c=))
TARGETS = $(addprefix $(BIN_DIR)/, $(BASENAMES))
DEBUG_TARGETS = $(addsuffix _debug, $(TARGETS))

# Default target: compile regular executables
all: $(TARGETS)

# Debug target: compile debug executables
debug: $(DEBUG_TARGETS)

# Rule to compile regular binaries
$(BIN_DIR)/%: $(SRC_DIR)/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $<

# Rule to compile debug binaries with -DDEBUG
$(BIN_DIR)/%_debug: $(SRC_DIR)/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -g -DDEBUG -o $@ $<

# Ensure bin directory exists
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean rule: remove all binaries
clean:
	rm -rf $(BIN_DIR)

.PHONY: all debug clean

