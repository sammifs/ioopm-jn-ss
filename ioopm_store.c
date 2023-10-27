#include "ioopm_store.h"

struct store {
    merch_hash_table_t *warehouse;

    // hash table mapping shelf name i.e "A34" to merch name i.e "Ost". Used to
    // avoid mixing merch on shelf.
    hash_table_t *shelves;

    int cart_index;
    cart_hash_table_t *carts;
};

ioopm_store_t *ioopm_store_create() {
    ioopm_store_t *store = calloc(1, sizeof(ioopm_store_t));

    store->warehouse = merch_hash_table_create();

    // shelves is so basic that it can be a generic hash table.
    // It's created with hash function string->int and key comparison str<->str.
    // value equality is never checked so its NULL.
    store->shelves = hash_table_create(string_to_int, compare_str, NULL);

    store->cart_index = 0;
    store->carts = cart_hash_table_create();
    return store;
}

void ioopm_store_destroy(ioopm_store_t *store) {
    merch_hash_table_destroy(store->warehouse);
    cart_hash_table_destroy(store->carts);

    // store->shelves is not responsible for any of the strdups it carries.
    // Thats why we can do a simple hash_table_destroy on it.
    // shelf_names are destroyed when shelf_list is destroyed, and merch_names are
    // destroyed when when merch_hash_table is destroyed.
    hash_table_destroy(store->shelves);
    free(store);
}

bool ioopm_store_has_merch(ioopm_store_t *store, char*name) {
    return merch_hash_table_has_key(store->warehouse, name);
}
// TODO: Handle empty string as name
bool ioopm_store_add_merch(ioopm_store_t *store, char *name, char *desc, int price) {
    return merch_hash_table_insert(store->warehouse, name, desc, price);
}

void ioopm_store_list_merch(ioopm_store_t *store) {
    char **merch_names = merch_hash_table_keys(store->warehouse);
    int size = merch_hash_table_size(store->warehouse);
    qsort(merch_names, size, sizeof(char *), cmpstringp);

    int batch_size = 20;
    int current_i = 0;

    while (current_i < size) {

        for (int i=current_i; i < current_i + batch_size && i < size; i++) {
            printf("%s\n", merch_names[i]);
        }

        if (current_i + batch_size < size) {
            char choice = toupper(ask_question_char(("Continue printing? (Y for yes): ")));

            if (choice != 'Y') {
                break;
            }
        }
        else { break; }

        current_i += batch_size;
    }
    free(merch_names);
}

bool delete_merch_from_shelves_pred_fun(entry_t *entry, void *name) {
    if (compare_str(entry_value(entry), str_elem(name))) { return true; }
    else return false;
}
void delete_merch_from_shelves_ht(ioopm_store_t *store, char *name) {
    hash_table_destroy_any_entries(store->shelves, delete_merch_from_shelves_pred_fun, name);
}
bool ioopm_store_delete_merch(ioopm_store_t *store, char *name) {
    delete_merch_from_shelves_ht(store, name);
    carts_hash_table_remove_orders(store->carts, name);
    return merch_hash_table_remove(store->warehouse, name);
}

int ioopm_store_edit_merch(ioopm_store_t *store, char *old_name, char *name, char *desc, int price) {
    if (ioopm_store_has_merch(store, old_name)) {
        if (ioopm_store_has_merch(store, name)) {
            // We are trying to edit the name into an already existing name, not allowed.
            // Return error code -2
            return -2;
        }
        else {
            ioopm_store_delete_merch(store, old_name);
            ioopm_store_add_merch(store, name, desc, price);
            return 0;
        }
    }
    else {
        // Merch we are trying to edit was not found. Return error code -1.
        return -1;
    }
}

void ioopm_store_show_stock(ioopm_store_t *store, char *name) {
    bool success;
    shelf_list_print_name_amount(merch_get_locs(merch_hash_table_lookup(store->warehouse, name, &success)));
}

int ioopm_store_replenish_stock(ioopm_store_t *store, char *merch_name, char *shelf_name, int amount) {
    bool merch_found;
    merch_t *merch = merch_hash_table_lookup(store->warehouse, merch_name, &merch_found);

    if (merch_found) {
        bool shelf_found;
        elem_t merch_of_found_shelf = hash_table_lookup(store->shelves, str_elem(shelf_name), &shelf_found);
        if (shelf_found && compare_str(merch_of_found_shelf, str_elem(merch_name))) {
            // This means we found the shelf and it belongs to the merch we want to replenish. Score!
            // Now we find it in merch->locs and increase amount. Return 1 to indicate success.
            shelf_t *shelf = shelf_list_get_shelf(merch_get_locs(merch), shelf_name);
            shelf_increase_amount(shelf, amount);
            merch_increase_amount(merch, amount);

            return 1;
        }
        else if (shelf_found) {
            // We found the shelf but it did not belong to our merch. Mixing on shelves is not 
            // allowed. Return error code -2.

            return -2;
        }
        else {
            // Shelf wasnt found, this means it is free to claim for our merch! Create a new shelf
            // and place it in merch->locs. Then create an entry to the shelves hash table.
            // Return 0 to indicate success.
            shelf_list_append(merch_get_locs(merch), shelf_name, amount);
            merch_increase_amount(merch, amount);

            // VERY IMPORTANT to get the merch name pointer from merch_t *merch instead of from 
            // merch_name. Now we can free merch_name in event_loop however we want 
            // and the shelves hashtable is free from responsiblity.
            hash_table_insert(store->shelves, str_elem(shelf_name), str_elem(merch_get_name(merch)));
            return 0;
        }
    }
    else {
        // Merch wasnt found. Return error code -1.
        return -1;
    }
}

void ioopm_store_create_cart(ioopm_store_t *store) {
    store->cart_index++;
    cart_hash_table_insert(store->carts, store->cart_index);
}

int ioopm_store_get_cart_index(ioopm_store_t *store) {
    return store->cart_index;
}

bool ioopm_store_has_cart(ioopm_store_t *store, int cart_index) {
    bool success;
    cart_hash_table_lookup(store->carts, cart_index, &success);
    return success;
}

//TODO: Lägg till "free" för de strdup:ade namnen
bool ioopm_store_remove_cart(ioopm_store_t *store, int cart_index) {
    return cart_hash_table_remove(store->carts, cart_index);
}

bool amount_exists(cart_hash_table_t *carts, merch_t *merch, int amount) {
    int existing_amount = merch_get_amount(merch);
    int amount_within_orders = cart_hash_table_order_amount_for_merch(carts, merch_get_name(merch));
    if (amount + amount_within_orders <= existing_amount) {
        return true;
    } else {
        return false;
    }
}

// strdup merch_name
int ioopm_store_add_to_cart(ioopm_store_t *store, int cart_index, char *merch_name, int amount) {
    bool merch_found;
    merch_t *merch = merch_hash_table_lookup(store->warehouse, merch_name, &merch_found);

    if (merch_found) {
        if (amount_exists(store->carts, merch, amount)) {
            if (cart_hash_table_append_order(store->carts, cart_index, merch_name, amount, merch_get_price(merch))) {
                // Everything worked. Return 0.
                return 0;
            } else {
                // Cart not found. Return error code -1.
                return -1;
            }
        } else {
            return -3;
        }
    } else {
        // Merch not found. Return error code -2.
        return -2;
    }
}

void ioopm_store_remove_from_cart(ioopm_store_t *store, int cart_index) {
    // TODO : stub
}

int ioopm_store_calculate_cost_cart(ioopm_store_t *store, int cart_index, bool *success) {
    return cart_hash_table_calculate_cost(store->carts, cart_index, success);
}

void checkout(ioopm_store_t *store, cart_t *cart) {
    order_t *order = cart_get_first_order(cart);

    while (order != NULL) {
        int amount = order_get_amount(order);
        char *item = order_get_merch(order);
        bool merch_found;

        merch_t *merch_to_change = merch_hash_table_lookup(store->warehouse, item, &merch_found);
        shelf_list_t *locs = merch_get_locs(merch_to_change);

        decrease_total_amount(merch_to_change, amount);
        list_t *shelves_to_delete = shelf_decrease_amount(locs, amount);

        if (shelves_to_delete != NULL) {
            list_iterator_t *iter = list_iterator(shelves_to_delete);

            while (iterator_has_next(iter)) {
                char *shelf_name = iterator_next(iter).ptr_value;

                bool success;
                hash_table_remove(store->shelves, ptr_elem(shelf_name), &success);
            }
            iterator_destroy(iter);
            linked_list_remove(shelves_to_delete,0);

            for (int i=0; i<linked_list_size(shelves_to_delete); i++) {
                destroy_first_shelf(locs);
            }
            linked_list_destroy(shelves_to_delete);
        }
        
        order = cart_get_next_order(order);
    }
}

bool ioopm_store_checkout_cart(ioopm_store_t *store, int cart_index) {
    bool cart_found;
    cart_t *cart = cart_hash_table_lookup(store->carts, cart_index, &cart_found);
    if (cart_found) {
        checkout(store, cart);
        // Remove the cart that has been checked out
        cart_hash_table_remove(store->carts, cart_index);
        return true;
    } else {
        return false;
    }
}