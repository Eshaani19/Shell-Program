# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Werror -g

# Source and object files
SRC_FILES = main.c utils.c builtin.c exec.c input.c
OBJ_FILES = main.o utils.o builtin.o exec.o input.o
EXEC = rush

# Default target: build the executable
all: $(EXEC)

# Rule to link the object files and create the executable
$(EXEC): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to compile each source file into an object file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to remove compiled files
clean:
	rm -f $(OBJ_FILES) $(EXEC)

# Phony targets to avoid conflicts with file names
.PHONY: all clean
