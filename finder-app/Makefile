# Compiler selection
# If CROSS_COMPILE is not set, CC defaults to gcc
CC := $(CROSS_COMPILE)gcc

# Compiler flags
CFLAGS := -Wall -Werror

# Target executable
TARGET := writer

# Source and object files
SRC := writer.c
OBJ := writer.o

# Default target
all: $(TARGET)

# Build the writer application
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -static -o $(TARGET) $(OBJ) 

# Compile source to object file
$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)

# Clean target
clean:
	rm -f $(TARGET) *.o

# Phony targets
.PHONY: all clean