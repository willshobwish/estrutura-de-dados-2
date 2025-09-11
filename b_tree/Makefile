# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g -std=c99
LIBS = -lm

# Target executable name
TARGET = program

# Source files
SOURCES = main.c b_tree.c random_array_generator.c

# Object files (automatically generated from source files)
OBJECTS = $(SOURCES:.c=.o)

# Header files (for dependency tracking)
HEADERS = b_tree.h random_array_generator.h

# Default target - builds the program
all: $(TARGET)

# Build the main executable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LIBS)
	@echo "Build complete! Run with: ./$(TARGET)"

# Rule to build object files from source files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "Clean complete!"

# Rebuild everything from scratch
rebuild: clean all

# Install target (optional - copies to /usr/local/bin)
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/
	@echo "Installed $(TARGET) to /usr/local/bin/"

# Debug build with extra debugging info
debug: CFLAGS += -DDEBUG -O0
debug: $(TARGET)

# Release build with optimization
release: CFLAGS += -O2 -DNDEBUG
release: clean $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Check if stb_image.h exists
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

# Declare phony targets (targets that don't create files with the same name)
.PHONY: all clean rebuild install debug release run check-deps help