#include "hashtable.h"
#include "hashfuncs.h"
#include <time.h>

const size_t HASHTABLE_SIZE = 99991;
const size_t NUM_OF_KEYS = 100000;

void HashTableSpeedTest (HashTable *htable, const char *filename, int *keys);
void GenerateIntKeys (int *intkeys, size_t num_of_keys);
void FillIntTables (HashTable *hashtables, size_t num_of_tables, int *keys, size_t num_of_keys);


int main ()
{
    HashTable htable = {};
    HashTableCtor (&htable, IntHash1, int_cmp, HASHTABLE_SIZE);

    int *intkeys = (int *) calloc (NUM_OF_KEYS, sizeof (int));

    GenerateIntKeys (intkeys, NUM_OF_KEYS);
    FillIntTables (&htable, 1, intkeys, NUM_OF_KEYS);

    HashTableSpeedTest (&htable, "output.txt", intkeys);

    HashTableDtor (&htable);
    free (intkeys);

    return 0;
}


void HashTableSpeedTest (HashTable *htable, const char *filename, int *keys)
{
    FILE *file = fopen (filename, "w");

    char *ops = (char *) calloc (1000000, sizeof (char));
    srand (time (NULL));
    
    for (int num_of_ops = 10000; num_of_ops <= 1000000; num_of_ops += 10000)
    {
        for (int i = 0; i < num_of_ops; i++) ops [i] = rand () % 3;

        clock_t start = clock ();

        for (int i = 0; i < num_of_ops; i++)
        {
            if      (ops [i] == 0) HashTableInsert (htable, (void *)(keys + i % NUM_OF_KEYS), (void *)(keys + i % NUM_OF_KEYS));
            else if (ops [i] == 1) HashTableRemove (htable, (void *)(keys + i % NUM_OF_KEYS));
            else if (ops [i] == 2) HashTableFind   (htable, (void *)(keys + i % NUM_OF_KEYS));
        }

        clock_t end = clock ();
 
        fprintf (file,   "%d %lf\n", num_of_ops, (double)(end - start) / CLOCKS_PER_SEC);
        fprintf (stdout, "%d %lf\n", num_of_ops, (double)(end - start) / CLOCKS_PER_SEC);
    }

    fclose (file);
}


void GenerateIntKeys (int *intkeys, size_t num_of_keys)
{
    for (int i = 0; i < num_of_keys; i++) intkeys [i] = (rand () << 15) + rand ();
}

void FillIntTables (HashTable *hashtables, size_t num_of_tables, int *keys, size_t num_of_keys)
{
    for (size_t tablenum = 0; tablenum < num_of_tables; tablenum++)
    {
        for (size_t i = 0; i < num_of_keys; i++) HashTableInsert (hashtables + tablenum, (void *)(keys + i), (void *)(keys + i));
    }
}