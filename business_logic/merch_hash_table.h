#pragma once

#include "../datastructures/hash_table.h"
#include "../utils/utils.h"
#include "shelf_list.h"

typedef hash_table_t merch_hash_table_t;

typedef struct merch merch_t;

/// @brief Gets the locations of the merch
/// @param merch The merch to operate upon
/// @return Returns the list och all locations of shelves
shelf_list_t *merch_get_locs(merch_t *merch);

/// @brief Gets the name from the merch
/// @param merch The merch to operate upon
/// @return Returns the name of the merch
char *merch_get_name(merch_t *merch);

/// @brief Gets the total amount of merchandise from the merch:s shelves
/// @param merch The merch to operate upon
/// @return Returns the total amount of merchandise from the merch:s shelves
int merch_get_amount(merch_t *merch);

/// @brief Gets the price of the merch
/// @param merch The merch to operate upon
/// @return Returns the price of the merch
int merch_get_price(merch_t *merch);

/// @brief Changes the description of a merch
/// @param merch The merch to operate upon
/// @param desc The new description, must be heap allocated char *.
void merch_change_desc(merch_t *merch, char *desc);

/// @brief Changes the price of a merch
/// @param merch The merch to operate upon  
/// @param price The new price
void merch_change_price(merch_t *merch, int price);

/// @brief Changes the location list of a merch
/// @param merch The merch to operate upon
/// @param locs The new location list
void merch_change_locs(merch_t *merch, shelf_list_t *locs);

/// @brief Increases the total amount of a merch
/// @param merch The merch to operate upon
/// @param amount The amount to increase with
void merch_increase_amount(merch_t *merch, int amount);

/// @brief Create a new hash table
/// @return A new empty hash table 
merch_hash_table_t *merch_hash_table_create();

/// @brief Delete a hash table and free its memory
/// @param ht a hash table to be deleted
void merch_hash_table_destroy(merch_hash_table_t *ht);

/// @brief check if a hash table has an entry with a given name
/// @param ht hash table operated upon
/// @param name the name sought
/// @return Returns True if the name exists in the hash table, else False
bool merch_hash_table_has_key(merch_hash_table_t *ht, char *name);

/// @brief adds a new merch to the hash table
/// @param ht hash table operated upon
/// @param name key to insert, must be heap allocated char *.
/// @param desc description to insert into the merch, must be heap allocated char *.
/// @param price price to insert into the merch
/// @return Returns True if the insertions went successfully, False if the name already exists
/// in the hash table
bool merch_hash_table_insert(merch_hash_table_t *ht, char* name, char* desc, int price);

/// @brief Gets all the names from the hash table and gathers the pointers in an array
/// @param ht hash table operated upon
/// @return an array with names
char **merch_hash_table_keys(merch_hash_table_t *ht);

/// @brief Gets the size of the hash table
/// @param ht hash table operated upon
/// @return the size of the hash table
int merch_hash_table_size(merch_hash_table_t *ht);

/// @brief Looks if a certain merchandise exists in the hash table
/// @param ht hash table operated upon
/// @param name the name of the merchandise being sought
/// @param success a pointer to a boolean that changes wether the lookup was successful or not
/// @return Returns the pointer to the merch of the name if it exists, else return NULL
merch_t *merch_hash_table_lookup(merch_hash_table_t *ht, char *name, bool *success);

/// @brief removes the given merchandise
/// @param ht hash table operated upon
/// @param name Merchandise to remove
/// @return True if it was successful, else False
bool merch_hash_table_remove(merch_hash_table_t *ht, char *name);

/// @brief Decreases the total amount of a merchandise
/// @param merch_to_change merch operated upon
/// @param decreasing_amount amount to be decreased with
/// @return the new decreased amount
int decrease_total_amount(merch_t *merch_to_change, int decreasing_amount);