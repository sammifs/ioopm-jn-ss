#include <stdbool.h>
#include "hash_table.h"

void init_hashtable(ioopm_hash_table_t *ht);

bool add_merch(ioopm_hash_table_t *ht);

bool list_merch(ioopm_hash_table_t *ht);

bool remove_merch(ioopm_hash_table_t *ht);

bool edit_merch(ioopm_hash_table_t *ht);

bool show_stock(ioopm_hash_table_t *ht);

bool replenish_stock(ioopm_hash_table_t *ht);

bool quit(ioopm_hash_table_t *ht);