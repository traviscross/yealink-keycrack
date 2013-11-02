###### -*- mode: makefile -*-

BINs := yealink-cfgcrack yealink-keycrack yealink-keyderiv

.PHONY: all clean

all: $(BINs)

clean:
	rm -f $(BINs)

yealink-cfgcrack: yealink-cfgcrack.c Makefile
	gcc -O3 -lssl -lcrypto -o $@ $<

%: %.c Makefile
	gcc -O3 -o $@ $<
