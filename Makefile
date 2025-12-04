# Compiler
CC := gcc

# Project settings
TARGET := flaggr

# Directories
SRC_DIR := src
INC_DIR := include
OBJ_DIR := obj

# Source files
SRCS := main.c $(wildcard $(SRC_DIR)/*.c)

# Object files mapped into obj/
OBJS := $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

# Flags
CFLAGS := -Wall -Wextra -I$(INC_DIR)
LIBS := `sdl2-config --cflags --libs` -lSDL2_ttf -lSDL2_image

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