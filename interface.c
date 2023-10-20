#include "logic.h"
#include "hash_table.h"
#include "utils.h"
#include "linked_list.h"
#include "common.h"
#include <stdlib.h>
#include <stdio.h>
#include "interface.h"


void ioopm_add_merch(ioopm_hash_table_t *ht) {
    elem_t name = str_elem(ask_question_string("What is the name?: "));

    bool result = name_exists(ht, name);
    if (!result) {
        char *desc = ask_question_string("What is the description?:  ");
        int price = ask_question_int("What is the price?: ");
        merch_create(ht, name, desc, price);
    } else {
        free(name.str_value);
        printf("Item already exists!\n");   
    }
}

void ioopm_list_merch(ioopm_hash_table_t *ht) {
    size_t size = ioopm_hash_table_size(ht);
    int cmpr = 20;
    bool loop = true;
    bool result; 
    int index = 0; 

    while (loop) {
        result = list_merch(ht, cmpr, size, &index);
        if (result) {
            loop = yes_or_no("Do you want to keep printing items? Y/N: ");  
            if (loop) {
                cmpr += 20;
            } else {
                loop = false;
            }
        } else {
            loop = false;
        }
    }
}

void ioopm_delete_merch(ioopm_hash_table_t *ht) {
    elem_t item = str_elem(ask_question_string("What item do you want to delete?:  "));

    bool delete_success = delete_merch(ht, item);
    if (delete_success) {
        printf("Item was successfully deleted.\n");
    }
    else {
        printf("This item does not exist in our warehouse!\n");
    }
    free(item.str_value);
}

void ioopm_edit_merch(ioopm_hash_table_t *ht) { 
    char *changed_str;
    int changed_int;
    bool lookup_success;
    char *question;
    bool try_again = true;
    bool result = true;
    bool yes;
    elem_t item = str_elem(ask_question_string("What item do you want to change?: "));
    // This runs twice since we run lookup inside change_change name and the others aswell, we can delete
    // from the but add return value from lookup as a pointer as a argument.
    elem_t ptr = ioopm_hash_table_lookup(ht, item, &lookup_success);

    if (lookup_success) {
        question = "Do you want to change the name? Y/N: ";
        yes = yes_or_no(question);
        if (yes) {
            while (try_again) {
                changed_str = ask_question_string("Give me a name: ");
                result = change_name(ht, changed_str, &item);
                if (!result) {
                    free(changed_str);
                    try_again = yes_or_no("That name already exist, do you want to try again? Y/N; ");
                } else {
                    free(changed_str);
                    try_again = false;
                }
            }
        }
        if (result) {
            item = str_elem(changed_str);
            ptr = ioopm_hash_table_lookup(ht, str_elem(changed_str), &lookup_success);
        }
        
        question = "Do you want to change the description? Y/N: ";
        yes = yes_or_no(question);
        if (yes) {
            free(ptr.merch_ptr->desc);
            changed_str = ask_question_string("Write your new description:\n");
            change_desc(ht, changed_str, &item);
        }

        question = "Do you want to change the price? Y/N: ";
        yes = yes_or_no(question);
        if (yes) {
            changed_int = ask_question_int("Write your new price:\n");
            change_price(ht, changed_int, &item);
        }
        free(item.str_value);
    } else {
        free(item.str_value);
        printf("That item does not exist in our warehouse.\n");
    }
}

void ioopm_show_stock(ioopm_hash_table_t *ht) {
    elem_t item = str_elem(ask_question_string("What item do you want to see the stocks of?: "));
    show_stock(ht, item);
    free(item.str_value);
}

void ioopm_replenish_stock(ioopm_hash_table_t *ht) {
    elem_t item = str_elem(ask_question_string("What item do you want to replenish?: "));
    char *shelf = ask_question_shelf("What shelf do you want to replenish?: ");
    int amount = ask_question_int("What amount do you want to increase the stock with?: ");

    if (!replenish_stock(ht, &item, shelf, amount)) {
        free(item.str_value);
        free(shelf);
    }   
}

void ioopm_create_cart() {
    // TODO: Stub
}

void ioopm_remove_cart() {
    // TODO: Stub
}

void ioopm_add_to_cart() {
    // TODO: Stub
}

void ioopm_remove_from_cart() {
    // TODO: Stub
}

void ioopm_calculate_cart() {
    // TODO: Stub
}

void ioopm_checkout() {
    // TODO: Stub
}

void ioopm_undo() {
    // TODO: Stub
}

void ioopm_quit(bool *loop) {
    *loop = false;
}