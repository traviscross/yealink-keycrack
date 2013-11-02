###### -*- mode: makefile -*-

BIN := yealink-keycrack

.PHONY: all clean

all: $(BIN)

clean:
	rm -f $(BIN)

yealink-keycrack: $(BIN).c Makefile
	gcc -O3 -o $@ $<
