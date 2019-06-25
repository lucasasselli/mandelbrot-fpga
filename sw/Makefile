CC=gcc
CFLAGS=-std=c99 -O3
LDFLAGS=-lglut -lGLU -lGL -lm -Ilibs

BIN_DIR=bin

$(BIN_DIR)/mandelbrot-test : mandelbrot-test.c mandelbrot.h palette.h
	$(CC) $(CFLAGS) mandelbrot-test.c -o $@ $(LDFLAGS)

.PHONY: all
all: mandelbrot

.PHONY: clean
init:
	mkdir $(BIN_DIR)

.PHONY: clean
clean:
	rm -rf $(BIN_DIR)
