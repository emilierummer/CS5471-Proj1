
CC := cc
CFLAGS := -O2 -I./Source
LDFLAGS :=

SRCDIR := Source
IPCHECK_SRC := $(SRCDIR)/IPCheck.c
RBFGEN_SRC := $(SRCDIR)/RBFGen.c
HEADERS := $(SRCDIR)/HashUtils.h
HASHUTILS_SRC := $(SRCDIR)/HashUtils.c
HASHUTILS_OBJ := HashUtils.o

all: ipcheck rbfgen


ipcheck: $(IPCHECK_SRC) $(HEADERS)
	$(CC) $(CFLAGS) -c $(HASHUTILS_SRC) -o $(HASHUTILS_OBJ)
	$(CC) $(CFLAGS) -o ipcheck $(IPCHECK_SRC) $(HASHUTILS_OBJ) -lcrypto $(LDFLAGS)

# RBFGen depends on OpenSSL for SHA256

rbfgen: $(RBFGEN_SRC) $(HEADERS)
	$(CC) $(CFLAGS) -c $(HASHUTILS_SRC) -o $(HASHUTILS_OBJ)
	$(CC) $(CFLAGS) -o rbfgen $(RBFGEN_SRC) $(HASHUTILS_OBJ) -lcrypto $(LDFLAGS)

.PHONY: run-ipcheck run-rbfgen clean

run-ipcheck: ipcheck
	./ipcheck

run-rbfgen: rbfgen
	./rbfgen

clean:
	rm -f ipcheck rbfgen HashUtils.o
