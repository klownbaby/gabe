# (c) Kevin Kleiman, 2024
# A shitty Makefile for building GABE
#
SRC := src
LIB := lib
INCLUDE := include
BIN := bin
EMU := gabe
LIBGABE := libgabe

CC := gcc
CFLAGS := -g -I $(INCLUDE) -o $(BIN)/$(EMU) -O2 -Wall -Wextra -Wno-unused-variable
LFLAGS := -g -I $(LIB)/$(INCLUDE) -O2 -Wall -Wextra -Wno-unused-variable

TARGETS := $(SRC)/*.c
LIBTARGETS := $(LIB)/*.c
OBJ := $(BIN)/*.o
LOBJ := $(BIN)/$(LIBGABE)/*.o

# Change ROM here
TESTROM := ./roms/dmg-acid2.gb

.PHONY: all clean lib build run gdb

all: clean build run

clean:
	rm -rf $(OBJ) $(LOBJ) $(BIN)/$(LIBGABE).a

lib: 
	$(CC) -c $(LIBTARGETS) $(LFLAGS)
	mv *.o $(BIN)/$(LIBGABE)
	ar -rc $(BIN)/$(LIBGABE).a $(LOBJ)

build: lib
	$(CC) $(TARGETS) $(CFLAGS) $(BIN)/$(LIBGABE).a

gdb: clean build
	gdb $(BIN)/$(EMU)

run:
	echo "\n" && ./$(BIN)/$(EMU) $(TESTROM)
