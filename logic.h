#include <stdlib.h>
#include "hash_table.h"

char *get_desc(ioopm_hash_table_t *ht, elem_t item, bool *success);

int get_price(ioopm_hash_table_t *ht, elem_t item, bool *success);

void delete_all_items(ioopm_hash_table_t *ht);

bool name_exists(ioopm_hash_table_t *ht, elem_t name);

// TODO: Gör om till void, vi behöver inte ett return value längre
elem_t merch_create(ioopm_hash_table_t *ht, elem_t name, char *desc, int price);

void merch_destroy(merch_t *merch);

bool list_merch(ioopm_hash_table_t *ht, int cmpr, size_t size, int *index);

bool change_name(ioopm_hash_table_t *ht, char *name, elem_t *item);

void change_desc(ioopm_hash_table_t *ht, char *desc, elem_t *item);

void change_price(ioopm_hash_table_t *ht, int price, elem_t *item);

bool delete_merch(ioopm_hash_table_t *ht, elem_t item);

void edit_merch(ioopm_hash_table_t *ht);

bool show_stock(ioopm_hash_table_t *ht, elem_t item);

bool replenish_stock(ioopm_hash_table_t *ht, elem_t *item, char *shelf, int amount);

void create_cart();

void remove_cart();

void add_to_cart();

void remove_from_cart();

void calculate_cart();

void checkout();

void undo();
