CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lm

SRCDIR = src
OBJDIR = obj
BINDIR = bin

EXECUTABLE = steganography

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(OBJDIR)/main.o

.PHONY: all clean

all: $(BINDIR)/$(EXECUTABLE)

$(BINDIR)/$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJDIR)/main.o: $(SOURCES)
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf $(BINDIR) $(OBJDIR)