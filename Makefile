# Define the directories.
PROJDIR := $(realpath $(CURDIR))
BINDIR := $(PROJDIR)/bin
OBJDIR := $(BINDIR)/obj
SOURCEDIR := $(PROJDIR)/src

# Get all source directories.
SRCDIRS := $(sort $(dir $(wildcard $(SOURCEDIR)/*/)))

# Define the include paths.
INCLUDES := $(foreach dir, $(SRCDIRS), $(addprefix -I, $(dir)))

# Get all source files.
SRCS := $(foreach dir, $(SRCDIRS), $(wildcard $(dir)*.c))

# Compile object files.
OBJS := $(SRCS:%.c=%.o)
DEPS := $(OBJS:%.o=%.d)

# Name of executable.
TARGET = azshell

# Compiler to use.
CC = gcc

# Compiler flags.
CFLAGS = -g3 -Wall -Wextra -Werror -Wshadow -Wdouble-promotion -Wformat=2 -Wformat-truncation \
	 -Wundef -fno-common -Wpedantic -Wconversion -Wcast-align -Wunused -Wpointer-arith \
	 -Wcast-qual -Wmissing-prototypes -Wno-missing-braces

PSEP = $(strip /)

.PHONY: all clean directories

all: directories $(TARGET)

%.o: %.c
	@echo Building Object Files
	$(CC) -c $(CFLAGS) $(INCLUDES) -o $@ $< 

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

-include $(DEPS)

directories:
	mkdir -p $(BINDIR) 2>/dev/null
	mkdir -p $(OBJDIR) 2>/dev/null

clean:
	rm -rf $(BINDIR) 2>/dev/null
	@echo Done cleaning!
