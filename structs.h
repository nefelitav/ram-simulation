#ifndef _STRUCTS_H_
#define _STRUCTS_H_

#include <semaphore.h>

#define FILENAME_LENGTH 200
#define PAGE_NAME 6

typedef enum { 
    false, 
    true 
} bool; 

typedef struct hash_item {
    char* key; // page number
    int frame;
    char action; // R or W
} hash_item;

typedef struct hash_list {
    hash_item item; // item info
    struct hash_list* next;    // next item in list
} hash_list;

typedef struct hash_table {
    int size; // how many hash_lists
    hash_list* table;   // array of linked lists
} hash_table;

hash_table* create_table(int size);
void delete_table(hash_table* table);

void insert_table(hash_table* table, const char* key, int frame, char action); // add an item
bool remove_table(hash_table* table, const char* key); // remove an item // return true if we need to write to disk
bool exists_table(hash_table* table, const char* key); // check if exists
hash_item* get_table(hash_table* table, const char* key); // get value
void update_to_w_table(hash_table* table, const char* key); // Update hash_item > key to W so that when we remove it we know that it should be written to disk


typedef struct shared_memory {
    char filename_0[FILENAME_LENGTH];
    unsigned int writes_to_disk_0;
    unsigned int reads_0;
    unsigned int writes_0;
    unsigned int page_faults_0;

    char filename_1[FILENAME_LENGTH];
    unsigned int writes_to_disk_1;
    unsigned int reads_1;
    unsigned int writes_1;
    unsigned int page_faults_1;

    unsigned int frames;
    sem_t mutex_0;
    sem_t mutex_1;
} shared_memory;

#endif