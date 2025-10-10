
CC := cc
CFLAGS := -O2 -I./Source
LDFLAGS :=

SRCDIR := Source
IPCHECK_SRC := $(SRCDIR)/IPCheck.c
RBFGEN_SRC := $(SRCDIR)/RBFGen.c

all: ipcheck rbfgen

ipcheck: $(IPCHECK_SRC)
	$(CC) $(CFLAGS) -o ipcheck $(IPCHECK_SRC) $(LDFLAGS)

# RBFGen depends on OpenSSL for SHA256
rbfgen: $(RBFGEN_SRC)
	$(CC) $(CFLAGS) -o rbfgen $(RBFGEN_SRC) -lcrypto $(LDFLAGS)

.PHONY: run-ipcheck run-rbfgen clean

run-ipcheck: ipcheck
	./ipcheck

run-rbfgen: rbfgen
	./rbfgen

clean:
	rm -f ipcheck rbfgen
