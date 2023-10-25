#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "ioopm_store.h"


void print_menu() {
    printf("[A]dd merchandise.\n");
    printf("[L]ist merchandise.\n");
    printf("[D]elete merchandise.\n");
    printf("[E]dit merchandise.\n");
    printf("[S]how stock.\n");
    printf("Re[P]plenish.\n");
    printf("[C]reate cart.\n");
    printf("[R]emove cart.\n");
    printf("[+] Add to cart.\n");
    printf("[-] Remove from cart.\n");
    printf("Check[O]ut.\n");
    printf("[U]ndo.\n");
    printf("[Q]uit\n");
}

int main() {
    print_menu();
    ioopm_store_t *store = ioopm_store_create();
    bool loop = true;
    while (loop) {
        char choice = toupper(ask_question_char("What to do?"));

        if (choice == 'A') {
            char *name = ask_question_string("What is the name of the merch?: ");
            char *desc = ask_question_string("What is the description?:  ");
            int price = ask_question_int("What is the price?:   ");
            if (ioopm_store_add_merch(store, name, desc, price)) {
                printf("Merch was successfully added!\n");
            } else {
                printf("Name already in use!\n");
                // name and desc was not inputed anywhere due to failure and are at risk of becoming
                // memleaks. We need to free them now.
                free(name);
                free(desc);
            }
        }
        else if (choice == 'L') {
            ioopm_store_list_merch(store);
        }
        else if (choice == 'D') {
            char *name = ask_question_string("What merch do you want to delete?:  ");
            if (ioopm_store_has_merch(store, name)) {
                choice = toupper(ask_question_char("Merch found - are you sure you want to delete? (Y for yes): "));
                if (choice == 'Y') {
                    ioopm_store_delete_merch(store, name);
                    printf("Merch was successfully deleted!\n");
                }
                else {
                    printf("Merch was NOT deleted. Either you said no or the merch doesn't exist!\n");
                }
            }
            else {
                printf("No merch with that name!\n");
            }
            // name needs to be freed in either case since unlike in add_merch, it was not inputed 
            // anywhere.
            free(name);
        }
        else if (choice == 'E') {
            char *name = ask_question_string("What merch do you want to edit?:  ");
            if (ioopm_store_has_merch(store, name)) {
                char *new_name = ask_question_string("What is the new name?:  ");
                char *new_desc = ask_question_string("What is the new description?:  ");
                int new_price = ask_question_int("What is the new price?: ");

                choice = ask_question_char("Are you sure you want to edit merch? (Y for yes): ");

                if (choice == 'Y' && (0 == ioopm_store_edit_merch(store, name, new_name, new_desc, new_price))) {
                    printf("Merch was successfully edited!\n");
                }
                else {
                    printf("Merch was NOT edited. Either you said no or the new merch name is already occupied!\n");
                    free(new_name);
                    free(new_desc);
                }
            }
            else {
                printf("No merch with that name!\n");
            }
            free(name);
        }
        else if (choice == 'S') {
            char *name = ask_question_string("What merch to show stock of?: ");
            if (ioopm_store_has_merch(store, name)) {
                ioopm_store_show_stock(store, name);
            }
            else {
                printf("No merch with that name!\n");
            }
            free(name);
        }
        else if (choice == 'P') {
            char *name = ask_question_string("What merch do you want to replenish?:  ");
            char *shelf = ask_question_shelf("What shelf do you want to replenish?: ");
            int amount = ask_question_int("Amount to replenish?: ");
            
            int code = ioopm_store_replenish_stock(store, name, shelf, amount);

            if (code == -2) {
                printf("Shelf is occupied by other merch! Mixing is not allowed!\n");
                // shelf need to be freed since it wasn't input.
                free(shelf);
            }
            else if (code == -1) {
                printf("No merch with that name!\n");
                // shelf need to be freed since it wasn't input.
                free(shelf);
            }
            else if (code == 1) {
                printf("Merch was successfully replenished!\n");
                free(shelf);
            }
            else {
                printf("Merch was successfully replenished!\n");
            }
            free(name);
        }
        else if (choice == 'R') {
            int cart_index = ask_question_int("What index on the cart?");
            ioopm_store_remove_cart()
        }
        else if (choice == 'C') {
            ioopm_store_create_cart(store);
            printf("Cart added with index %d.\n", ioopm_store_get_cart_index(store));
        }
        else if (choice == 'Q') {
            ioopm_store_destroy(store);
            loop = false;
        }
    }
    return 0;
}