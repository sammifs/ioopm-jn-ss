#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include "common.h"
#include "linked_list.h"
#include "iterator.h"

/**
 * @file hash_table.h
 * @author Johannes Segersten, Samuel Sverker
 * @date 10 Sep 2023
 * @brief Simple hash table that maps integer keys to string values.
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 *
 * @see $CANVAS_OBJECT_REFERENCE$/assignments/gb54499f3b7b264e3af3b68c756090f52
 */

typedef struct hash_table hash_table_t;

typedef struct entry entry_t;

typedef int(*hash_function)(elem_t);

elem_t entry_value(entry_t *entry);

/// @brief Create a new hash table
/// @return A new empty hash table
hash_table_t *hash_table_create(hash_function f, eq_function key_eq, eq_function value_eq);

/// @brief Delete a hash table and free its memory
/// @param ht a hash table to be deleted
void hash_table_destroy(hash_table_t *ht);

/// @brief add key => value entry in hash table ht
/// @param ht hash table operated upon
/// @param key key to insert
/// @param value value to insert
void hash_table_insert(hash_table_t *ht, elem_t key, elem_t value);

/// @brief lookup value for key in hash table ht
/// @param ht hash table operated upon
/// @param key key to lookup
/// @param success will update to true if function terminates correctly, otherwise false.
/// @return the value mapped to by the key.
elem_t hash_table_lookup(hash_table_t *ht, elem_t key, bool *success);

/// @brief remove any mapping from key to a value
/// @param ht hash table operated upon
/// @param key key to remove
/// @param success will update to true if function terminates correctly, otherwise false.
/// @return the value mapped to by key.
elem_t hash_table_remove(hash_table_t *ht, elem_t key, bool *success);

/// @brief returns the number of key => value entries in the hash table
/// @param ht hash table operated upon
/// @return the number of key => value entries in the hash table
size_t hash_table_size(hash_table_t *ht);

/// @brief checks if the hash table is empty
/// @param ht hash table operated upon
/// @return true is size == 0, else false
bool hash_table_is_empty(hash_table_t *ht);

/// @brief clear all the entries in a hash table
/// @param ht hash table operated upon
void hash_table_clear(hash_table_t *ht);

/// @brief return the keys for all entries in a hash map (in no particular order, but same as hash_table_values)
/// @param ht hash table operated upon
/// @return an list_t of keys for hash table h
list_t *hash_table_keys(hash_table_t *ht);

/// @brief return the values for all entries in a hash map (in no particular order, but same as hash_table_keys)
/// @param ht hash table operated upon
/// @return an list_t of values for hash table h
list_t *hash_table_values(hash_table_t *ht);

/// @brief check if a hash table has an entry with a given key
/// @param ht hash table operated upon
/// @param key the key sought
bool hash_table_has_key(hash_table_t *ht, elem_t key);

/// @brief check if a hash table has an entry with a given value
/// @param ht hash table operated upon
/// @param value the value sought
bool hash_table_has_value(hash_table_t *ht, elem_t value);

/// @brief check if a predicate is satisfied by all entries in a hash table
/// @param ht hash table operated upon
/// @param pred the predicate
/// @param arg extra argument to pred
bool hash_table_all(hash_table_t *ht, predicate pred, void *arg);

/// @brief check if a predicate is satisfied by any entry in a hash table
/// @param ht hash table operated upon
/// @param pred the predicate
/// @param arg extra argument to pred
bool hash_table_any(hash_table_t *ht, predicate pred, void *arg);

/// @brief apply a function to all entries in a hash table
/// @param ht hash table operated upon
/// @param apply_fun the function to be applied to all elements
/// @param arg extra argument to apply_fun
void hash_table_apply_to_all(hash_table_t *ht, apply_function apply_fun, void *arg);

typedef bool(*predicate_entry)(entry_t *entry, void *arg);

/// @brief destroys all entires that pass the predicate.
/// @param ht hash table operated upon
/// @param pred_fun predicate function that entries need to pass
void hash_table_destroy_any_entries(hash_table_t *ht, predicate_entry pred_fun, void *arg);

/// @brief Changes the value of all entries that the predicate function returns true on
/// @param ht hash table operated upon
/// @param pred_fun predicate function that entries need to pass
/// @param old Argument of which will be 
void hash_table_change_all(hash_table_t *ht, predicate_entry pred_fun, void *old, void *new);
