CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lm

SRCDIR = src
BINDIR = bin

SOURCES = $(wildcard $(SRCDIR)/*.c)
BIN = $(BINDIR)/ss

.PHONY: all clean
 
all: $(BIN)

$(BINDIR)/ss: $(SOURCES)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -rf $(BINDIR) $(OBJDIR)
