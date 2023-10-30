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
            int price = ask_question_positive_int("What is the price?:   ");
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
                int new_price = ask_question_positive_int("What is the new price?: ");

                choice = toupper(ask_question_char("Are you sure you want to edit merch? (Y for yes): "));
                int result = ioopm_store_edit_merch(store, name, new_name, new_desc, new_price);
                if (choice == 'Y' && (result == 0)) {
                    printf("Merch was successfully edited!\n");
                } else if (choice == 'Y' && (result == 1)) {
                    printf("The description and price got changed!\n");
                    free(new_name);
                } else {
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
            int amount = ask_question_positive_int("Amount to replenish?: ");
            
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
        else if (choice == 'C') {
            ioopm_store_create_cart(store);
            printf("Cart added with index %d.\n", ioopm_store_get_cart_index(store));
        }
        else if (choice == 'R') {
            int cart_index = ask_question_int("What index on the cart?");
            if (ioopm_store_has_cart(store, cart_index)) {
                choice = toupper(ask_question_char("Cart found - are you sure you want to delete? (Y for yes): "));
                if (choice == 'Y') {
                    ioopm_store_remove_cart(store, cart_index);
                    printf("Cart was successfully removed.\n");
                }
                else {
                    printf("Cart was NOT removed.\n");
                }
            }
            else {
                printf("Cart was not found.\n");
            }
        }
        else if (choice == '+') {
            int cart_index = ask_question_int("What index?: ");
            char *merch_name = ask_question_string("What merch?: ");
            int amount = ask_question_positive_int("How many?: ");
            int result = ioopm_store_add_to_cart(store, cart_index, merch_name, amount);
            if (result == -2) {
                printf("Merch not found in warehouse!\n");
                free(merch_name);
            } else if (result == -1) {
                printf("No cart with that index!\n");
                free(merch_name);
            } else if (result == -3) {
                printf("That amount of that merch does not exist in our warehouse!\n");
                free(merch_name);
            } else {
                printf("Order added successfully to cart!\n");
            }
        }
        else if (choice == '-') {
            int cart_index = ask_question_int("What index of the cart?: ");
            char *merch_name = ask_question_string("What merch?: ");
            int amount = ask_question_positive_int("How many?: ");
            int result = ioopm_store_remove_from_cart(store, cart_index, merch_name, amount);
            if (result == 0) {
                printf("The remove was successful!\n");
            } else if (result == -1) {
                printf("No cart with that index!\n");
            } else if (result == -2) {
                printf("That merch was not found in that cart!\n");
            } else {
                printf("The amount you gave was greater than the items of that merch in your cart!\n");
            }
            free(merch_name);
        }
        else if (choice == 'Q') {
            ioopm_store_destroy(store);
            loop = false;
        }
        else if (choice == '=') {
            int cart_index = ask_question_int("What cart do you want to calculate?: ");
            bool cart_found;
            int cost = ioopm_store_calculate_cost_cart(store, cart_index, &cart_found);
            if (cart_found) {
                printf("Cost of cart %d: %dkr\n", cart_index, cost);
            } else {
                printf("Cart not found!\n");
            }
        } 
        else if (choice == 'O') {
            int cart_index = ask_question_int("What cart do you want to checkout?: ");
            bool calc_done;
            int result = ioopm_store_calculate_cost_cart(store, cart_index, &calc_done);
            bool cart_found = ioopm_store_checkout_cart(store, cart_index);
            if (cart_found) {
                printf("Cart %d costed %dkr and is now checked out!\nThank you for your business!\n", cart_index, result);
            } else {
                printf("That cart was not found, sorry!\n");
            }
        }
    }
    return 0;
}