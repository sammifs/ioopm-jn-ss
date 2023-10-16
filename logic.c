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

shelf_t *create_shelf(char *shelf, int amount) {
    shelf_t *result = calloc(1, sizeof(shelf_t));
    result->shelf = shelf;
    result->amount = amount;
    return result;
}

merch_t *merch_create() {
    merch_t *result = calloc(1, sizeof(merch_t));
    

    result->desc = ask_question_string("What is the description?    ");
    result->price = ask_question_int("What is the price?    ");
    // TODO: Look at eq function, maybe should stay NULL, maybe something else.
    // TODO: Create the first shelf where the items is being placed
    result->locs = ioopm_linked_list_create(compare_str);

    return result;
}

void add_merch(ioopm_hash_table_t *ht) {
    elem_t name = ptr_elem(ask_question_string("What is the name?    "));
    
    bool success = false;
    ioopm_hash_table_lookup(ht, name, &success);
    if (!success) {
        merch_t *new = merch_create();
        ioopm_hash_table_insert(ht, name, ptr_elem(new));
    }
    // If true we are not allowed to continue.
    else {
        printf("Item already exists!\n");
    }
}

void list_merch(ioopm_hash_table_t *ht) {
    // TODO: 20 listings per page
    size_t size = ioopm_hash_table_size(ht);
    int cmpr = 20;
    int i = 0;
    bool loop = true;

    if (size != 0) {
        char **merch_names = ioopm_hash_table_keys_char(ht);
        qsort(merch_names, size, sizeof(char *), cmpstringp);
        //TODO: antingen strcmp på både "n" och "N" eller toupper för VARJE question for loop
        while (loop) {
            // We either print the upcoming 20 products or the remaning if there are less
            if (cmpr > size) {
                cmpr = size;   
            }
            for (; i < cmpr; i++) {
                printf("%s\n", merch_names[i]);
            }
            // If there are product that we have not printed yet, get the option to keep going or not
            if (cmpr != size) {
                loop = yes_or_no("Do you want to keep printing items? Y/N: ");
            } else {
                loop = false;
            }
            cmpr = cmpr + 20;
        }
    } else {
        printf("We don't have any items in our warehouse!\n");
    }
}

void delete_merch(ioopm_hash_table_t *ht) {
    // TODO: Stub
}

void edit_merch(ioopm_hash_table_t *ht) {
    char *changed_str;
    int changed_int;
    bool success = false;
    char *qstn;

    elem_t item = ptr_elem(ask_question_string("What item do you want to change?: "));
    elem_t ptr = ioopm_hash_table_lookup(ht, item, &success);
    merch_t *merch = ptr.ptr_value;
    if (success) {
        qstn = "Do you want to change the name? Y/N: ";
        bool yes = yes_or_no(qstn);
        if (yes) {
            // TODO: Får ej byta till ett redan existerande namn!
            bool loop = true;
            while (loop) {
                changed_str = ask_question_string("Write your new name:");
                if (ioopm_hash_table_has_key(ht, ptr_elem(changed_str))) {
                    loop = yes_or_no("This key already exists. Do you want to try a new name? Y/N: ");
                } else {
                // Merch name was not found. We can continue.
                ioopm_hash_table_insert(ht, ptr_elem(changed_str), ptr);
                bool remove_success;
                ioopm_hash_table_remove(ht, item, &remove_success);
                loop = false;
                }
            }
        }

        qstn = "Do you want to change the description? Y/N: ";
        yes = yes_or_no(qstn);
        if (yes) {
            changed_str = ask_question_string("Write your new description:\n");
            merch->desc = changed_str;
        }

        qstn = "Do you want to change the price? Y/N: ";
        yes = yes_or_no(qstn);
        if (yes) {
            changed_int = ask_question_int("Write your new price:\n");
            merch->price = changed_int;
        }

    } else {
        printf("That item does not exist in our warehouse.\n");
    }
}

void show_stock(ioopm_hash_table_t *ht) {
    bool success;
    shelf_t *shelf;

    elem_t item = ptr_elem(ask_question_string("What item do you want to see the stocks of?: "));
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

void replenish_stock(ioopm_hash_table_t *ht) {
    bool success;
    char *shelf;
    int amount;
    
    elem_t item = ptr_elem(ask_question_string("What item do you want to replenish?: "));
    elem_t ptr = ioopm_hash_table_lookup(ht, item, &success);
    merch_t *merch = ptr.ptr_value;
    
    if (success) {
        shelf = ask_question_shelf("What shelf do you want to replenish?:   ");

        bool linked_list_success = false;
        elem_t found = ioopm_linked_list_contains_return_elem(merch->locs, shelf, &linked_list_success);

        if (linked_list_success) {
            shelf_t *found_shelf = found.ptr_value;
            found_shelf->amount += ask_question_int("What amount?:   ");
        } else {
            amount = ask_question_int("That shelf did not exist, we will add a new one\nGive the amount for the shelf: ");
            ioopm_linked_list_append(merch->locs, ptr_elem(create_shelf(shelf, amount)));
        }
    } else {
        printf("That item does not exist in our warehouse.\n");
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

void quit(bool *loop) {
    *loop = false;
}