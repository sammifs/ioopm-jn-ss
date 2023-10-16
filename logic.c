#include "logic.h"
#include "hash_table.h"
#include "utils.h"
#include "linked_list.h"
#include "common.h"
#include <stdlib.h>
#include <stdio.h>

// TODO: print whats wrong before returning false in all functions

struct merch
{
  int price;   // holds the price
  char *desc;
  ioopm_list_t *locs; 
};

bool name_exists(ioopm_hash_table_t *ht, elem_t name) {
    bool success = false;
    ioopm_hash_table_lookup(ht, name, &success);
    return success;
}

shelf_t *create_shelf(char *shelf, int amount) {
    shelf_t *result = calloc(1, sizeof(shelf_t));
    result->shelf = shelf;
    result->amount = amount;
    return result;
}

void merch_create(ioopm_hash_table_t *ht, elem_t name, char *desc, int price) {
    merch_t *result = calloc(1, sizeof(merch_t));
    
    // TODO: Look at eq function, maybe should say NULL, maybe something else.
    result->desc = desc;
    result->price = price;
    result->locs = ioopm_linked_list_create(compare_str);

    ioopm_hash_table_insert(ht, name, ptr_elem(result));
}


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
                return true;
            } else {
                return false;
            }
    } else {
        printf("We don't have any items in our warehouse!\n");
        return false;
    }
}

void delete_merch(ioopm_hash_table_t *ht) {
    // TODO: Stub
}

bool change_name(ioopm_hash_table_t *ht, char *name, elem_t *item, elem_t *ptr) {
    if (ioopm_hash_table_has_key(ht, ptr_elem(name))) {
        return false;
    } else {
        // Merch name was not found. We can continue.
        ioopm_hash_table_insert(ht, ptr_elem(name), *ptr);
        bool remove_success;

        // Remove the item with the old name
        ioopm_hash_table_remove(ht, *item, &remove_success);
        return true;
    }
}
void change_desc(char *desc, elem_t *ptr) {
    merch_t *merch = ptr->ptr_value; 
    merch->desc = desc;
}

void change_price(int price, elem_t *ptr) {    
    merch_t *merch = ptr->ptr_value; 
    merch->price = price;
}


void show_stock(ioopm_hash_table_t *ht, elem_t item) {
    bool success;
    shelf_t *shelf;

    elem_t ptr = ioopm_hash_table_lookup(ht, item, &success);
    merch_t *merch = ptr.ptr_value;

    if (success) {
        ioopm_list_t *list = merch->locs;
        size_t size = ioopm_linked_list_size(list);
        ioopm_list_iterator_t *itr = ioopm_list_iterator(list);

        if (size != 0) {
            for (int i = 0; i < size; i++) {
                shelf = ioopm_iterator_next(itr).ptr_value;
                printf("%s: ", shelf->shelf);
                printf("%d\n", shelf->amount);
            }
            ioopm_iterator_destroy(itr);
        } else {
            ioopm_iterator_destroy(itr);
            printf("This product don't have any shelfes\n");
        }

    } else {
        printf("That item does not exist in our warehouse.\n");
    }
}

void replenish_stock(ioopm_hash_table_t *ht, elem_t *item, char *shelf, int amount) {
    bool success;
    
    elem_t ptr = ioopm_hash_table_lookup(ht, *item, &success);
    merch_t *merch = ptr.ptr_value;
    
    if (success) {
        bool linked_list_success = false;
        elem_t *found = ioopm_linked_list_contains_return_elem(merch->locs, shelf, &linked_list_success);

        if (linked_list_success) {
            shelf_t *found_shelf = found->ptr_value;
            found_shelf->amount += amount;
        } else {
            //TODO: Vi lägger nu till en shelf direkt om den inte finns, får inget val.
            ioopm_linked_list_append(merch->locs, ptr_elem(create_shelf(shelf, amount)));
        }
    } else {
        printf("We couldn't replenish since the given item does not exist in our warehouse.\n");
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