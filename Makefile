# A shitty Makefile for building GABE
# (c) Kevin Kleiman, 2024

SRC := src
LIB := lib
INCLUDE := include
BIN := bin
EMU := gabe
LIBGABE := libgabe

CC := gcc
CFLAGS := -I $(INCLUDE) -o $(BIN)/$(EMU) -O2 -Wall -Wextra
LFLAGS := -I $(LIB)/$(INCLUDE) -O2 -Wall -Wextra

TARGETS := $(SRC)/*.c
LIBTARGETS := $(LIB)/*.c
OBJ := $(BIN)/*.o
LOBJ := $(BIN)/$(LIBGABE)/*.o

.PHONY: all clean lib build run

all: clean build run

clean:
	rm -rf $(OBJ) $(LOBJ) $(LIB)/$(LIBGABE).a

lib: 
	$(CC) -c $(LIBTARGETS) $(LFLAGS)
	mv *.o $(BIN)/$(LIBGABE)
	ar -rc $(LIB)/$(LIBGABE).a $(LOBJ)

build: lib
	$(CC) $(TARGETS) $(CFLAGS) $(LIB)/$(LIBGABE).a

run:
	./$(BIN)/$(EMU)
