###### -*- mode: makefile -*-

BINs := yealink-keycrack yealink-keyderiv

.PHONY: all clean

all: $(BINs)

clean:
	rm -f $(BINs)

%: %.c Makefile
	gcc -O3 -o $@ $<
