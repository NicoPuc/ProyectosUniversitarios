# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c11

# Directories
SRC_DIR = src
LRSH_DIR = $(SRC_DIR)/lrsh
MANAGER_DIR = $(SRC_DIR)/input_manager
OBJ_DIR = obj

# Source files
SRCS = $(LRSH_DIR)/main.c \
       $(MANAGER_DIR)/manager.c

# Object files
OBJS = $(OBJ_DIR)/main.o \
       $(OBJ_DIR)/manager.o

# Output executable
TARGET = lrsh

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to build object files
$(OBJ_DIR)/main.o: $(LRSH_DIR)/main.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/manager.o: $(MANAGER_DIR)/manager.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets (targets that are not files)
.PHONY: all clean
