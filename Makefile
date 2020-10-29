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
CC = gcc-9

# Compiler flags.
CFLAGS = -Wall -Wextra -Wshadow -Wdouble-promotion -Wformat=2 -Wformat-overflow -Wformat-truncation \
	 -Wundef -fno-common -Wpedantic -Wconversion -Wcast-align -Wpointer-arith \
	 -Wcast-qual -Wmissing-prototypes -Wno-missing-braces -g3 -ggdb3 -fno-eliminate-unused-debug-symbols\
	 -fvar-tracking -fno-diagnostics-show-line-numbers -Warray-bounds -Wattribute-alias \
	 -Wmissing-attributes -Wstringop-truncation -O2

PSEP = $(strip /)

.PHONY: all clean directories git

all: directories $(TARGET)

%.o: %.c
	@echo Building Object Files $$@
	$(CC) -c $(CFLAGS) $(INCLUDES) -o $@ $< 

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

-include $(DEPS)

git:
	git add .
	git commit -m "$m"
	git push origin "$b"

directories:
	mkdir -p $(BINDIR) 2>/dev/null
	mkdir -p $(OBJDIR) 2>/dev/null

clean:
	rm -rf $(BINDIR) 2>/dev/null
	rm -f $(TARGET) 2>/dev/null
	@echo Done cleaning!
