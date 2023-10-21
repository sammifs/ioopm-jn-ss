#pragma once

typedef struct cart_list cart_list_t;

cart_list_t *cart_list_create(int index_of_cart);

void cart_list_destroy(cart_list_t *ls);

void cart_list_append_order(cart_list_t *ls, char *merch_name, int amount, int price);

int cart_list_calculate_cost(cart_list_t *ls);

void cart_list_checkout();