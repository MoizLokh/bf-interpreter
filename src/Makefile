CC = gcc
CFLAGS = -I$(IDIR)

IDIR = ../include
ODIR = obj
SRCS = $(wildcard *.c)
DEPS = $(wildcard $(IDIR)/*.h)
OBJS = $(patsubst %.c, $(ODIR)/%.o, $(SRCS))

BDIR = bin
BIN = $(BDIR)/main

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	$(RM) -r $(ODIR)/*.o $(BDIR)/*


