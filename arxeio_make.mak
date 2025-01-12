# Compilerr
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c99

# Source files
SRC = e_shop_askisi.c

# Target executable
TARGET = e_shop

# Default rule to build the executable
$(TARGET): $(SRC) e_shop.h
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Rule to clean up build files
clean:
	rm -f $(TARGET)
