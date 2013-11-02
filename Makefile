###### -*- mode: makefile -*-

BINs := yealink-cfgcrack yealink-keycrack yealink-keyderiv
ENCs := $(patsubst %.cfg,%.enc,$(wildcard test/*.cfg))
CFLAGS := -std=gnu99 -O3 -Wall

.PHONY: all clean

all: $(BINs) $(ENCs)

clean:
	rm -f $(BINs)

yealink-cfgcrack: yealink-cfgcrack.c Makefile
	gcc $(CFLAGS) -lssl -lcrypto -o $@ $<

%: %.c Makefile
	gcc $(CFLAGS) -o $@ $<

test/test-keydiff.conf: Makefile
	printf '%s\n' '2000000' > $@

test/test-keytime.conf: test/test-keydiff.conf Makefile
	printf '%s-%s\n' $$(date -u +%s) $$(cat test/test-keydiff.conf) | bc > $@

test/test-key.conf: test/test-keytime.conf yealink-keyderiv Makefile
	./yealink-keyderiv $(shell cat test/test-keytime.conf) > $@

test/%.enc: test/%.cfg test/test-key.conf Makefile
	./test/enc.sh $(shell cat test/test-key.conf) < $< > $@
