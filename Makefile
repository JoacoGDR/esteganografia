CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lm

SRCDIR = src
BINDIR = bin

SOURCES = $(wildcard $(SRCDIR)/*.c)
BIN = $(BINDIR)/main

.PHONY: all clean
 
all: $(BIN)

$(BINDIR)/main: $(SOURCES)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf $(BINDIR) $(OBJDIR)
