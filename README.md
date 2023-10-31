# Introduction
Written by Samuel Sverker, Jonathan Näslund.

Hash table comes from Samuel's Assignment 1.
Linked list comes from Jonathan's Assignment 1.
Utils comes from Jonathan's bootstrap labs.


# Responsibility
The program does not take responsibility of any char * that was NOT successfully inserted. Either with ioopm_store_add_merch, ioopm_store_edit_merch, ioopm_store_replenish_merch, ioopm_store_add_to_cart, and ioopm_store_remove_from_cart. If any of these functions returns an error code (negative integer) the char * will NOT be freed upon ioopm_store_destroy. As it doesn't exist within the ioopm_store_t.

# How to run
To build the program and run its tests, write "make build_store_test" at the directory of this README and ./build_store_test there after. 
To build the program without running the tests, write "make event_loop" and then ./event_loop.
To build the program and run its tests with valgrind, write "make mem_store_test".
To run all .c files, except files from "datastructures", with gcov, write "make gcov_tests"

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
This code coverage has been gathered with help of gcov:
ioopm_store.c: 95.29%
merch_hash_table.c: 98.73%
cart_hash_table.c: 97.50%
shelf_list.c: 96.51%
utils.c: 21.13%


