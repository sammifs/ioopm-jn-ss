#pragma once

#include "datastructures/hash_table.h"
#include "utils.h"

typedef hash_table_t cart_hash_table_t;

typedef struct cart cart_t;

cart_hash_table_t *cart_hash_table_create();

void cart_hash_table_destroy(cart_hash_table_t *ht);

void cart_hash_table_insert(cart_hash_table_t *ht, int cart_index);

cart_t *cart_hash_table_lookup(cart_hash_table_t *ht, int cart_index, bool *success);

bool cart_hash_table_remove(cart_hash_table_t *ht, int cart_index);

bool cart_hash_table_append_order(cart_hash_table_t *ht, int cart_index, char *merch_name, int amount, int price);

int cart_hash_table_calculate_cost(cart_hash_table_t *ht, int cart_index, bool *success);

void cart_list_checkout();