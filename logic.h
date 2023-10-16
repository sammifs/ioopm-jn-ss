#include <stdbool.h>
#include "hash_table.h"

typedef struct merch merch_t;
typedef struct shelf shelf_t;

void init_hashtable(ioopm_hash_table_t *ht);

bool add_merch();

bool delete_merch();

bool edit_merch();

bool show_stock();

bool replenish_stock();

void list_merch(ioopm_hash_table_t *ht);

void create_cart();

void remove_cart();

void add_to_cart();

void remove_from_cart();

void calculate_cart();

void checkout();

void undo();

void quit();