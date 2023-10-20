#include "logic.h"
#include "hash_table.h"
#include "utils.h"
#include "linked_list.h"
#include "common.h"
#include <stdlib.h>
#include <stdio.h>


char *get_desc(ioopm_hash_table_t *ht, elem_t item, bool *success)
{
    elem_t sought_merch = ioopm_hash_table_lookup(ht, item, success);

    if (*success) {
        return sought_merch.merch_ptr->desc;
    } else {
        return NULL;
    }
}

int get_price(ioopm_hash_table_t *ht, elem_t item, bool *success)
{
    elem_t sought_merch = ioopm_hash_table_lookup(ht, item, success);

    if (*success) {
        return sought_merch.merch_ptr->price;
    } else {
        return 0;
    }
}

void delete_all_items(ioopm_hash_table_t *ht)
{
    char **merch_names = ioopm_hash_table_keys_char(ht);
    size_t size = ioopm_hash_table_size(ht);
    for (int i = 0; i < size; i++) {
        delete_merch(ht, str_elem(merch_names[i]));
    }
    free(merch_names);
}

// TODO: print whats wrong before returning false in all functions

bool name_exists(ioopm_hash_table_t *ht, elem_t name) {
    bool success = false;
    ioopm_hash_table_lookup(ht, name, &success);
    return success;
}

shelf_t *create_shelf(char *shelf, char* merch_name, int amount) {
    shelf_t *result = calloc(1, sizeof(shelf_t));
    result->shelf = shelf;
    result->merch_name = merch_name;
    result->amount = amount;
    return result;
}

elem_t merch_create(ioopm_hash_table_t *ht, elem_t name, char *desc, int price) {
    merch_t *result = calloc(1, sizeof(merch_t));
    
    // TODO: Look at eq function, maybe should say NULL, maybe something else.
    result->desc = desc;
    result->price = price;
    result->locs = ioopm_linked_list_create(compare_str);

    ioopm_hash_table_insert(ht, name, merch_elem(result));

    return name;
}
// DETTA ÄR FÖR TESTER
void merch_destroy(merch_t *merch) {
    // TODO: 
    ioopm_linked_list_destroy(merch->locs);
    free(merch);
}

// DETTA ÄR FÖR EVENT_LOOP
// void merch_destroy(merch_t *merch) {
//     // TODO: 
//     ioopm_linked_list_destroy(merch->locs);
//     free(merch->desc);
//     free(merch);
// }

bool list_merch(ioopm_hash_table_t *ht, int cmpr, size_t size, int *index) {
    if (size != 0) {
        char **merch_names = ioopm_hash_table_keys_char(ht);
        qsort(merch_names, size, sizeof(char *), cmpstringp);
            // We either print the upcoming 20 products or the remaning if there are less
            if (cmpr >= size) {
                cmpr = size;
            }
            for (; *index < cmpr; (*index)++) {
                printf("%s\n", merch_names[*index]);
            }
            // If there are product that we have not printed yet, get the option to keep going or not
            if (cmpr != size) {
                free(merch_names);
                return true;
            } else {
                free(merch_names);
                return false;
            }
    } else {
        printf("We don't have any items in our warehouse!\n");
        return false;
    }
}

// TODO: Maybe change to bool function for better error handling?
bool delete_merch(ioopm_hash_table_t *ht, elem_t item) {
    bool item_exists;
    elem_t found_merch = ioopm_hash_table_lookup(ht, item, &item_exists);

    if (item_exists) {
        bool remove_success;
        ioopm_hash_table_remove(ht, item, &remove_success);

        ioopm_list_iterator_t *iter = ioopm_list_iterator(found_merch.merch_ptr->locs);

        while (ioopm_iterator_has_next(iter)) {
            assert(ioopm_iterator_next(iter).shelf_ptr);
            free(ioopm_iterator_current(iter).shelf_ptr);
        }
        ioopm_iterator_destroy(iter);
        merch_destroy(found_merch.merch_ptr);
        // TODO: Remove shelves from other list/array
        return true;
    } else {
        return false;
    }
}

// bool delete_merch(ioopm_hash_table_t *ht, elem_t item) {
//     bool item_exists;
//     elem_t found_merch = ioopm_hash_table_lookup(ht, item, &item_exists);

//     if (item_exists) {
//         elem_t *key_ptr = ioopm_get_key_pointer(ht, item, &item_exists);
//         bool remove_success;
//         ioopm_hash_table_remove(ht, item, &remove_success);

//         ioopm_list_iterator_t *iter = ioopm_list_iterator(found_merch.merch_ptr->locs);

//         while (ioopm_iterator_has_next(iter)) {
//             assert(ioopm_iterator_next(iter).shelf_ptr);
//             free(ioopm_iterator_current(iter).shelf_ptr);
//         }
//         ioopm_iterator_destroy(iter);
//         merch_destroy(found_merch.merch_ptr);
//         free(key_ptr);
//         // TODO: Remove shelves from other list/array
//         return true;
//     } else {
//         return false;
//     }
// }

bool change_name(ioopm_hash_table_t *ht, char *name, elem_t *item) {
    bool item_found;
    elem_t ptr = ioopm_hash_table_lookup(ht, *item, &item_found);

    if (ioopm_hash_table_has_key(ht, str_elem(name))) {
        return false;
    } else {
        // Merch name was not found. We can continue.
        ioopm_hash_table_insert(ht, str_elem(name), ptr);
        bool remove_success;

        // Remove the item with the old name
        ioopm_hash_table_remove(ht, *item, &remove_success);
        return true;
    }
}
void change_desc(ioopm_hash_table_t *ht, char *desc, elem_t *item) {
    bool lookup_success;
    elem_t ptr = ioopm_hash_table_lookup(ht, *item, &lookup_success);
    merch_t *merch = ptr.merch_ptr; 
    merch->desc = desc;
}

void change_price(ioopm_hash_table_t *ht, int price, elem_t *item) {
    bool lookup_success;
    elem_t ptr = ioopm_hash_table_lookup(ht, *item, &lookup_success);
    merch_t *merch = ptr.merch_ptr; 
    merch->price = price;
}

bool show_stock(ioopm_hash_table_t *ht, elem_t item) {
    bool success;
    shelf_t *shelf;

    elem_t ptr = ioopm_hash_table_lookup(ht, item, &success);
    merch_t *merch = ptr.merch_ptr;

    if (success) {
        ioopm_list_t *list = merch->locs;
        size_t size = ioopm_linked_list_size(list);

        if (size != 0) {
            ioopm_list_iterator_t *itr = ioopm_list_iterator(list);

            for (int i = 0; i < size; i++) {
                shelf = ioopm_iterator_next(itr).shelf_ptr;
                printf("%s: ", shelf->shelf);
                printf("%d\n", shelf->amount);
            }
            ioopm_iterator_destroy(itr);
            return true;
        } else {
            printf("This product don't have any shelfes\n");
            return false;

        }

    } else {
        printf("That item does not exist in our warehouse.\n");
        return false;
    }
}

bool replenish_stock(ioopm_hash_table_t *ht, elem_t *item, char *shelf, int amount, ioopm_hash_table_t *shelf_ht) {
    //TODO: Free strdups om de inte används!
    bool merch_found_in_warehouse;
    
    elem_t ptr = ioopm_hash_table_lookup(ht, *item, &merch_found_in_warehouse);
    merch_t *merch = ptr.merch_ptr;
    
    if (merch_found_in_warehouse) {
        bool shelf_found_for_correct_merch = false;
        elem_t *found = ioopm_linked_list_contains_return_elem(merch->locs, shelf, &shelf_found_for_correct_merch);

        if (shelf_found_for_correct_merch) {
            shelf_t *found_shelf = found->shelf_ptr;
            found_shelf->amount += amount;
            free(item->str_value);
            return true;
        } else {
            // Check shelf_ht if shelf is used by other merch.
            if (ioopm_hash_table_has_key(shelf_ht, str_elem(shelf))) {
                printf("We couldn't replenish since the given shelf is used by another merchandise.\n");
                return false;
            }
            //TODO: Vi lägger nu till en shelf direkt om den inte finns, får inget val.

            // Shelf was not found anywhere, we create a new shelf and put the pointer in both
            // merch->locs and in shelf_ht.
            elem_t new_shelf = shelf_elem(create_shelf(shelf, item->str_value, amount));
            ioopm_linked_list_append(merch->locs, new_shelf);
            ioopm_hash_table_insert(shelf_ht, str_elem(shelf), new_shelf);
            return true;
        }
    } else {
        printf("We couldn't replenish since the given item does not exist in our warehouse.\n");
        return false;
    }
}

void create_cart() {
    // TODO: Stub
}

void remove_cart() {
    // TODO: Stub
}

void add_to_cart() {
    // TODO: Stub
}

void remove_from_cart() {
    // TODO: Stub
}

void calculate_cart() {
    // TODO: Stub
}

void checkout() {
    // TODO: Stub
}

void undo() {
    // TODO: Stub
}