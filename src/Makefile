CC = gcc
CFLAGS = -I$(IDIR)

IDIR = ../include
ODIR = obj
SRCS = $(wildcard *.c)
DEPS = $(wildcard $(IDIR)/*.h)
OBJS = $(patsubst %.c, $(ODIR)/%.o, $(SRCS))

TDIR = ../tests
TESTS = $(wildcard $(TDIR)/*.c)
TESTBINS = $(patsubst $(TDIR)/%.c, $(TDIR)/bin/%, $(TESTS))

BDIR = bin
BIN = $(BDIR)/main

OBJSNOMAIN = $(filter-out obj/main.o, $(OBJS))

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TDIR)/bin/%: $(TESTS)
	$(CC) $< $(OBJSNOMAIN) -o $@ $(CFLAGS) 

$(TDIR)/bin:
	mkdir $@

$(ODIR):
	mkdir $@

$(BDIR):
	mkdir $@

$(IDIR):
	mkdir $@

test: $(TDIR)/bin $(TESTBINS)
	for test in $(TESTBINS) ; do ./$$test ; done

.PHONY: clean

clean:
	$(RM) -r $(ODIR)/*.o $(BDIR)/*


