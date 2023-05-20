#ifndef _HASHFUNCS_H
#define _HASHFUNCS_H

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

uint64_t   IntHash1 (void *key);
uint64_t   IntHash2 (void *key);
uint64_t   IntHash3 (void *key);
uint64_t FloatHash1 (void *key);
uint64_t FloatHash2 (void *key);
uint64_t   StrHash1 (void *key);
uint64_t   StrHash2 (void *key);
uint64_t   StrHash3 (void *key);
uint64_t Crc32Hash  (void *key);

int   int_cmp (void *key1, void *key2);
int float_cmp (void *key1, void *key2);
int   str_cmp (void *key1, void *key2);

#endif