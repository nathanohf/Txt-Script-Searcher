# Compiler and flags
CC = gcc
CFLAGS = -Wall -std=c99

# Output executable
OUTPUT = prog

# Source files
SRCS = searcher.c

# Object files (generated from source files)
OBJ_FILES = $(SRCS:.c=.o)

# Default target to build the program
all: $(OUTPUT)

# Rule to build the target executable
$(OUTPUT): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(OUTPUT)

# Rule to compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(OBJ_FILES) $(OUTPUT)

# Phony targets (not actual files)
.PHONY: all clean

