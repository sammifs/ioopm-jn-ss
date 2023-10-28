#pragma once

#include "datastructures/hash_table.h"
#include "utils.h"

typedef hash_table_t cart_hash_table_t;

typedef struct cart cart_t;
typedef struct order order_t;

cart_hash_table_t *cart_hash_table_create();

void cart_hash_table_destroy(cart_hash_table_t *ht);

void cart_hash_table_insert(cart_hash_table_t *ht, int cart_index);

cart_t *cart_hash_table_lookup(cart_hash_table_t *ht, int cart_index, bool *success);

bool cart_hash_table_remove(cart_hash_table_t *ht, int cart_index);

bool cart_hash_table_append_order(cart_hash_table_t *ht, int cart_index, char *merch_name, int amount, int price);

int cart_hash_table_calculate_cost(cart_hash_table_t *ht, int cart_index, bool *success);

void cart_list_checkout();

int cart_hash_table_order_amount_for_merch(cart_hash_table_t *ht, char *merch_name);

int single_cart_order_amount_of_merch(cart_t *cart, char *merch_name);

void remove_amount_of_items(cart_t *cart, char *merch_name, int amount);

void carts_hash_table_remove_orders(cart_hash_table_t *ht, char *name);

order_t *cart_get_first_order(cart_t *cart);

order_t *cart_get_next_order(order_t *order);

int order_get_amount(order_t *order);

char *order_get_merch(order_t *order);
