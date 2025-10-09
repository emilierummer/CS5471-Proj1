CC := g++
CFLAGS := -std=c++17 -O2 -I./Source

SRCDIR := Source
IPCHECK_SRC := $(SRCDIR)/IPCheck.cpp
RBFGEN_SRC := $(SRCDIR)/RBFGen.cpp

all: ipcheck rbfgen

ipcheck: $(IPCHECK_SRC)
	$(CC) $(CFLAGS) -o ipcheck $(IPCHECK_SRC)

rbfgen: $(RBFGEN_SRC)
	$(CC) $(CFLAGS) -o rbfgen $(RBFGEN_SRC)

.PHONY: run-ipcheck run-rbfgen clean

run-ipcheck: ipcheck
	./ipcheck

run-rbfgen: rbfgen
	./rbfgen

clean:
	rm -f ipcheck rbfgen
