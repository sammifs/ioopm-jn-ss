#pragma once

#include "merch_hash_table.h"

typedef struct store ioopm_store_t;

ioopm_store_t *ioopm_store_create();

void ioopm_store_destroy();

bool ioopm_store_has_merch(ioopm_store_t *store, char*name);

/// @brief Adds merch into the store->warehouse. Utilises merch_hash_table to do so. Returns false
/// if name already in use.
/// @param store 
/// @param name 
/// @param desc 
/// @param price 
/// @return  True if merch could be added, false means name is already occupied.
bool ioopm_store_add_merch(ioopm_store_t *store, char *name, char *desc, int price);

void ioopm_store_list_merch(ioopm_store_t *store);

bool ioopm_store_delete_merch(ioopm_store_t *store, char *name);

bool ioopm_store_edit_merch(ioopm_store_t *store, char* old_name,char *name, char *desc, int price);

void ioopm_store_show_stock();

int ioopm_store_replenish_stock(ioopm_store_t *store, char *name, char *shelf, int amount);

void ioopm_store_create_cart();

void ioopm_store_remove_cart();

void ioopm_store_add_to_cart();

void ioopm_store_calculate_cost_cart();

void ioopm_store_checkout_cart();