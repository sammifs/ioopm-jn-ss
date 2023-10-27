#include "cart_hash_table.h"


struct order {
    char *merch_name;
    int amount;
    int price;
    order_t *next;
};

order_t *order_create(char *name, int amount, int price, order_t *next) {
    order_t *result = calloc(1, sizeof(order_t));

    result->merch_name = name;
    result->amount = amount;
    result->price = price;
    result->next = next;

    return result;
}

void order_destroy(order_t *order) {
    // TODO : Should order_t be responsible for order->merch_name??
    free(order->merch_name);
    free(order);
}

struct cart {
    order_t *first;
    size_t size;
};

cart_t *cart_create() {
    cart_t *result = calloc(1, sizeof(cart_t));

    result->first = NULL;
    result->size = 0;

    return result;
}

void cart_destroy(elem_t key, elem_t *value, void *arg) {
    cart_t *cart = (*value).ptr_value;
    order_t *current = cart->first;
    while (current != NULL) {
        order_t *tmp = current->next;
        order_destroy(current);
        current = tmp;
    }
    free(cart);
}

bool cart_is_empty(cart_t *cart) {
    return cart->size == 0;
}

void cart_append(cart_t *cart, char *name, int amount, int price) {
    if (cart_is_empty(cart)) {
        cart->first = order_create(name, amount, price, NULL);
        cart->size++;
    }
    else {
        order_t *current = cart->first;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = order_create(name, amount, price, NULL);
        cart->size++;
    }
}

bool cart_remove_order_with_merch(cart_t *cart, char* merch_name) {
    order_t *previous = cart->first;
    if (previous == NULL) { return false; }
    if (strcmp(previous->merch_name, merch_name) == 0) {
        cart->first = previous->next;
        order_destroy(previous);
        return true;
    }
    order_t *current = previous->next;
    while (current != NULL) {
        if (strcmp(current->merch_name, merch_name) == 0) {
            previous->next = current->next;
            order_destroy(current);
            return true;
        }
    }
    return false;
}

int cart_calculate_cost(cart_t *cart) {
    int cost = 0;
    order_t *order = cart->first;
    while (order) {
        cost += order->amount * order->price;
        order = order->next;
    }
    return cost;
}


cart_hash_table_t *cart_hash_table_create() {
    // int -> cart_t*
    // Non-generic hashtable.
    cart_hash_table_t *ht = hash_table_create(elem_t_to_int, compare_int, NULL);

    return ht;
}

void cart_hash_table_destroy(cart_hash_table_t *ht) {
    // TODO : Tänk över ägarskap för strdups inuti.
    hash_table_apply_to_all(ht, cart_destroy, NULL);
    hash_table_destroy(ht);
}

// TODO : Tänk över detta, se om det stämmer.
// We should never have to check for collisons due to
// the overarching structure in ioopm_store_t, two carts
// CANNOT have the same name.
void cart_hash_table_insert(cart_hash_table_t *ht, int cart_index) {
    cart_t *cart = cart_create();

    hash_table_insert(ht, int_elem(cart_index), ptr_elem(cart));
}

cart_t *cart_hash_table_lookup(cart_hash_table_t *ht, int cart_index, bool *success) {
    return hash_table_lookup(ht, int_elem(cart_index), success).ptr_value;
}

bool cart_hash_table_remove(cart_hash_table_t *ht, int cart_index) {
    bool success;
    elem_t cart = hash_table_remove(ht, int_elem(cart_index), &success);
    if (success) {
        cart_destroy(ptr_elem(NULL), &cart, NULL);
        return true;
    }
    else {
        // We did not find the given cart_index, return false.
        return false;
    }
}

bool cart_hash_table_append_order(cart_hash_table_t *ht, int cart_index, char *merch_name, int amount, int price) {
    bool success;
    cart_t *cart = cart_hash_table_lookup(ht, cart_index, &success);
    if (success) {
        cart_append(cart, merch_name, amount, price);
        return true;
    }
    else {
        // We did not find the given cart_index, return false.
        return false;
    }
}

int cart_hash_table_calculate_cost(cart_hash_table_t *ht, int cart_index, bool *success) {
    cart_t *cart = cart_hash_table_lookup(ht, cart_index, success);

    if (*success) {
        return cart_calculate_cost(cart);
    }
    else {
        // We did not find the given cart_index, *success has already been set to false in
        // cart_hash_table_lookup, we return 0 but this value should never be read.
        return 0;
    }
}

int cart_hash_table_order_amount_for_merch(cart_hash_table_t *ht, char *merch_name) {
    list_t *ls = hash_table_values(ht);
    list_iterator_t *iter = list_iterator(ls);

    int amount = 0;
    for (int i=0; iterator_has_next(iter); i++) {
        order_t *order = ((cart_t *) iterator_next(iter).ptr_value)->first;
        while (order != NULL) {
            if (strcmp(order->merch_name, merch_name) == 0) {
                amount += order->amount;
            }
            order = order->next;
        }
    }
    iterator_destroy(iter);
    linked_list_destroy(ls);
    return amount;
}

void carts_hash_table_remove_orders(cart_hash_table_t *ht, char *merch_name) {
    list_t *ls = hash_table_values(ht);
    list_iterator_t *iter = list_iterator(ls);

    while (iterator_has_next(iter)) {
        cart_t *cart = iterator_next(iter).ptr_value;
        while (cart_remove_order_with_merch(cart, merch_name));
    }
    iterator_destroy(iter);
    linked_list_destroy(ls);
}

order_t *cart_get_first_order(cart_t *cart) {
    return cart->first;
}

order_t *cart_get_next_order(order_t *order) {
    return order->next;
}

int order_get_amount(order_t *order) {
    return order->amount;
}

char *order_get_merch(order_t *order) {
    return order->merch_name;
}