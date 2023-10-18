#include <stdlib.h>
#include "hash_table.h"

bool name_exists(ioopm_hash_table_t *ht, elem_t name);

merch_t *merch_create(ioopm_hash_table_t *ht, elem_t name, char *desc, int price);

void merch_destroy(merch_t *merch);

bool list_merch(ioopm_hash_table_t *ht, int cmpr, size_t size, int *index);

bool change_name(ioopm_hash_table_t *ht, char *name, elem_t *item);

void change_desc(ioopm_hash_table_t *ht, char *desc, elem_t *item);

void change_price(ioopm_hash_table_t *ht, int price, elem_t *item);

void delete_merch(merch_t *merch);

void edit_merch(ioopm_hash_table_t *ht);

void show_stock(ioopm_hash_table_t *ht, elem_t item);

void replenish_stock(ioopm_hash_table_t *ht, elem_t *item, char *shelf, int amount);

void create_cart();

void remove_cart();

void add_to_cart();

void remove_from_cart();

void calculate_cart();

void checkout();

void undo();
