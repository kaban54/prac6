#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const size_t LIST_BASE_CAP = 1;


struct HashTableElem
{
    void *key;
    void *value;
};

struct HashTableList 
{
    size_t size;
    size_t capacity;
    
    HashTableElem *data;
};

struct HashTable
{
    uint64_t (*hash_func)(void *key);
    int (*cmp_func)(void *key1, void *key2);
    HashTableList *data;
    uint64_t size;
};


void HashTableCtor (HashTable *htable, uint64_t (*hash_func)(void *elem), int (*cmp_func)(void *key1, void *key2), uint64_t size);

void hashtable_list_ctor (HashTableList *lst, size_t capacity);

void HashTableDtor (HashTable *htable);

void hashtable_list_dtor (HashTableList *lst);

void HashTableInsert (HashTable *htable, void *key, void *value);

void hashtable_list_insert (HashTableList *lst, void *key, void *value, int (*cmp_func)(void *key1, void *key2));

void hashtable_list_resize (HashTableList *lst, size_t new_cap);

void *HashTableFind (HashTable *htable, void *key);

void *hashtable_list_find (HashTableList *lst, void *key, int (*cmp_func)(void *key1, void *key2));

void HashTableRemove (HashTable *htable, void *key);

void hashtable_list_remove (HashTableList *lst, void *key, int (*cmp_func)(void *key1, void *key2));

//inline HashTableElem *hashtable_list_find_asm (HashTableElem *elem, void *value);

#endif