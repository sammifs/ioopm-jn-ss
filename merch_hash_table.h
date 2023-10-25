#pragma once

#include "datastructures/hash_table.h"
#include "utils.h"
#include "shelf_list.h"

typedef hash_table_t merch_hash_table_t;

typedef struct merch merch_t;

shelf_list_t *merch_get_locs(merch_t *merch);

char *merch_get_name(merch_t *merch);

int merch_get_amount(merch_t *merch);

int merch_get_price(merch_t *merch);

void merch_increase_amount(merch_t *merch, int amount);

merch_hash_table_t *merch_hash_table_create();

void merch_hash_table_destroy(merch_hash_table_t *ht);

bool merch_hash_table_has_key(merch_hash_table_t *ht, char *name);

bool merch_hash_table_insert(merch_hash_table_t *ht, char* name, char* desc, int price);

char **merch_hash_table_keys(merch_hash_table_t *ht);

int merch_hash_table_size(merch_hash_table_t *ht);

merch_t *merch_hash_table_lookup(merch_hash_table_t *ht, char *name, bool *success);

bool merch_hash_table_remove(merch_hash_table_t *ht, char *name);