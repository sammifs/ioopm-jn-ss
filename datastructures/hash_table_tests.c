#include <CUnit/Basic.h>
#include "hash_table.h"
#include <stdio.h>
#include <stdlib.h>

int init_suite(void)
{
    // Change this function if you want to do something *before* you
    // run a test suite
    return 0;
}
int clean_suite(void)
{
    // Change this function if you want to do something *after* you
    // run a test suite
    return 0;
}

bool compare_int_elements(elem_t a, elem_t b) { // eq_function
  return b.int_value == a.int_value;
}
int extract_int_hash_key(elem_t key)
{
  return key.int_value;
}
bool stringcomp(elem_t one, elem_t two) {
    return strcmp((char *) one.ptr_value, (char *) two.ptr_value) == 0;
}
void ht_create_destroy() {
    hash_table_t *ht = hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);

    CU_ASSERT_PTR_NOT_NULL(ht);
    hash_table_destroy(ht);
}

void ht_insert_lookup() {
    hash_table_t *ht = hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);

    // Test looking for nonexistant key
    bool success = false;
    hash_table_lookup(ht, int_elem(5), &success);
    CU_ASSERT_FALSE(success);

    hash_table_insert(ht, int_elem(5), ptr_elem("hello"));
    CU_ASSERT_STRING_EQUAL("hello", hash_table_lookup(ht, int_elem(5), &success).ptr_value);
    CU_ASSERT_TRUE(success);

    hash_table_destroy(ht);
}

void ht_insert_already_in_use_key() {
    hash_table_t *ht = hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);
    hash_table_insert(ht, int_elem(2), ptr_elem("test"));
    hash_table_insert(ht, int_elem(2), ptr_elem("overwritten"));

    bool success;
    CU_ASSERT_STRING_EQUAL("overwritten", hash_table_lookup(ht, int_elem(2), &success).ptr_value);
    CU_ASSERT_TRUE(success);

    hash_table_destroy(ht);
}

void ht_insert_lookup_invalid_key() {
    hash_table_t *ht = hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);
    hash_table_insert(ht, int_elem(-125), ptr_elem("test"));

    bool success;
    CU_ASSERT_PTR_NULL(hash_table_lookup(ht, int_elem(-125), &success).ptr_value);
    CU_ASSERT_FALSE(success);

    hash_table_destroy(ht);
}

void ht_remove() {
    hash_table_t *ht = hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);
    hash_table_insert(ht, int_elem(5), ptr_elem("hello"));

    bool success;
    CU_ASSERT_STRING_EQUAL("hello", hash_table_remove(ht, int_elem(5), &success).ptr_value);
    CU_ASSERT_TRUE(success);

    hash_table_destroy(ht);
}

void ht_remove_non_existing() {
    hash_table_t *ht = hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);

    bool success;
    CU_ASSERT_PTR_NULL(hash_table_remove(ht, int_elem(5), &success).ptr_value);
    CU_ASSERT_FALSE(success);

    hash_table_destroy(ht);
}

void ht_remove_invalid_key() {
    hash_table_t *ht = hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);

    bool success;
    
    CU_ASSERT_PTR_NULL(hash_table_remove(ht, int_elem(-6005), &success).ptr_value);
    CU_ASSERT_FALSE(success);

    hash_table_destroy(ht);
}

void ht_size_empty_ht() {
    hash_table_t *ht = hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);

    CU_ASSERT_EQUAL(0, hash_table_size(ht));

    hash_table_destroy(ht);
}

void ht_size_after_overwrite() {
    hash_table_t *ht = hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);

    hash_table_insert(ht, int_elem(5), ptr_elem("Foo"));
    hash_table_insert(ht, int_elem(5), ptr_elem("Bar"));
    CU_ASSERT_EQUAL(1, hash_table_size(ht));

    hash_table_destroy(ht);
}

void ht_size_stress() {
    hash_table_t *ht = hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);

    hash_table_insert(ht, int_elem(16), ptr_elem("Foo"));
    hash_table_insert(ht, int_elem(5), ptr_elem("Bar"));
    hash_table_insert(ht, int_elem(0), ptr_elem("Baz"));
    hash_table_insert(ht, int_elem(22), ptr_elem("Foo"));
    hash_table_insert(ht, int_elem(34), ptr_elem("Bar"));

    bool success;
    hash_table_remove(ht, int_elem(5), &success);
    hash_table_remove(ht, int_elem(34), &success);

    CU_ASSERT_EQUAL(3, hash_table_size(ht));

    hash_table_destroy(ht);
}

void ht_clear() {
    hash_table_t *ht = hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);

    hash_table_insert(ht, int_elem(16), ptr_elem("Foo"));
    hash_table_insert(ht, int_elem(5), ptr_elem("Bar"));
    hash_table_insert(ht, int_elem(0), ptr_elem("Baz"));
    hash_table_insert(ht, int_elem(22), ptr_elem("Foo"));
    hash_table_insert(ht, int_elem(34), ptr_elem("Bar"));

    hash_table_clear(ht);
    CU_ASSERT_EQUAL(0, hash_table_size(ht));

    bool success;
    CU_ASSERT_PTR_NULL(hash_table_lookup(ht, int_elem(22), &success).ptr_value);
    CU_ASSERT_FALSE(success);

    hash_table_destroy(ht);
}

void ht_keys() {
    hash_table_t *ht = hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);

    int keys[5] = { 3, 10, 42, 0, 99 };
    bool found[5] = { false };
    hash_table_insert(ht, int_elem(99), ptr_elem("Foo"));
    hash_table_insert(ht, int_elem(0), ptr_elem("Bar"));
    hash_table_insert(ht, int_elem(42), ptr_elem("Baz"));
    hash_table_insert(ht, int_elem(10), ptr_elem("Foo"));
    hash_table_insert(ht, int_elem(3), ptr_elem("Bar"));

    
    list_t *returned_keys = hash_table_keys(ht);
    list_iterator_t *iter = list_iterator(returned_keys);
    
    for (int i=0; i<5; i++) {
        // If hash_table_size(ht) isnt 5 something is very wrong
        iterator_reset(iter);
        for (int j=0; j<hash_table_size(ht); j++) {
            if (compare_int_elements(int_elem(keys[i]),iterator_next(iter))) { found[i] = true; break; } 
        }
    }
    
    for (int i=0; i<5; i++) {
        CU_ASSERT_TRUE(found[i]);
    }
    linked_list_destroy(returned_keys);
    iterator_destroy(iter);
    hash_table_destroy(ht);
}

void ht_keys_empty() {
    hash_table_t *ht = hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);
    list_t *returned_keys = hash_table_keys(ht);
    CU_ASSERT_PTR_NULL(linked_list_first(returned_keys));

    linked_list_destroy(returned_keys);
    hash_table_destroy(ht);
}

void ht_values() {
    hash_table_t *ht = hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);

    char *values[5] = { "Foo", "Bar", "Baz", "Boo", "Dar" };
    bool found[5] = { false };

    hash_table_insert(ht, int_elem(99), ptr_elem("Foo"));
    hash_table_insert(ht, int_elem(0), ptr_elem("Bar"));
    hash_table_insert(ht, int_elem(42), ptr_elem("Baz"));
    hash_table_insert(ht, int_elem(10), ptr_elem("Boo"));
    hash_table_insert(ht, int_elem(3),ptr_elem( "Dar"));

    list_t *returned_values = hash_table_values(ht);
    list_iterator_t *value_iter = list_iterator(returned_values);
    for (int i=0; i<5; i++) {
        // If hash_table_size(ht) isnt 5 something is very wrong
        iterator_reset(value_iter);
        for (int j=0; j<hash_table_size(ht); j++) {
            if (stringcomp(ptr_elem(values[i]),iterator_next(value_iter))) { found[i] = true; break; } 
        }
    }
    
    for (int i=0; i<5; i++) {
        CU_ASSERT_TRUE(found[i]);
    }
    linked_list_destroy(returned_values);
    iterator_destroy(value_iter);
    hash_table_destroy(ht);
}

void ht_values_empty() {
    hash_table_t *ht = hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);
    list_t *returned_values = hash_table_values(ht);
    CU_ASSERT_PTR_NULL(linked_list_first(returned_values));

    linked_list_destroy(returned_values);
    hash_table_destroy(ht);
}

void ht_keysvalues() {
    hash_table_t *ht = hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);

    int keys[5] = { 3, 10, 42, 0, 99 };
    char *values[5] = { "three", "ten", "fortytwo", "zero", "ninetynine" };
    bool found[5] = { false };

    for (int i=0; i<5; i++) {
        hash_table_insert(ht, int_elem(keys[i]), ptr_elem(values[i]));
    }

    list_t *returned_keys = hash_table_keys(ht);
    list_t *returned_values = hash_table_values(ht);

    list_iterator_t *key_iter = list_iterator(returned_keys);
    list_iterator_t *value_iter = list_iterator(returned_values);

    for (int i=0; i<5; i++) {
        // If hash_table_size(ht) isnt 5 something is very wrong
        iterator_reset(key_iter);
        iterator_reset(value_iter);
        for (int j=0; j<hash_table_size(ht); j++) {
            // Index j in the returned list has to return the same as index i in the original.
            // Logical & to MAKE SURE BOTH iterator_next() execute.
            if (compare_int_elements(int_elem(keys[i]),iterator_next(key_iter)) &
             stringcomp(ptr_elem(values[i]),iterator_next(value_iter))) { 
                found[i] = true; 
                break; 
            }
        }
    }

    for (int i=0; i<5; i++) {
        CU_ASSERT_TRUE(found[i]);
    }
    linked_list_destroy(returned_keys);
    linked_list_destroy(returned_values);
    iterator_destroy(key_iter);
    iterator_destroy(value_iter);
    hash_table_destroy(ht);
}

void ht_has_key() {
    hash_table_t *ht = hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);

    hash_table_insert(ht, int_elem(5), ptr_elem("Foo"));

    CU_ASSERT_TRUE(hash_table_has_key(ht, int_elem(5)));
    hash_table_destroy(ht);
}

void ht_has_key_nonexistant() {
    hash_table_t *ht = hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);

    CU_ASSERT_FALSE(hash_table_has_key(ht, int_elem(5)));
    hash_table_destroy(ht);
}

void ht_has_key_invalid_search() {
    hash_table_t *ht = hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);

    CU_ASSERT_FALSE(hash_table_has_key(ht, int_elem(-1244)));
    hash_table_destroy(ht);
}

void ht_has_value() {
    hash_table_t *ht = hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);

    hash_table_insert(ht, int_elem(5), ptr_elem("Foo"));

    CU_ASSERT_TRUE(hash_table_has_value(ht, ptr_elem("Foo")));
    hash_table_destroy(ht);
}

void ht_has_value_aliasing() {
    hash_table_t *ht = hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);

    elem_t word = ptr_elem("Foo");
    hash_table_insert(ht, int_elem(5), word);
    CU_ASSERT_TRUE(hash_table_has_value(ht, word));

    hash_table_destroy(ht);
}

bool string_contains(elem_t key_ignore, elem_t value, void *arg) { // predicate
    char *lookup = arg;

    for (int i=0; i<strlen(value.ptr_value); i++) {
        if (((char *)value.ptr_value)[i] == *lookup) { return true; }
    }
    return false;
}
void ht_all() {
    hash_table_t *ht = hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);

    int keys[5] = { 3, 10, 42, 0, 99 };
    char *values[5] = { "three", "ten", "fortytwo", "zerot", "ninetynine" };

    for (int i=0; i<5; i++) {
        hash_table_insert(ht, int_elem(keys[i]), ptr_elem(values[i]));
    }

    char equal = 'e';
    CU_ASSERT_FALSE(hash_table_all(ht, string_contains, &equal));

    equal = 't';
    CU_ASSERT_TRUE(hash_table_all(ht, string_contains, &equal));

    hash_table_destroy(ht);
}

void ht_all_empty() {
    hash_table_t *ht = hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);

    char equal = 'e';
    CU_ASSERT_FALSE(hash_table_all(ht, string_contains, &equal));

    hash_table_destroy(ht);
}

bool key_equal(elem_t key, elem_t value_ignore, void *arg) { // predicate
    int *other_ptr = arg;
    return key.int_value == *other_ptr;
}
void ht_any() {
    hash_table_t *ht = hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);

    int keys[5] = { 3, 10, 42, 0, 99 };
    char *values[5] = { "three", "ten", "fortytwo", "zero", "ninetynine" };

    for (int i=0; i<5; i++) {
        hash_table_insert(ht, int_elem(keys[i]), ptr_elem(values[i]));
    }
    int equal = 10;
    CU_ASSERT_FALSE(hash_table_any(ht, key_equal, &equal));

    equal = 99;
    CU_ASSERT_TRUE(hash_table_any(ht, key_equal, &equal));

    hash_table_destroy(ht);
}

void ht_any_empty() {
    hash_table_t *ht = hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);

    int equal = 10;
    CU_ASSERT_FALSE(hash_table_any(ht, key_equal, &equal));

    hash_table_destroy(ht);
}

void pointer_move(elem_t key_ignore, elem_t *value, void *arg) { // apply_function
    value->ptr_value = value->ptr_value + 1;
}
void ht_apply_all() {
    hash_table_t *ht = hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);

    int keys[5] = { 3, 10, 42, 0, 99 };
    char *values[5] = { "three", "ten", "fortytwo", "tzero", "tnineynine" };

    for (int i=0; i<5; i++) {
        hash_table_insert(ht, int_elem(keys[i]), ptr_elem(values[i]));
    }

    char t = 't';
    CU_ASSERT_TRUE(hash_table_all(ht, string_contains, &t));
    hash_table_apply_to_all(ht, pointer_move, &t);
    CU_ASSERT_FALSE(hash_table_all(ht, string_contains, &t));

    hash_table_destroy(ht);
}

void ht_apply_all_empty() {
    hash_table_t *ht = hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);
    char t = 't';
    CU_ASSERT_FALSE(hash_table_all(ht, string_contains, &t));
    hash_table_apply_to_all(ht, pointer_move, &t);
    CU_ASSERT_FALSE(hash_table_all(ht, string_contains, &t));

    hash_table_destroy(ht);
}

int main()
{
    // First we try to set up CUnit, and exit if we fail
    if (CU_initialize_registry() != CUE_SUCCESS)
        return CU_get_error();
    // We then create an empty test suite and specify the name and
    // the init and cleanup functions
    CU_pSuite hash_table = CU_add_suite("Hash table tests", init_suite,
                                           clean_suite);
    if (hash_table == NULL)
    {
        // If the test suite could not be added, tear down CUnit and exit
        CU_cleanup_registry();
        return CU_get_error();
    }
    // This is where we add the test functions to our test suite.
    // For each call to CU_add_test we specify the test suite, the
    // name or description of the test, and the function that runs
    // the test in question. If you want to add another test, just
    // copy a line below and change the information
    if (
        (CU_add_test(hash_table, "hash_table_create & hash_table_destroy", ht_create_destroy) == NULL) ||
        (CU_add_test(hash_table, "hash_table_insert & hash_table_lookup", ht_insert_lookup) == NULL) ||
        (CU_add_test(hash_table, "hash_table_insert with already in use key", ht_insert_already_in_use_key) == NULL) ||
        (CU_add_test(hash_table, "hash_table_insert & hash_table_lookup with negative value", ht_insert_lookup_invalid_key) == NULL) ||
        (CU_add_test(hash_table, "hash_table_remove", ht_remove) == NULL) ||
        (CU_add_test(hash_table, "hash_table_remove with negative value", ht_remove_invalid_key) == NULL) ||
        (CU_add_test(hash_table, "hash_table_remove before any insert", ht_remove_non_existing) == NULL) ||
        (CU_add_test(hash_table, "hash_table_size on empty ht", ht_size_empty_ht) == NULL) ||
        (CU_add_test(hash_table, "hash_table_size after overwritten entry", ht_size_after_overwrite) == NULL) ||
        (CU_add_test(hash_table, "hash_table_size stress test", ht_size_stress) == NULL) ||
        (CU_add_test(hash_table, "hash_table_clear", ht_clear) == NULL) ||
        (CU_add_test(hash_table, "hash_table_keys", ht_keys) == NULL) ||
        (CU_add_test(hash_table, "hash_table_keys on empty ht", ht_keys_empty) == NULL) ||
        (CU_add_test(hash_table, "hash_table_values", ht_values) == NULL) || 
        (CU_add_test(hash_table, "hash_table_values on empty ht", ht_values_empty) == NULL) || 
        (CU_add_test(hash_table, "hash_table_keys & hash_table_values, check if order is maintained between", ht_keysvalues) == NULL) ||
        (CU_add_test(hash_table, "hash_table_has_key", ht_has_key) == NULL) ||
        (CU_add_test(hash_table, "hash_table_has_key on empty ht", ht_has_key_nonexistant) == NULL) ||
        (CU_add_test(hash_table, "hash_table_has_key, with invalid negative search term", ht_has_key_invalid_search) == NULL) ||
        (CU_add_test(hash_table, "hash_table_has_value", ht_has_value) == NULL) ||
        (CU_add_test(hash_table, "hash_table_has_value with alias", ht_has_value_aliasing) == NULL) ||
        (CU_add_test(hash_table, "hash_table_apply_to_all", ht_apply_all) == NULL) ||
        (CU_add_test(hash_table, "hash_table_apply_to_all on empty ht", ht_apply_all_empty) == NULL) ||
        0)
    {
        // If adding any of the tests fails, we tear down CUnit and exit
        CU_cleanup_registry();
        return CU_get_error();
    }
    // Set the running mode. Use CU_BRM_VERBOSE for maximum output.
    // Use CU_BRM_NORMAL to only print errors and a summary
    CU_basic_set_mode(CU_BRM_VERBOSE);
    // This is where the tests are actually run!
    CU_basic_run_tests();
    // Tear down CUnit before exiting
    CU_cleanup_registry();
    return CU_get_error();
}