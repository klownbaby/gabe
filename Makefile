# A shitty Makefile for building gary
# (c) Kevin Kleiman, 2024

SRC := src
LIB := lib
INCLUDE := include
BIN := bin
EMU := gary
LIBGARY := libgary

CC := gcc
CFLAGS := -I $(INCLUDE) -o $(BIN)/$(EMU) -O2 -Wall -Wextra
LFLAGS := -I $(INCLUDE) -O2 -Wall -Wextra

TARGETS := $(SRC)/*.c
LIBTARGETS := $(LIB)/*.c
OBJ := $(BIN)/*.o
LOBJ := $(BIN)/$(LIBGARY)/$(LIBGARY).o

.PHONY: all build clean run

all: clean build run

clean:
	rm -rf $(OBJ) $(LOBJ) $(LIB)/$(LIBGARY)

glib: 
	$(CC) -c $(LIBTARGETS) -o $(LOBJ) $(LFLAGS)
	ar -rc $(LIB)/$(LIBGARY).a $(LOBJ)

build: glib
	$(CC) $(TARGETS) $(CFLAGS) $(LIB)/$(LIBGARY).a -lgcc

run:
	./$(BIN)/$(EMU)
