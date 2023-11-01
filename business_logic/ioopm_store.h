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
/// @param store Where all merchandise are kept.
void ioopm_store_destroy(ioopm_store_t *store);

/// @brief Gets the warehouse from the store
/// @param store Where the warehouse is located
/// @return returns the warehouse hash_table
merch_hash_table_t *store_get_warehouse(ioopm_store_t *store);

/// @brief Gets the shelf hash_table from the store
/// @param store Where the shelf hash_table is located
/// @return returns the shelf hash_table
hash_table_t *store_get_shelves(ioopm_store_t *store);

/// @brief Checks if store->warehouse contains specified merch.
/// @param store Where all merchandise are kept.
/// @param name name of merch to be looked up.
/// @return True if found, false if not.
bool ioopm_store_has_merch(ioopm_store_t *store, char *name);

/// @brief Adds merch into the store->warehouse. Utilises merch_hash_table to do so. Returns false
/// if name already in use.
/// @param store Where all merchandise are kept.
/// @param name name of the merch to be created.
/// @param desc description of the merch to be created.
/// @param price price of the merch to be created.
/// @return  True if merch could be added, false means name is already occupied.
bool ioopm_store_add_merch(ioopm_store_t *store, char *name, char *desc, int price);

/// @brief All merchandise found are dividied into pages of 20 merchandise each. The function then prints
/// the specified page.
/// @param store Where all merchandise are kept.
/// @param page Page of 20 to print.
/// @return 1 if page was successfully printed and there are no items beyond the page. Returns 0
/// if successfull print and no items beyond the page. Returns -1 if page was out of bounds. 
/// Returns -2 if page was negative (negative pages are invalid). 
int ioopm_store_list_merch(ioopm_store_t *store, int page);


/// @brief Deletes a specific merchandise from the warehouse, from the respetive shelves and possibly from carts.
/// @param store Where all merchandise are kept.
/// @param name The name of the merchandise to be deleted.
/// @return True if the deletion was successful, otherwise false.
bool ioopm_store_delete_merch(ioopm_store_t *store, char *name);


/// @brief Edits the name, description and price of a given merch.
/// @param store Where all merchandise are kept.
/// @param old_name The name of the merchandise to be changed.
/// @param new_name The new name of the merchandise.
/// @param desc The new description for the merchandise
/// @param price The new price for the merchandise 
/// @return Return 1 if we only changed description and/or price. Return 0 if we successfully changed
/// the name and the description and the price. Returns -1 if the merchandise to be changed was not found.
/// Returns -2 if we try to change the name to something that already exists in the warehouse.
int ioopm_store_edit_merch(ioopm_store_t *store, char* old_name, char *new_name, char *desc, int price);

/// @brief Prints both the avaliable amount for the user and all shelves to a specific merchandise 
/// with respective amount.
/// @param store Where all merchandise are kept.
/// @param name The merchandise to be printed from
/// @return true if merch was found, false if it wasn't.
bool ioopm_store_show_stock(ioopm_store_t *store, char *name);

/// @brief Replenishes stock of given merch at given shelf by given amount. Works with error code
/// returns, 0 or 1 is successful operation.
/// @param store ioopm_store_t to be operated on.
/// @param name name of the merch to replenish
/// @param shelf shelf name to be replenished at, can be already existing for the merch or new.
/// @param amount amount to replenish with.
/// @return Returns 0 if successful. Returns 1 if successful by increasing amount on 
// already existing shelf. Returns -1 if merch name could not be found. 
/// Returns -2 if shelf is occupied by another type of merch (mixing on shelves is not allowed).
/// Returns -3 if amount is less than 1.
int ioopm_store_replenish_stock(ioopm_store_t *store, char *name, char *shelf, int amount);

/// @brief Creates a cart 
/// @param store Where the cart will be stored and where all merchandise exist
void ioopm_store_create_cart(ioopm_store_t *store);

/// @brief Gets the index of the the last created cart
/// @param store Where the cart_index is stored
/// @return Return the index of the last created cart or 0 if none has been made.
int ioopm_store_get_cart_index(ioopm_store_t *store);

/// @brief Checks if a certain cart exists
/// @param store Where the carts exist if the have been created and not yet checked out
/// @param cart_index The index of the cart which is being seeked
/// @return Returns True if the cart was found, else False
bool ioopm_store_has_cart(ioopm_store_t *store, int cart_index);

/// @brief Removes a cart completely 
/// @param store Where all the carts exist
/// @param cart_index The index of the cart which is being removed
/// @return Returns True if the cart was found and successfully removed, else False
bool ioopm_store_remove_cart(ioopm_store_t *store, int cart_index);

/// @brief Adds a merchandise with some amount to a cart. Works with error code
/// returns, 0 is successful operation, else unsuccessful.
/// @param store Where all the carts and merchandise exists
/// @param cart_index The index of the cart of which to put the merchandise in
/// @param merch_name The name of the merchandise to be added to the cart
/// @param amount A positive number of the amount of merchandise to be added to the cart
/// @return Returns 0 if everything worked well. Returns -1 if the given cart was not found. Returns -2 
/// if the merch was not found. Returns -3 if the given amount was bigger than the existing amount in 
/// the warehouse. Returns -4 if amount is less than 1.
int ioopm_store_add_to_cart(ioopm_store_t *store, int cart_index, char *merch_name, int amount);

/// @brief Removes a number of items of merchandise from a specific cart. Works with error code
/// returns, 0 is successful operation, else unsuccessful.
/// @param store Where all the carts exists
/// @param cart_index The index of the cart where to remove the merchandise from
/// @param merch_name The name of the merchandise to be removed 
/// @param amount A positive number of the amount of merchandise to be reomved from the cart
/// @return Returns 0 if the everything went successfully. Returns -1 if the cart was not found. Returns -2
/// if the merchandise was not found in the given cart. Returns -3 if the given amount was greater than the 
/// existing amount, couldn't remove that many. Returns -4 if amount is less than 1.
int ioopm_store_remove_from_cart(ioopm_store_t *store, int cart_index, char *merch_name, int amount);

/// @brief Calculates the cost of a specific cart
/// @param store Where all the carts exist
/// @param cart_index The index of the cart to be calculated
/// @param success A pointer to a boolean to be changed if the cart was found or not
/// @return Returns the whole cost of the cart
int ioopm_store_calculate_cost_cart(ioopm_store_t *store, int cart_index, bool *success);

/// @brief Checksout a cart and decreases the amount of the merchandise that has been checked out
/// @param store Where the carts exist
/// @param cart_index The index of the cart to be checked out
/// @return True if the cart was found and successfully checked out, else False
bool ioopm_store_checkout_cart(ioopm_store_t *store, int cart_index);