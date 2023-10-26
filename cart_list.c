#include "cart_list.h"

struct cart_list {
    order_t first;
    int size;
    int i;  // Vad gör detta?
};

struct order {
    char *merch_name;
    int amount;
    int price;
    order_t *next;
};

typedef struct order order_t;

order_t *order_create(char *name, int amount, int price, order_t *next) {
    order_t *result = calloc(1, sizeof(order_t));

    result->merch_name = name;
    result->amount = amount;
    result->price = price;
    result->next = next;
}

void order_destroy(order_t *order) {
    // TODO : Should order_t be responsible for order->merch_name??
    free(order);
}

cart_list_t *cart_list_create(int index_of_cart) {
    cart_list_t *result = calloc(1, sizeof(cart_list_t));

    result->first = NULL;
    result->size = 0;
    result->i = index_of_cart;
}

void cart_list_destroy(cart_list_t *list) {
    assert(list);
    order_t *current = list->first;
    while (current != NULL) {
        order_t *tmp = current->next;
        order_destroy(current);
        current = tmp;
    }    
    free(list);
}

void cart_list_append_order(cart_list_t *list, char *merch_name, int amount, int price) {
    if (cart_list_is_empty(list)) {
        list->first = order_create(merch_name, amount, price, NULL);
        list->size++;
    }
    else {
        order_t *current = list->first;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = order_create(merch_name, amount, price, NULL);
        list->size++;
    }
}

bool cart_list_is_empty(cart_list_t *list) {
    return list->size == 0;
}

int cart_list_calculate_cost(cart_list_t *list) {
    int cost = 0;
    order_t order = list->first;
    while(order) {
        cost = order.
    }
}

void cart_list_checkout() {

}