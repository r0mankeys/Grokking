#ifndef HASH_TABLE_H
#define HASH_TABLE_H

typedef struct table_item {
    char *key;
    char *value;
} table_item;

typedef struct hash_table {
    table_item **items;
    int size;
    int count;
} hash_table;

unsigned long hash_function(char *str);
table_item *create_table_item(char *key, char *value);
hash_table *create_hash_table(int size);
void print_table(hash_table *table);
void hash_table_insert(hash_table *table, char *key, char *value);
void hash_table_delete(hash_table *table, char *key);
void hash_table_search(hash_table *table, char *key);
void free_item(table_item *item);
void free_table(hash_table *table);

#endif
