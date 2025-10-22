# Compiler and flags
CC     = gcc
CFLAGS = -Wall -Wextra -g

# Project files
SRC    = main.c graph.c
OBJ    = $(SRC:.c=.o)
DEPS   = graph.h 

# Output program name
TARGET = program

# Default rule (first one = default target)
all: $(TARGET)

# Link objects into final executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compile .c into .o (auto-dependency on headers)
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean build files
clean:
	rm -f $(OBJ) $(TARGET)

# Run program after build
run: $(TARGET)
	./$(TARGET)
