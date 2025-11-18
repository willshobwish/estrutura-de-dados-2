CC     = gcc
CFLAGS = -Wall -Wextra -g

SRC    = main.c graph.c
OBJ    = $(SRC:.c=.o)
DEPS   = graph.h 

TARGET = program

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	./$(TARGET)
