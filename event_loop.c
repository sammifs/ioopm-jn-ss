#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "hash_table.h"
#include "linked_list.h"
#include "logic.h"
#include "interface.h"

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

// TODO: TESTER
// TODO: Kolla på strdup i ask_question_char, behövs den? Kanske returnera int istället?
// TODO: Kolla på strdup i shelves listan, greedy linked_list_destroy?
// TODO: ioopm_hash_table_apply_to_all för att frigöra strdup i warehouse


int main() {
    print_menu();
    // TODO : Maybe strcmp -> int compare. Change key to int with hash.
    ioopm_hash_table_t *warehouse = ioopm_hash_table_create(string_to_int, compare_str, NULL);
    bool loop = true;
    while (loop) {
        char *choice_ptr = ask_question_char("What to do?\n");
        char choice = toupper(*choice_ptr);

        if (choice == 'A') {
            ioopm_add_merch(warehouse);
        }
        else if (choice == 'L') {
            ioopm_list_merch(warehouse); 
        }
        else if (choice == 'D') {
            ioopm_delete_merch(warehouse);
        }
        else if (choice == 'E') {
            ioopm_edit_merch(warehouse);
        }
        else if (choice == 'S') {
            ioopm_show_stock(warehouse);
        }
        else if (choice == 'P') {
            ioopm_replenish_stock(warehouse);
        }
        else if (choice == 'C') {
            ioopm_create_cart();
        }
        else if (choice == 'R') {
            ioopm_remove_cart();
        }
        else if (choice == '+') {
            ioopm_add_to_cart();
        }
        else if (choice == '-') {
            ioopm_remove_from_cart();
        }
        else if (choice == '=') {
            ioopm_calculate_cart();
        }
        else if (choice == 'O') {
            ioopm_checkout();
        }
        else if (choice == 'U') {
            ioopm_undo();
        }
        else if (choice == 'Q') {
            ioopm_quit(&loop);
        }
        else {
            printf("Not an option!\n");
        }

        free(choice_ptr);
    }
    delete_all_items(warehouse);
    ioopm_hash_table_destroy(warehouse);
    return 0;
}