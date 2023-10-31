#pragma once

#include "datastructures/hash_table.h"
#include "utils.h"

typedef hash_table_t cart_hash_table_t;

typedef struct cart cart_t;
typedef struct order order_t;

/// @brief Create a new hash table
/// @return A new empty hash table
cart_hash_table_t *cart_hash_table_create();

/// @brief Delete a hash table and free its memory
/// @param ht a hash table to be deleted
void cart_hash_table_destroy(cart_hash_table_t *ht);

/// @brief adds a new cart to the hash table. We never check for collision of two
/// cart which means that the user must handle the cart_index to never insert an
/// already existing one.
/// @param ht hash table operated upon
/// @param cart_index key to insert
void cart_hash_table_insert(cart_hash_table_t *ht, int cart_index);

/// @brief Looks if a certain cart exists in the hash table
/// @param ht hash table operated upon
/// @param cart_index the index of the cart being sought
/// @param success a pointer to a boolean that changes wether the lookup was successful or not
/// @return Returns the pointer to the cart of the given index if it exists, else return NULL
cart_t *cart_hash_table_lookup(cart_hash_table_t *ht, int cart_index, bool *success);

/// @brief removes the given cart
/// @param ht hash table operated upon
/// @param cart_index cart to remove
/// @return True if it was successful, else False
bool cart_hash_table_remove(cart_hash_table_t *ht, int cart_index);

/// @brief Appends a new order of a merchandise with an amount in a specific cart given
/// @param ht hash table operated upon
/// @param cart_index the cart to insert the order in
/// @param merch_name the merchandise to be added
/// @param amount the amount of the merchandise
/// @param price the price of the merchandise
/// @return True if it went successfully, else False
bool cart_hash_table_append_order(cart_hash_table_t *ht, int cart_index, char *merch_name, int amount, int price);

/// @brief Calculates to cost of the whole cart
/// @param ht hash table operated upon
/// @param cart_index the cart operated upon
/// @param success pointer to a boolean that is changing depending to if the cart exists or not
/// @return the total cost of the cart or 0 if the cart doesn't exist
int cart_hash_table_calculate_cost(cart_hash_table_t *ht, int cart_index, bool *success);

/// @brief Gets the total amount of a merchandise that is reserved in all carts
/// @param ht hash table operated upon
/// @param merch_name merch sought in the carts
/// @return the total amount of the merchandise that is reserved in carts
int cart_hash_table_order_amount_for_merch(cart_hash_table_t *ht, char *merch_name);

/// @brief Gets the total amount of a merchandise that is reserved in a single cart
/// @param cart cart operated upon
/// @param merch_name merch sought in the cart
/// @return the amount of the merchandise that is reserved in the cart
int single_cart_order_amount_of_merch(cart_t *cart, char *merch_name);

/// @brief decreases the number of items of a merchandise in a cart
/// @param cart cart operated upon
/// @param merch_name merchandise to decrease
/// @param amount amount to decrease with
void remove_amount_of_items(cart_t *cart, char *merch_name, int amount);

/// @brief removes a specific merchandise from all carts
/// @param ht hash table operated upon
/// @param name merchandise to remove
void carts_hash_table_remove_orders(cart_hash_table_t *ht, char *name);

/// @brief changes a specific merchandise in all carts that it exists in
/// @param ht hash table operated upon
/// @param old_name merch to be changed
/// @param new_name new name of the merch
/// @param price new price of the merch
void carts_hash_table_change_orders(cart_hash_table_t *ht, char *old_name, char *new_name, int price);

/// @brief Gets the first order of a cart
/// @param cart cart operated upon
/// @return the first order in the cart
order_t *cart_get_first_order(cart_t *cart);

/// @brief Gets the next order from another order
/// @param order order operated upon
/// @return the next order from the given one
order_t *cart_get_next_order(order_t *order);

/// @brief Gets the amount of a order
/// @param order order operated upon
/// @return the amount of the order
int order_get_amount(order_t *order);

/// @brief Gets the merchandise name in the order
/// @param order order operated upon
/// @return the name of the merchandise in the order
char *order_get_merch(order_t *order);
