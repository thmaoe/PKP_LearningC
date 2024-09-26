# Compiler and flags
CC = gcc
CFLAGS = -Wall -pedantic

# Target executable
TARGET = pkp

# Source and object files
SRCS = pkp.c gaussian_elim.c generation.c matrix_utils.c mod_utils.c 
OBJS = $(SRCS:.c=.o)

# Rule to build the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to build object files
%.o: %.c
	$(CC) $(CFLAGS) -c $<

run: pkp
	./pkp

# Clean up the directory (remove executable and object files)
clean:
	rm -f $(TARGET) $(OBJS)
