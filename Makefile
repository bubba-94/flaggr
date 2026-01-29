# Compiler
CC := gcc

# Project settings
TARGET := flaggr

# Directories
OBJ_DIR := obj

# Source files
SRCS := main.c flaggr.c

LIBS := -lSDL2

# Object files mapped into obj/
OBJS := $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

# Flags
CFLAGS := -Wall -Wextra

# Default target
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LIBS)

# Rule to make sure obj folders exist
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: clean