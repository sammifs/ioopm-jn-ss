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
    printf("Check[O]ut.\n");
    printf("[U]ndo.\n");
    printf("[Q]uit\n");
}

int main() {
    print_menu();
    ioopm_hash_table_t *ht = ioopm_hash_table_create(char_to_int, compare_int, NULL);
    init_hashtable(ht);
    bool loop = true;
    while (loop) {
        elem_t input = int_elem(*ask_question_string("What to do?\n"));
        bool success;
        bool (*fun_pointer) ();
        fun_pointer = ioopm_hash_table_lookup(ht, input, &success).ptr_value;
        loop = fun_pointer();
    }
    ioopm_hash_table_destroy(ht);
    return 0;
}