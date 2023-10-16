#include <stdlib.h>
#include "hash_table.h"

typedef struct merch merch_t;

bool name_exists(ioopm_hash_table_t *ht, elem_t name);

void merch_create(ioopm_hash_table_t *ht, elem_t name, char *desc, int price);

bool list_merch(ioopm_hash_table_t *ht, int cmpr, size_t size, int *index);

bool change_name(ioopm_hash_table_t *ht, char *name, elem_t *item, elem_t *ptr);

void change_desc(char *desc, elem_t *ptr);

void change_price(int price, elem_t *ptr);

void delete_merch(ioopm_hash_table_t *ht);

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
