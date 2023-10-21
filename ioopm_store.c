#include "ioopm_store.h"

struct store {
    merch_hash_table_t *warehouse;

    // hash table mapping shelf name i.e "A34" to merch name i.e "Ost". Used to
    // avoid mixing merch on shelf.
    hash_table_t *shelves;
};

ioopm_store_t *ioopm_store_create() {
    ioopm_store_t *store = calloc(1, sizeof(ioopm_store_t));

    store->warehouse = merch_hash_table_create();

    // shelves is so basic that it can be a generic hash table.
    // It's created with hash function string->int and key comparison str<->str.
    // value equality is never checked so its NULL.
    store->shelves = hash_table_create(string_to_int, compare_str, NULL);

    return store;
}

void ioopm_store_destroy(ioopm_store_t *store) {
    merch_hash_table_destroy(store->warehouse);

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

bool ioopm_store_add_merch(ioopm_store_t *store, char *name, char *desc, int price) {
    return merch_hash_table_insert(store->warehouse, name, desc, price);
}

void ioopm_store_list_merch(ioopm_store_t *store) {
    char **merch_names = merch_hash_table_keys(store->warehouse);
    int size = merch_hash_table_size(store->warehouse);
    qsort(merch_names, size, sizeof(char *), cmpstringp);

    for (int i=0; i<size; i++) {
        printf("%s\n", merch_names[i]);
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
    return merch_hash_table_remove(store->warehouse, name);
}

bool ioopm_store_edit_merch(ioopm_store_t *store, char *old_name, char *name, char *desc, int price) {
    if (ioopm_store_has_merch(store, name)) {
        // We are trying to edit the name into an already existing name, not allowed.
        return false;
    }
    else {
        ioopm_store_delete_merch(store, old_name);
        ioopm_store_add_merch(store, name, desc, price);
        return true;
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
            // Now we find it in merch->locs and increase amount. Return 0 to indicate success.
            shelf_t *shelf = shelf_list_get_shelf(merch_get_locs(merch), shelf_name);
            shelf_increase_amount(shelf, amount);

            return 0;
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
            shelf_list_append(merch_get_locs(merch), shelf_name, merch_name, amount);

            // VERY IMPORTANT to get the merch name pointer from merch_t *merch instead of from 
            // merch_name now we can free merch_name in event_loop however we want 
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

void ioopm_store_create_cart();

void ioopm_store_remove_cart();

void ioopm_store_add_to_cart();

void ioopm_store_calculate_cost_cart();

void ioopm_store_checkout_cart();