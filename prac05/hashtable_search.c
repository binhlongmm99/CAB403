// Based on the Week 3 hashtable exercise

#include <inttypes.h> // for portable integer declarations
#include <stdbool.h>  // for bool type
#include <stdio.h>    // for printf()
#include <stdlib.h>   // for malloc(), free(), NULL
#include <string.h>   // for strcmp()
#include <pthread.h>

// An item inserted into a hash table.
// As hash collisions can occur, multiple items can exist in one bucket.
// Therefore, each bucket is a linked list of items that hashes to that bucket.
typedef struct item item_t;
struct item
{
    char key[4];
    int value;
    item_t *next;
};

void item_print(item_t *i)
{
    printf("key=%s value=%d", i->key, i->value);
}

// A hash table mapping a string to an integer.
typedef struct htab htab_t;
struct htab
{
    item_t **buckets;
    size_t size;
};

// Initialise a new hash table with n buckets.
// pre: true
// post: (return == false AND allocation of table failed)
//       OR (all buckets are null pointers)
bool htab_init(htab_t *h, size_t n)
{
    h->size = n;
    h->buckets = (item_t **)calloc(n, sizeof(item_t *));
    return h->buckets != 0;
}

// The Bernstein hash function.
// A very fast hash function that works well in practice.
size_t djb_hash(char *s)
{
    size_t hash = 5381;
    int c;
    while ((c = *s++) != '\0')
    {
        // hash = hash * 33 + c
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

// Calculate the offset for the bucket for key in hash table.
size_t htab_index(htab_t *h, char *key)
{
    return djb_hash(key) % h->size;
}

// Find pointer to head of list for key in hash table.
item_t *htab_bucket(htab_t *h, char *key)
{
    return h->buckets[htab_index(h, key)];
}

// Find an item for key in hash table.
// pre: true
// post: (return == NULL AND item not found)
//       OR (strcmp(return->key, key) == 0)
item_t *htab_find(htab_t *h, char *key)
{
    for (item_t *i = htab_bucket(h, key); i != NULL; i = i->next)
    {
        if (strcmp(i->key, key) == 0)
        { // found the key
            return i;
        }
    }
    return NULL;
}

// Add a key with value to the hash table.
// pre: htab_find(h, key) == NULL
// post: (return == false AND allocation of new item failed)
//       OR (htab_find(h, key) != NULL)
bool htab_add(htab_t *h, char *key, int value)
{
    // allocate new item
    item_t *newhead = (item_t *)malloc(sizeof(item_t));
    if (newhead == NULL)
    {
        return false;
    }
    strncpy(newhead->key, key, 4);
    newhead->value = value;

    // hash key and place item in appropriate bucket
    size_t bucket = htab_index(h, key);
    newhead->next = h->buckets[bucket];
    h->buckets[bucket] = newhead;
    return true;
}

// Print the hash table.
// pre: true
// post: hash table is printed to screen
void htab_print(htab_t *h)
{
    printf("hash table with %ld buckets\n", h->size);
    for (size_t i = 0; i < h->size; ++i)
    {
        printf("bucket %ld: ", i);
        if (h->buckets[i] == NULL)
        {
            printf("empty\n");
        }
        else
        {
            for (item_t *j = h->buckets[i]; j != NULL; j = j->next)
            {
                item_print(j);
                if (j->next != NULL)
                {
                    printf(" -> ");
                }
            }
            printf("\n");
        }
    }
}

// Delete an item with key from the hash table.
// pre: htab_find(h, key) != NULL
// post: htab_find(h, key) == NULL
void htab_delete(htab_t *h, char *key)
{
    item_t *head = htab_bucket(h, key);
    item_t *current = head;
    item_t *previous = NULL;
    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            if (previous == NULL)
            { // first item in list
                h->buckets[htab_index(h, key)] = current->next;
            }
            else
            {
                previous->next = current->next;
            }
            free(current);
            break;
        }
        previous = current;
        current = current->next;
    }
}

// Destroy an initialised hash table.
// pre: htab_init(h)
// post: all memory for hash table is released
void htab_destroy(htab_t *h)
{
    // free linked lists
    for (size_t i = 0; i < h->size; ++i)
    {
        item_t *bucket = h->buckets[i];
        while (bucket != NULL)
        {
            item_t *next = bucket->next;
            free(bucket);
            bucket = next;
        }
    }

    // free buckets array
    free(h->buckets);
    h->buckets = NULL;
    h->size = 0;
}

// Iterates through each bucket of hashtable 'h', printing out keys with value 'search'
// pre: htab_init(h)
// post: each key with value 'search' has been printed to stdout
void htab_search_value(htab_t *h, int search)
{
    for (size_t i = 0; i < h->size; ++i)
    {
        for (item_t *bucket = h->buckets[i]; bucket != NULL; bucket = bucket->next) {
            if (bucket->value == search) printf("%s ", bucket->key);
        }
    }
    printf("\n");
}

int main(int argc, char **argv)
{
    // create a hash table with 100 buckets
    htab_t h;
    if (!htab_init(&h, 100))
    {
        printf("failed to initialise hash table\n");
        return EXIT_FAILURE;
    }

    // add 10000 items to hash table.
    char key[4];
    for (int i = 0; i < 10000; i++) {
        // Generate a unique key for each item
        key[0] = (i % 26) + 'A';
        key[1] = ((i / 26) % 26) + 'A';
        key[2] = ((i / 676) % 26) + 'A';
        key[3] = '\0';
        // Generate a value (0-99) for each item
        htab_add(&h, key, rand() % 100);
    }
    
    // Get search value from command line (0 if none provided)
    int search = 0;
    if (argc >= 2) search = atoi(argv[1]);
    
    htab_search_value(&h, search);
    htab_destroy(&h);
}
