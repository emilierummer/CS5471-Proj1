#ifndef HASHUTILS_H
#define HASHUTILS_H

#include <stdio.h>

#define NUM_HASHES 8

int hashWithKey(int key, const char *ip, int m);
int getRbfRow(int col);

#endif
