#include "hashtable.h"
#include "hashfuncs.h"
#include <time.h>

const char *const  INPUT_FILE_NAME = "input.txt";
const char *const OUTPUT_FILE_NAME = "output.csv";

const size_t HASHTABLE_SIZE = 1000;
const size_t NUM_OF_KEYS = 100000;
const size_t MAX_STR_LEN = 32;

void GenerateIntKeys   (int     *intkeys, size_t num_of_keys);
void GenerateFloatKeys (float *floatkeys, size_t num_of_keys);
void GenerateStrKeys   (char    *strkeys, size_t num_of_keys, size_t max_str_len);

void FillIntTables   (HashTable *hashtables, size_t num_of_tables, int   *keys, size_t num_of_keys);
void FillFloatTables (HashTable *hashtables, size_t num_of_tables, float *keys, size_t num_of_keys);
void FillStrTables   (HashTable *hashtables, size_t num_of_tables, char  *keys, size_t num_of_keys, size_t max_str_len);

void TestHashFuncs (HashTable *hashtables, const char *output_file_name, int num_of_funcs);
void PrintListsLen (HashTable *htable, FILE *out_file);

int main ()
{
    srand (time (NULL));

    HashTable   inthashtables [3] = {};
    HashTable floathashtables [2] = {};
    HashTable   strhashtables [4] = {};
    
    HashTableCtor (  inthashtables + 0,   IntHash1,   int_cmp, HASHTABLE_SIZE);
    HashTableCtor (  inthashtables + 1,   IntHash2,   int_cmp, HASHTABLE_SIZE);
    HashTableCtor (  inthashtables + 2,   IntHash3,   int_cmp, HASHTABLE_SIZE);

    HashTableCtor (floathashtables + 0, FloatHash1, float_cmp, HASHTABLE_SIZE);
    HashTableCtor (floathashtables + 1, FloatHash2, float_cmp, HASHTABLE_SIZE);

    HashTableCtor (  strhashtables + 0,   StrHash1,   str_cmp, HASHTABLE_SIZE);
    HashTableCtor (  strhashtables + 1,   StrHash2,   str_cmp, HASHTABLE_SIZE);
    HashTableCtor (  strhashtables + 2,   StrHash3,   str_cmp, HASHTABLE_SIZE);
    HashTableCtor (  strhashtables + 3,  Crc32Hash,   str_cmp, HASHTABLE_SIZE);
    

    int     *intkeys = (int *)   calloc (NUM_OF_KEYS, sizeof (int));
    float *floatkeys = (float *) calloc (NUM_OF_KEYS, sizeof (int));
    char    *strkeys = (char *)  calloc (NUM_OF_KEYS, MAX_STR_LEN * sizeof (char));

    
    GenerateIntKeys   (  intkeys, NUM_OF_KEYS);
    GenerateFloatKeys (floatkeys, NUM_OF_KEYS);
    GenerateStrKeys   (  strkeys, NUM_OF_KEYS, MAX_STR_LEN);

    FillIntTables   (  inthashtables, 3,   intkeys, NUM_OF_KEYS);
    FillFloatTables (floathashtables, 2, floatkeys, NUM_OF_KEYS);
    FillStrTables   (  strhashtables, 4,   strkeys, NUM_OF_KEYS, MAX_STR_LEN);
    
    TestHashFuncs (  inthashtables,   "int.csv", 3);
    TestHashFuncs (floathashtables, "float.csv", 2);
    TestHashFuncs (  strhashtables,   "str.csv", 4);
    
    for (size_t index = 0; index < 3; index++) HashTableDtor (  inthashtables + index);
    for (size_t index = 0; index < 2; index++) HashTableDtor (floathashtables + index);
    for (size_t index = 0; index < 4; index++) HashTableDtor (  strhashtables + index);
    
    free (intkeys);
    free (floatkeys);
    free (strkeys);

    return 0;
}


void GenerateIntKeys (int *intkeys, size_t num_of_keys)
{
    for (int i = 0; i < num_of_keys; i++) intkeys [i] = (rand () << 15) + rand ();
}

void GenerateFloatKeys (float *floatkeys, size_t num_of_keys)
{
    for (int i = 0; i < num_of_keys; i++) floatkeys [i] = (float) rand () + ((float) rand ()) / RAND_MAX;
}

void GenerateStrKeys (char *strkeys, size_t num_of_keys, size_t max_str_len)
{
    for (int i = 0; i < num_of_keys; i++)
    {
        size_t len = rand () % (max_str_len - 1);
        for (int j = 0; j < len; j++) strkeys [i * max_str_len + j] = rand () % 256;
        strkeys [i * max_str_len + len] = '\0';
    }
}


void FillIntTables (HashTable *hashtables, size_t num_of_tables, int *keys, size_t num_of_keys)
{
    for (size_t tablenum = 0; tablenum < num_of_tables; tablenum++)
    {
        for (size_t i = 0; i < num_of_keys; i++) HashTableInsert (hashtables + tablenum, (void *)(keys + i), (void *)(keys + i));
    }
}

void FillFloatTables (HashTable *hashtables, size_t num_of_tables, float *keys, size_t num_of_keys)
{
    for (size_t tablenum = 0; tablenum < num_of_tables; tablenum++)
    {
        for (size_t i = 0; i < num_of_keys; i++) HashTableInsert (hashtables + tablenum, (void *)(keys + i), (void *)(keys + i));
    }
}

void FillStrTables (HashTable *hashtables, size_t num_of_tables, char *keys, size_t num_of_keys, size_t max_str_len)
{
    for (size_t tablenum = 0; tablenum < num_of_tables; tablenum++)
    {
        for (size_t i = 0; i < num_of_keys; i++) HashTableInsert (hashtables + tablenum, (void *)(keys + i * max_str_len), (void *)(keys + i * max_str_len));
    }
}


void TestHashFuncs (HashTable *hashtables, const char *output_file_name, int num_of_funcs)
{
    FILE *out_file = fopen (output_file_name, "w");
    assert (out_file != nullptr);

    for (size_t index = 0; index < num_of_funcs; index++)
    {
        PrintListsLen (hashtables + index, out_file);
    }

    fclose (out_file);
}

void PrintListsLen (HashTable *htable, FILE *out_file)
{
    for (size_t index = 0; index < htable -> size; index++)
    {
        fprintf (out_file, "%ld;", htable -> data [index].size);
    }
    fprintf (out_file, "\n");

    fflush (out_file);
}