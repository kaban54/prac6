#include "hashfuncs.h"

uint64_t IntHash1 (void *key)
{
    return (*(unsigned int *) key) % 1000;
}

uint64_t IntHash2 (void *key)
{
    return *(unsigned int *) key;
}

uint64_t IntHash3 (void *key)
{
    double f = (double)(*((int *) key)) * 0.54321;
    f = f - int(f);

    return (unsigned int)(f * 1001);
}


uint64_t FloatHash1 (void *key)
{
    return (int)(*(float *) key);
}

uint64_t FloatHash2 (void *key)
{
    return *(unsigned int *) key;
}


uint64_t StrHash1 (void *key)
{
    return strlen ((const char *) key);
}

uint64_t StrHash2 (void *key)
{
    const unsigned char *str = (const unsigned char *) key;
    uint64_t hash = 0;

    while (*str != '\0') hash += *(str++);

    return hash;
}

uint64_t StrHash3 (void *key)
{
    const unsigned char *str = (const unsigned char *) key;
    uint64_t hash = 0;

    while (*str != '\0') hash = hash * 257 + *(str++);

    return hash;
}

uint64_t Crc32Hash (void *key)
{
    const char *str = (const char *) key;
    uint32_t ret = 0xFFFFFFFF;

    while (*str != '\0')
    {
        ret ^= *(str++);

        for (int i = 0; i < 8; i++)
        {
            ret = (ret & 1) ? (ret >> 1) ^ 0xEDB88320 : ret >> 1;
        }
    }
    return ret;
}


int int_cmp (void *key1, void *key2)
{
    return *(int *) key1 - *(int *) key2;
}

int float_cmp (void *key1, void *key2)
{
    if (fabs (*(int *) key1 - *(int *) key2) < 0.0001f) return 0;
    else return 1;
}

int str_cmp (void *key1, void *key2)
{
    return strcmp ((const char *) key1, (const char *) key2);
}
