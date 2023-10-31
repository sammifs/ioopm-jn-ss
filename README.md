# Introduction
Written by Samuel Sverker, Jonathan Näslund.

Hash table comes from Samuel's Assignment 1.
Linked list comes from Jonathan's Assignment 1.
Utils comes from Jonathan's bootstrap labs.


# Responsibility
The program does not take responsibility of any char * that was NOT successfully inserted. Either with ioopm_store_add_merch, ioopm_store_edit_merch, ioopm_store_replenish_merch, ioopm_store_add_to_cart, and ioopm_store_remove_from_cart. If any of these functions returns an error code (negative integer) the char * will NOT be freed upon ioopm_store_destroy. As it doesn't exist within the ioopm_store_t.

# How to run
To build the program and run its tests, write "make build_store_test" at the directory of this README. 
To build the program without running the tests, write "make event_loop".

Required files:
* datastructures/hash_table.h
* datastructures/linked_list.h
* datastructures/common.h
* datastructures/iterator.h
* cart_hash_table.h
* ioopm_store.h
* merch_hash_table.h
* shelf_list.h
* utils.h

# Code profile


