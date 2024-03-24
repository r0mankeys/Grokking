#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header_files/hash_table.h"

#define CAPACITY 5000 // Size of the hash table


unsigned long hash_function(char *str)
{
    unsigned long i = 0;

    for (int j = 0; str[j] != '\0'; j++)
    {
        i += str[j]; // Add the ASCII value of each character in the string
    }

    return i % CAPACITY; // So 'i' will always be less than CAPACITY
}

table_item *create_table_item(char *key, char *value)
{
    // 1. Allocate memory for the table_item struct and it's fields
    table_item *item = (table_item *)malloc(sizeof(table_item)); // Allocate memory for the table_item struct
    item->key = (char *)malloc(strlen(key) + 1); // +1 for the null terminator character
    item->value = (char *)malloc(strlen(value) + 1); // +1 for the null terminator character
    // 2. Copy the key and value strings into the new table_item
    strcpy(item->key, key);
    strcpy(item->value, value);
    // 3. Return the new table_item
    return item;
}

hash_table *create_hash_table(size_t size)
{
    // 1. Allocate memory for the hash_table struct and it's fields
    hash_table *table = (hash_table *)malloc(sizeof(hash_table)); // Allocate memory for the hash_table struct
    table->items = (table_item **)calloc(size, sizeof(table_item *)); // Allocate memory for the items array and intialise all pointers to NULL
    table->size = size;
    table->count = 0;
    // 2. Return the new hash_table
    return table;
}

void print_table(hash_table* table)
{
    printf("\nHash Table\n-------------------\n");

    for (int i = 0; i < table->size; i++)
    {
        if (table->items[i])
        {
            printf("Index: %d, Key: %s, Value: %s\n", i, table->items[i]->key, table->items[i]->value);
        }
    }

    printf("-------------------\n\n");
}

void hash_table_insert(hash_table *table, char *key, char* value)
{
    // 1. Create the new table_item
    table_item *item = create_table_item(key, value);
    // 2. Compute the index with the hash funciton
    unsigned long index = hash_function(key);
    // 3. Check if that index is occupied
    if (table->items[index] == NULL)
    {
        if (table->count == table->size)
        {
            // Hash Table is full 
            printf("Insert Error: Hash Table is full\n");
            free_item(item);
            return;
        }
        // 3.1 If it is not occupied set that index to the new table_item
        table->items[index] = item;
        table->count++;
        return;
    } else {
        // 3.2 If it is occupied, print an error message 
        printf("Insert Error: Index %lu is occupied\n", index);
        return;
    }
}

void hash_table_delete(hash_table *table, char *key)
{
    // 1. Compute the index with the hash function
    unsigned long index = hash_function(key);
    // 2. Check if the index is occupied
    if (table->items[index] != NULL)
    {
        // 2.1 If it is occupied, free the table_item and set the index to NULL
        free_item(table->items[index]);
        table->items[index] = NULL;
        table->count--;
        return;
    } else {
        // 2.2 If it is not occupied, print an error message
        printf("Delete Error: Index %lu is not occupied\n", index);
        return;
    }
}

void hash_table_search(hash_table *table, char* key)
{
    unsigned long index = hash_function(key);
    if (table->items[index] == NULL)
    {
        printf("Search Error: Index %lu is not occupied\n", index);
        return;
    }
    printf("Value: %s\n\n", table->items[index]->value);
    return;
}

void free_item(table_item *item)
{
    free(item->key);
    free(item->value);
    free(item);
}

void free_table(hash_table *table) 
{
    for (size_t i = 0; i < table->size; ++i)
    {
        table_item *item = table->items[i];
        if (item != NULL)
        {
            free_item(item);
        }
    }
    free(table->items);
    free(table);
}
