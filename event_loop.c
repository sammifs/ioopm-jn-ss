#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "hash_table.h"
#include "linked_list.h"
#include "logic.h"

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
    printf("[=] Calculate cost of cart.");
    printf("Check[O]ut.\n");
    printf("[U]ndo.\n");
    printf("[Q]uit\n");
}

int main() {
    print_menu();
    // TODO : Maybe strcmp -> int compare. Change key to int with hash.
    ioopm_hash_table_t *warehouse = ioopm_hash_table_create(string_to_int, compare_int, NULL);
    bool loop = true;
    while (loop) {
        char choice = toupper(*ask_question_string("What to do?\n"));

        if (choice == 'A') {
            add_merch(warehouse);
        }
        else if (choice == 'L') {
            list_merch(warehouse); 
        }
        else if (choice == 'D') {
            delete_merch(warehouse);
        }
        else if (choice == 'E') {
            edit_merch(warehouse);
        }
        else if (choice == 'S') {
            show_stock(warehouse);
        }
        else if (choice == 'P') {
            replenish_stock(warehouse);
        }
        else if (choice == 'C') {
            create_cart();
        }
        else if (choice == 'R') {
            remove_cart();
        }
        else if (choice == '+') {
            add_to_cart();
        }
        else if (choice == '-') {
            remove_from_cart();
        }
        else if (choice == '=') {
            calculate_cart();
        }
        else if (choice == 'O') {
            checkout();
        }
        else if (choice == 'U') {
            undo();
        }
        else if (choice == 'Q') {
            quit(&loop);
        }
        else {
            printf("Not an option!\n");
        }
    }
    ioopm_hash_table_destroy(warehouse);
    return 0;
}