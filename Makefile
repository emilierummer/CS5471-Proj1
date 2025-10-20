
CC := cc
CFLAGS := -O2 -I./Source
LDFLAGS :=

SRCDIR := Source
IPCHECK_SRC := $(SRCDIR)/IPCheck.c
RBFGEN_SRC := $(SRCDIR)/RBFGen.c
HEADERS := $(SRCDIR)/HashUtils.h
HASHUTILS_SRC := $(SRCDIR)/HashUtils.c
HASHUTILS_OBJ := HashUtils.o

all: IPCheck RBFGen


IPCheck: $(IPCHECK_SRC) $(HEADERS)
	$(CC) $(CFLAGS) -c $(HASHUTILS_SRC) -o $(HASHUTILS_OBJ)
	$(CC) $(CFLAGS) -o IPCheck $(IPCHECK_SRC) $(HASHUTILS_OBJ) -lcrypto $(LDFLAGS)

# RBFGen depends on OpenSSL for SHA256

RBFGen: $(RBFGEN_SRC) $(HEADERS)
	$(CC) $(CFLAGS) -c $(HASHUTILS_SRC) -o $(HASHUTILS_OBJ)
	$(CC) $(CFLAGS) -o RBFGen $(RBFGEN_SRC) $(HASHUTILS_OBJ) -lcrypto $(LDFLAGS)

clean:
	rm -f IPCheck RBFGen HashUtils.o
