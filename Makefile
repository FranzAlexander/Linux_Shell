# Define the build directory
BIN_DIR := bin
BUILD_DIR := $(BIN_DIR)/build
OBJ_DIR := $(BIN_DIR)/obj

# Define the source file directories.
SRC_DIR := src/*

# Define the source files.
SRCS := $(wildcard $(SRC_DIR)/*.c)

OBJS := $(SRCS:%.c=%.o)
DEPS := $(OBJS:%.o=%.d)

TARGET = azShell

CC = gcc

CFLAGS = -g3 -Wall -Wextra -Werror -Wshadow -Wdouble-promotion -Wformat=2 -Wformat-truncation -Wundef -fno-common \
	 -Wpedantic -Wconversion -Wcast-align -Wunused -Wpointer-arith -Wcast-qual \
	 -Wmissing-prototypes -Wno-missing-braces -I. -I$(SRC_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(TARGET): $(OBJS)
	@echo -e "\t" $(CC) $(CFLAGS) $(OBJS) $(TARGET) -o $@
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: make_dirs
	make_dirs: $(BUILD_DIR) $(OBJ_DIR)

$(BUILD_DIR):
	$(shell mkdir -p $@)

$(OBJ_DIR):
	$(shell mkdir -p $@)

-include $(DEPS)
