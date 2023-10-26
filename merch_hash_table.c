#include "merch_hash_table.h"

struct merch
{
  char *name;
  int price;   // holds the price
  char *desc;
  shelf_list_t *locs; 
  int amount;
};

merch_t *merch_create(char* name, char *desc, int price) {
    merch_t *result = calloc(1, sizeof(merch_t));
    
    result->name = name;
    result->desc = desc;
    result->price = price;
    result->locs = shelf_list_create();
    result->amount = 0;

    return result;
}

// Written like this to work with apply_function type. For use in hash_table_apply_to_all.
void merch_destroy(elem_t key, elem_t *value, void *arg) {
    merch_t *merch = (*value).ptr_value;

    free(merch->name);
    free(merch->desc);
    shelf_list_destroy(merch->locs);
    // TODO : When shelves are fleshed out we need to destroy every individual shelf here.
    free(merch);
}

shelf_list_t *merch_get_locs(merch_t *merch) {
    return merch->locs;
}

char *merch_get_name(merch_t *merch) {
    return merch->name;
}

int merch_get_amount(merch_t *merch) {
    return merch->amount;
}

int merch_get_price(merch_t *merch) {
    return merch->price;
}

void merch_increase_amount(merch_t *merch, int amount) {
    merch->amount += amount;
}

merch_hash_table_t *merch_hash_table_create() {
    // str -> merch_t*
    // Non-generic hashtable, this hashtable will only work on string mapping to pointer.
    // This hashtable also has no use in checking value equality so that is left as NULL.
    merch_hash_table_t *ht = hash_table_create(string_to_int, compare_str, NULL);
    
    return ht;
}

void merch_hash_table_destroy(merch_hash_table_t *ht) {

    hash_table_apply_to_all(ht, merch_destroy, NULL);
    hash_table_destroy(ht);
}

bool merch_hash_table_has_key(merch_hash_table_t *ht, char *name) {
    return hash_table_has_key(ht, str_elem(name));
}

bool merch_hash_table_insert(merch_hash_table_t *ht, char* name, char* desc, int price) {
    if (hash_table_has_key(ht, str_elem(name))) {
        // Merch already exists. Return false.
        return false;
    }
    else {
        merch_t *merch = merch_create(name, desc, price);
        hash_table_insert(ht, str_elem(name), ptr_elem(merch));

        return true;
    }
}

char **merch_hash_table_keys(merch_hash_table_t *ht) {
    list_t *ls = hash_table_keys(ht);
    list_iterator_t *iter = list_iterator(ls);
    int size = hash_table_size(ht);
    char **keys = calloc(size, 32 * sizeof(char));
    for (int i=0; iterator_has_next(iter); i++) {
        keys[i] = iterator_next(iter).str_value;
    }
    iterator_destroy(iter);
    linked_list_destroy(ls);
    return keys;
}

int merch_hash_table_size(merch_hash_table_t *ht) {
    return hash_table_size(ht);
}

merch_t *merch_hash_table_lookup(merch_hash_table_t *ht, char *name, bool *success) {
    return hash_table_lookup(ht, str_elem(name), success).ptr_value;
}

bool merch_hash_table_remove(merch_hash_table_t *ht, char *name) {
    bool success;
    elem_t merch = hash_table_remove(ht, str_elem(name), &success);
    if (success) {
        // Destroying the merch struct is all we want, other two are null.
        merch_destroy(ptr_elem(NULL), &merch, NULL);
        return true;
    }
    else {
        // We did not find the given name, return false.
        return false;

    }
}

int decrease_total_amount(merch_t *merch_to_change, int decreasing_amount) {
    int amount = merch_to_change->amount;
    if (amount > decreasing_amount) {
        amount = amount - decreasing_amount;
        return merch_to_change->amount;
    } else {
        merch_to_change->amount = 0;
        return merch_to_change->amount;
    }
}


shelf_list_t *get_shelf_list(merch_t *merch) {
    return merch->locs;
}