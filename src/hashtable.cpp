#include "hashtable.h"

void HashTableCtor (HashTable *htable, uint64_t (*hash_func)(void *key), int (*cmp_func)(void *key1, void *key2), uint64_t size)
{
    assert (htable    != nullptr);
    assert (hash_func != nullptr);
    assert ( cmp_func != nullptr);

    htable -> hash_func = hash_func;
    htable ->  cmp_func =  cmp_func;
    htable -> size = size;
    htable -> data = (HashTableList *) calloc (size, sizeof (htable -> data[0]));
    assert (htable -> data != nullptr);

    for (size_t index = 0; index < htable -> size; index++) hashtable_list_ctor (htable -> data + index, LIST_BASE_CAP);
}

void hashtable_list_ctor (HashTableList *lst, size_t capacity)
{
    lst -> data = (HashTableElem *) calloc (capacity, sizeof (lst -> data [0]));
    assert (lst -> data != nullptr);

    lst -> capacity = capacity;
    lst -> size     = 0;
}

void HashTableDtor (HashTable *htable)
{
    assert (htable != nullptr);

    for (size_t index = 0; index < htable -> size; index++) hashtable_list_dtor (htable -> data + index);
    free (htable -> data);

    htable -> size = 0;
    htable -> hash_func = nullptr;
    htable ->  cmp_func = nullptr;
}

void hashtable_list_dtor (HashTableList *lst)
{
    free (lst -> data);
    lst -> size     = 0;
    lst -> capacity = 0;
}

void HashTableInsert (HashTable *htable, void *key, void *value)
{
    uint64_t hash = htable -> hash_func (key) % htable -> size;

    hashtable_list_insert (htable -> data + hash, key, value, htable -> cmp_func);
}

void hashtable_list_insert (HashTableList *lst, void *key, void *value, int (*cmp_func)(void *key1, void *key2))
{
    if (hashtable_list_find (lst, key, cmp_func) != nullptr) return;

    if (lst -> size >= lst -> capacity) hashtable_list_resize (lst, lst -> capacity == 0 ? LIST_BASE_CAP : lst -> capacity * 2);

    lst -> data [lst -> size].key = key;
    lst -> data [lst -> size].value = value;
    lst -> size ++;
}

void hashtable_list_resize (HashTableList *lst, size_t new_cap)
{
    lst -> data = (HashTableElem *) realloc (lst -> data, new_cap * sizeof (lst -> data [0]));
    lst -> capacity = new_cap;
}

void *HashTableFind (HashTable *htable, void *key)
{
    uint64_t hash = htable -> hash_func (key) % htable -> size;

    return hashtable_list_find (htable -> data + hash, key, htable -> cmp_func);
}

void *hashtable_list_find (HashTableList *lst, void *key, int (*cmp_func)(void *key1, void *key2))
{
    for (size_t index = 0; index < lst -> size; index++)
    {
        if (cmp_func (key, lst -> data [index].key) == 0) return lst -> data [index].value;
    }
    return nullptr;
}

void HashTableRemove (HashTable *htable, void *value)
{
    uint64_t hash = htable -> hash_func (value) % htable -> size;

    hashtable_list_remove (htable -> data + hash, value, htable -> cmp_func);
}

void hashtable_list_remove (HashTableList *lst, void *key, int (*cmp_func)(void *key1, void *key2))
{
    for (size_t index = 0; index < lst -> size; index++)
    {
        if (cmp_func (key, lst -> data [index].key) == 0)
        {
            lst -> data [index] = lst -> data [--(lst -> size)];
            return;
        }
    }
}
