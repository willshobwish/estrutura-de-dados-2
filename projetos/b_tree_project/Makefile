CC = gcc
CFLAGS = -Wall -Wextra -g -std=c99
LIBS = -lm


TARGET = program

SOURCES = main.c b_tree.c pixel_data.c random_array_generator.c

OBJECTS = $(SOURCES:.c=.o)

HEADERS = b_tree.h pixel_data.h random_array_generator.h

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LIBS)
	@echo "Build complete! Run with: ./$(TARGET)"

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "Clean complete!"

rebuild: clean all

install: $(TARGET)
	cp $(TARGET) /usr/local/bin/
	@echo "Installed $(TARGET) to /usr/local/bin/"

debug: CFLAGS += -DDEBUG -O0
debug: $(TARGET)

release: CFLAGS += -O2 -DNDEBUG
release: clean $(TARGET)

run: $(TARGET)
	./$(TARGET)

check-deps:
	@if [ ! -f "stb_image.h" ]; then \
		echo "Warning: stb_image.h not found!"; \
		echo "Download it from: https://github.com/nothings/stb/blob/master/stb_image.h"; \
	else \
		echo "Dependencies OK!"; \
	fi

# Show help
help:
	@echo "Available targets:"
	@echo "  all      - Build the program (default)"
	@echo "  clean    - Remove generated files"
	@echo "  rebuild  - Clean and build"
	@echo "  debug    - Build with debug flags"
	@echo "  release  - Build optimized version"
	@echo "  run      - Build and run the program"
	@echo "  install  - Install to /usr/local/bin"
	@echo "  check-deps - Check if required files exist"
	@echo "  help     - Show this help message"

.PHONY: all clean rebuild install debug release run check-deps help