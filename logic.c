#include "logic.h"
#include "hash_table.h"
#include "utils.h"


void init_hashtable(ioopm_hash_table_t *ht) {
    ioopm_hash_table_insert(ht, int_elem('A'), ptr_elem(add_merch));
    ioopm_hash_table_insert(ht, int_elem('L'), ptr_elem(list_merch));
    ioopm_hash_table_insert(ht, int_elem('R'), ptr_elem(remove_merch));
    ioopm_hash_table_insert(ht, int_elem('E'), ptr_elem(edit_merch));
    ioopm_hash_table_insert(ht, int_elem('S'), ptr_elem(show_stock));
    ioopm_hash_table_insert(ht, int_elem('Q'), ptr_elem(quit));
}


bool add_merch(ioopm_hash_table_t *ht) {
    // TODO: Stub    
    char *key = ask_question_string("What is our product?  ");
    ioopm_hash_table_insert(ht, int_elem('A'), int_elem(324));
    return true;
}

bool list_merch(ioopm_hash_table_t *ht) {
    // TODO: Stub
    return true;
}

bool remove_merch(ioopm_hash_table_t *ht) {
    // TODO: Stub
    return true;
}

bool edit_merch(ioopm_hash_table_t *ht) {
    // TODO: Stub
    return true;
}

bool show_stock(ioopm_hash_table_t *ht) {
    // TODO: Stub
    return true;
}

bool replenish_stock(ioopm_hash_table_t *ht) {
    // TODO: Stub
    return true;
}

bool quit(ioopm_hash_table_t *ht) {
    // TODO:Stub
    return false;
}