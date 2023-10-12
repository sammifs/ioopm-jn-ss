#include "logic.h"
#include "hash_table.h"
#include "utils.h"
#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>

// TODO: print whats wrong before returning false in all functions


typedef struct merch merch_t;

struct merch
{
  char *name;       // holds the key
  int price;   // holds the price
  char *desc;
  ioopm_list_t *locs; 
};


void init_hashtable(ioopm_hash_table_t *ht) {
    ioopm_hash_table_insert(ht, int_elem('A'), ptr_elem(add_merch));
    ioopm_hash_table_insert(ht, int_elem('L'), ptr_elem(list_merch));
    ioopm_hash_table_insert(ht, int_elem('R'), ptr_elem(remove_merch));
    ioopm_hash_table_insert(ht, int_elem('E'), ptr_elem(edit_merch));
    ioopm_hash_table_insert(ht, int_elem('S'), ptr_elem(show_stock));
    ioopm_hash_table_insert(ht, int_elem('Q'), ptr_elem(quit));
}

merch_t *merch_create(char *name) {
    merch_t *result = calloc(1, sizeof(merch_t));
    
    result->name = name;
    result->desc = ask_question_string("What is the description?    ");
    result->price = ask_question_int("What is the price?    ");
    // TODO: Look at eq function, maybe should stay NULL, maybe something else.
    result->locs = ioopm_linked_list_create(NULL);

    return result;
}

bool add_merch(ioopm_hash_table_t *ht) {
    elem_t name = ptr_elem(ask_question_string("What is the name?    "));
    
    bool success = false;
    ioopm_hash_table_lookup(ht, name, &success);
    if (!success) {
        merch_t *new = merch_create(name.ptr_value);
        ioopm_hash_table_insert(ht, name, ptr_elem(new));
        return true;
    }
    // If true we are not allowed to continue.
    else {
        return false;
    }
}

void list_merch(ioopm_hash_table_t *ht) {
    // TODO: 20 listings per page
    size_t size = ioopm_hash_table_size(ht);
    if (size != 0) {
        char **merch_names = ioopm_hash_table_keys_char(ht);
        qsort(merch_names, size, sizeof(char *), cmpstringp);
        for (int i=0; i < size; i++) {
            printf("%s\n", merch_names[i]);
        }
    }
}

bool remove_merch(ioopm_hash_table_t *ht) {
    // TODO: Stub
    return true;
}

bool edit_merch(ioopm_hash_table_t *ht) {
    // TODO: Stub
    return true;
}

bool show_stock(ioopm_hash_table_t *ht) {
    // TODO: Stub
    return true;
}

bool replenish_stock(ioopm_hash_table_t *ht) {
    // TODO: Stub
    return true;
}

bool quit(ioopm_hash_table_t *ht) {
    // TODO:Stub
    return false;
}