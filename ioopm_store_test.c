#include <CUnit/Basic.h>
#include "ioopm_store.h"

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


void test_store_create_destroy() {
    ioopm_store_t *store = ioopm_store_create();

    CU_ASSERT_PTR_NOT_NULL(store);

    ioopm_store_destroy(store);
}

void test_add_merch(void)
{   
    ioopm_store_t *store = ioopm_store_create();

    ioopm_store_add_merch(store, strdup("Ost"), strdup("Mat"), 20);

    CU_ASSERT_TRUE(ioopm_store_has_merch(store, "Ost"));

    ioopm_store_destroy(store);
}

void test_has_merch(void)
{
    ioopm_store_t *store = ioopm_store_create();

    ioopm_store_add_merch(store, strdup("Ost"), strdup("Name"), 20);

    CU_ASSERT_FALSE(ioopm_store_has_merch(store, "BORD"));
    CU_ASSERT_TRUE(ioopm_store_has_merch(store, "Ost"));

    ioopm_store_destroy(store);
}

void test_delete_merch(void)
{
    ioopm_store_t *store = ioopm_store_create();
    
    // Test delete merch on an empty warehouse
    CU_ASSERT_FALSE(ioopm_store_delete_merch(store, "Ost"));


    // Test delete merch on an existing merch
    ioopm_store_add_merch(store, strdup("Ost"), strdup("Mat"), 20);
    CU_ASSERT_TRUE(ioopm_store_delete_merch(store, "Ost"));

    // Test delet merch on a resently deleted merch
    CU_ASSERT_FALSE(ioopm_store_delete_merch(store, "Ost"));

    ioopm_store_destroy(store);
}

void test_edit_merch() {
    ioopm_store_t *store = ioopm_store_create();

    ioopm_store_add_merch(store, strdup("Ost"), strdup("Desc"), 20);
    CU_ASSERT_TRUE(ioopm_store_has_merch(store, "Ost"));

    ioopm_store_edit_merch(store, "Ost", strdup("Bord"), strdup("Möbel"), 240);

    CU_ASSERT_FALSE(ioopm_store_has_merch(store, "Ost"));
    CU_ASSERT_TRUE(ioopm_store_has_merch(store, "Bord"));

    ioopm_store_destroy(store);
}

void test_edit_nonexisting_merch() {
    ioopm_store_t *store = ioopm_store_create();

    CU_ASSERT_EQUAL(-1, ioopm_store_edit_merch(store, "Ost", "Bord", "Möbel", 240));

    ioopm_store_destroy(store);
}

void test_edit_merch_to_already_existing_name() {
    ioopm_store_t *store = ioopm_store_create();

    ioopm_store_add_merch(store, strdup("Ost"), strdup("Mat"), 20);
    ioopm_store_add_merch(store, strdup("Bord"), strdup("Möbel"), 20);

    CU_ASSERT_EQUAL(-2, ioopm_store_edit_merch(store, "Ost", "Bord", "SDF", 152));

    ioopm_store_destroy(store);
}

void test_replenish_of_self_owned_shelf(void)
{
    ioopm_store_t *store = ioopm_store_create();
    
    ioopm_store_add_merch(store, strdup("Ost"), strdup("Mat"), 109); 
    ioopm_store_add_merch(store, strdup("Korv"), strdup("Mat"), 59); 

    // Create a new shelfs
    CU_ASSERT_EQUAL(0, ioopm_store_replenish_stock(store, "Ost", strdup("G17"), 100));
 

    // Replenish the first 
    CU_ASSERT_EQUAL(1, ioopm_store_replenish_stock(store, "Ost", "G17", 50));

    ioopm_store_destroy(store);
    
}

void test_replenish_already_owned_shelf() {
    ioopm_store_t *store = ioopm_store_create();

    ioopm_store_add_merch(store, strdup("Ost"), strdup("Mat"), 20); 
    ioopm_store_add_merch(store, strdup("Bord"), strdup("Möbel"), 150);

    CU_ASSERT_EQUAL(0, ioopm_store_replenish_stock(store, "Ost", strdup("A34"), 125));
    
    CU_ASSERT_EQUAL(-2, ioopm_store_replenish_stock(store, "Bord", "A34", 150));

    ioopm_store_destroy(store);
}

void test_replenish_not_found_item(void)
{
    ioopm_store_t *store = ioopm_store_create();

    CU_ASSERT_EQUAL(-1, ioopm_store_replenish_stock(store, "Ost", "A34", 125));


    ioopm_store_add_merch(store, strdup("Ost"), strdup("Mat"), 20); 
    ioopm_store_add_merch(store, strdup("Bord"), strdup("Möbel"), 150);

    CU_ASSERT_EQUAL(-1, ioopm_store_replenish_stock(store, "Korv", "A34", 125));

    ioopm_store_destroy(store);
}

void test_replenish_on_deleted_shelf() {
    ioopm_store_t *store = ioopm_store_create();

    ioopm_store_add_merch(store, strdup("Ost"), strdup("Mat"), 20); 
    ioopm_store_add_merch(store, strdup("Bord"), strdup("Möbel"), 150);

    CU_ASSERT_EQUAL(0, ioopm_store_replenish_stock(store, "Ost", strdup("A34"), 150));

    CU_ASSERT_TRUE(ioopm_store_delete_merch(store, "Ost"));

    CU_ASSERT_EQUAL(0, ioopm_store_replenish_stock(store, "Bord", strdup("A34"), 10));

    ioopm_store_destroy(store);
}


int main()
{
    // First we try to set up CUnit, and exit if we fail
    if (CU_initialize_registry() != CUE_SUCCESS)
        return CU_get_error();
    // We then create an empty test suite and specify the name and
    // the init and cleanup functions
    CU_pSuite my_test_suite = CU_add_suite("My awesome test suite", init_suite,
                                           clean_suite);
    if (my_test_suite == NULL)
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
        (CU_add_test(my_test_suite, "create and destroy ioopm_store_t", test_store_create_destroy) == NULL) ||
        (CU_add_test(my_test_suite, "ioopm_store_add_merch", test_add_merch) == NULL) ||
        (CU_add_test(my_test_suite, "ioopm_store_delete_merch", test_delete_merch) == NULL) ||
        (CU_add_test(my_test_suite, "ioopm_store_has_merch", test_has_merch) == NULL) ||
        (CU_add_test(my_test_suite, "ioopm_store_edit_merch", test_edit_merch) == NULL) ||
        (CU_add_test(my_test_suite, "ioopm_store_edit_merch for nonexisting merch", test_edit_nonexisting_merch) == NULL) ||
        (CU_add_test(my_test_suite, "ioopm_store_edit_merch to already existing name", test_edit_merch_to_already_existing_name) == NULL) ||
        (CU_add_test(my_test_suite, "ioopm_store_replenish_merch to shelf owned by right merch", test_replenish_of_self_owned_shelf) == NULL) ||
        (CU_add_test(my_test_suite, "ioopm_store_replenish_merch to shelf owned by other merch", test_replenish_already_owned_shelf) == NULL) ||
        (CU_add_test(my_test_suite, "ioopm_store_replenish_merch to a merch not found in the warehouse", test_replenish_not_found_item) == NULL) ||
        (CU_add_test(my_test_suite, "ioopm_store_replenish_merch to a shelf that was just deleted by ioopm_store_delete_merch", test_replenish_on_deleted_shelf) == NULL) ||
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