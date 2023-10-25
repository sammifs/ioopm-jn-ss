#pragma once

#include "merch_hash_table.h"
#include "cart_hash_table.h"

typedef struct store ioopm_store_t;

/// @brief Creates an ioopm_store_t on the heap
/// @return Pointer to created ioopm_store_t
ioopm_store_t *ioopm_store_create();

/// @brief Destroys store and frees every value contained within, every char* that has been
/// input is included and will be destroyed. Does NOT take responsiblity for values that 
/// were not successfully input.
/// @param store 
void ioopm_store_destroy(ioopm_store_t *store);

/// @brief Checks if store->warehouse contains specified merch.
/// @param store ioopm_store_t to be operated upon
/// @param name name of merch to be looked up.
/// @return True if found, false if not.
bool ioopm_store_has_merch(ioopm_store_t *store, char*name);

/// @brief Adds merch into the store->warehouse. Utilises merch_hash_table to do so. Returns false
/// if name already in use.
/// @param store ioopm_store_t to be operated upon 
/// @param name name of the merch to be created.
/// @param desc description of the merch to be created.
/// @param price price of the merch to be created.
/// @return  True if merch could be added, false means name is already occupied.
bool ioopm_store_add_merch(ioopm_store_t *store, char *name, char *desc, int price);

/// @brief 
/// @param store 
void ioopm_store_list_merch(ioopm_store_t *store);

bool ioopm_store_delete_merch(ioopm_store_t *store, char *name);

int ioopm_store_edit_merch(ioopm_store_t *store, char* old_name,char *name, char *desc, int price);

void ioopm_store_show_stock(ioopm_store_t *store, char *name);

/// @brief Replenishes stock of given merch at given shelf by given amount. Works with error code
/// returns, 0 or 1 is successful operation.
/// @param store ioopm_store_t to be operated on.
/// @param name name of the merch to replenish
/// @param shelf shelf name to be replenished at, can be already existing for the merch or new.
/// @param amount amount to replenish with.
/// @return Returns 0 if successful.  Returns 1 if successful by increasing amount on 
// already existing shelf. Returns -1 if merch name could not be found. 
/// Returns -2 if shelf is occupied by another type of merch (mixing on shelves is not allowed).
int ioopm_store_replenish_stock(ioopm_store_t *store, char *name, char *shelf, int amount);

void ioopm_store_create_cart();

int ioopm_store_get_cart_index(ioopm_store_t *store);

bool ioopm_store_has_cart(ioopm_store_t *store, int cart_index);

bool ioopm_store_remove_cart(ioopm_store_t *store, int cart_index);

int ioopm_store_add_to_cart(ioopm_store_t *store, int cart_index, char *merch_name, int amount);

int ioopm_store_calculate_cost_cart(ioopm_store_t *store, int cart_index, bool *success);

void ioopm_store_checkout_cart();