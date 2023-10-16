#include "logic.h"
#include "hash_table.h"
#include "utils.h"
#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>

// TODO: print whats wrong before returning false in all functions


struct shelf
{
  char *shelf;       // holds shelf as for exampel A23
  int amount;   // holds the amount in "ören"
};

struct merch
{
  char *name;       // holds the key
  int price;   // holds the price
  char *desc;
  ioopm_list_t *locs; 
};

merch_t *merch_create(char *name) {
    merch_t *result = calloc(1, sizeof(merch_t));
    
    result->name = name;
    result->desc = ask_question_string("What is the description?    ");
    result->price = ask_question_int("What is the price?    ");
    // TODO: Look at eq function, maybe should stay NULL, maybe something else.
    // TODO: Create the first shelf where the items is being placed
    result->locs = ioopm_linked_list_create(NULL);

    return result;
}

void add_merch(ioopm_hash_table_t *ht) {
    elem_t name = ptr_elem(ask_question_string("What is the name?    "));
    
    bool success = false;
    ioopm_hash_table_lookup(ht, name, &success);
    if (!success) {
        merch_t *new = merch_create(name.ptr_value);
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
    char *loop = "Boi";

    if (size != 0) {
        char **merch_names = ioopm_hash_table_keys_char(ht);
        qsort(merch_names, size, sizeof(char *), cmpstringp);
        //TODO: antingen strcmp på både "n" och "N" eller toupper för VARJE question for loop
        while (!(strcmp("N", loop) == 0 || strcmp("n", loop) == 0)) {
            // We either print the upcoming 20 products or the remaning if there are less
            if (cmpr > size) {
                cmpr = size;   
            }
            for (; i < cmpr; i++) {
                printf("%s\n", merch_names[i]);
            }
            // If there are product that we have not printed yet, get the option to keep going or not
            if (cmpr != size) {
                loop = ask_question_string("Press n to go back to menu, else enter to keep on going");
            } else {
                loop = "N";
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
        // Ändra edit_name eftersom vi bör byta plats på produkten efter byte av namne
        // Eventuellt att vi använder ett ID som representerar varje produkt som inte ändras vid ändring av namn
        qstn = "Do you want to change the name?";
        bool yes = yes_or_no(qstn);
        if (yes) {
            // Får ej byta till ett redan existerande namn!
            changed_str = ask_question_string("Write your new name:\n");
            merch->name = changed_str;
        }

        qstn = "Do you want to change the description?";
        yes = yes_or_no(qstn);
        if (yes) {
            changed_str = ask_question_string("Write your new description:\n");
            merch->name = changed_str;
        }

        qstn = "Do you want to change the price?";
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
        } else {
            printf("This product don't have any shelfes\n");
        }


    } else {
        printf("That item does not exist in our warehouse.\n");
    }
}

void replenish_stock(ioopm_hash_table_t *ht) {
    // TODO: Stub
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