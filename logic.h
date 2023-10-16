#include <stdvoid.h>
#include "hash_table.h"

typedef struct merch merch_t;
typedef struct shelf shelf_t;

void add_merch(ioopm_hash_table_t *ht);

void list_merch(ioopm_hash_table_t *ht);

void delete_merch(ioopm_hash_table_t *ht);

void edit_merch(ioopm_hash_table_t *ht);

void show_stock(ioopm_hash_table_t *ht);

void replenish_stock(ioopm_hash_table_t *ht);

void create_cart();

void remove_cart();

void add_to_cart();

void remove_from_cart();

void calculate_cart();

void checkout();

void undo();

void quit(bool *loop);