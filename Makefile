# Define the build directory
BUILD_DIR = ./build

# Define the source files.
SRCS := $(wildcard src/*/*.c)

OBJS = $(SRCS:.c=.o)

TARGET ?= azShell

CC = gcc

CFLAGS = -g3 -Wall -Wextra -Werror -Wshadow -Wdouble-promotion -Wformat=2 -Wformat-truncation -Wundef -fno-common \
	 -Wpedantic -Wconversion -Wcast-align -Wunused -Wpointer-arith -Wcast-qual \
	 -Wmissing-prototypes -Wno-missing-braces

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/$(TARGET): $(OBJS)
	$(CC) -o $@ $^
