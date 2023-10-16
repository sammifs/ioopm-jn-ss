#include <stdlib.h>
#include "hash_table.h"

void ioopm_add_merch(ioopm_hash_table_t *ht);

void ioopm_list_merch(ioopm_hash_table_t *ht);

void ioopm_delete_merch(ioopm_hash_table_t *ht);

void ioopm_edit_merch(ioopm_hash_table_t *ht);

void ioopm_show_stock(ioopm_hash_table_t *ht);

void ioopm_replenish_stock(ioopm_hash_table_t *ht);

void ioopm_create_cart();

void ioopm_remove_cart();

void ioopm_add_to_cart();

void ioopm_remove_from_cart();

void ioopm_calculate_cart();

void ioopm_checkout();

void ioopm_undo();

void ioopm_quit(bool *loop);