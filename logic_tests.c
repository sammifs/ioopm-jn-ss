#include <CUnit/Basic.h>
#include "logic.h"
#include "utils.h"
#include "hash_table.h"

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
// These are example test functions. You should replace them with
// functions of your own.
void test_add_merch(void)
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(string_to_int, compare_str, NULL);

    elem_t item = merch_create(ht, str_elem("Ost"), "Mat", 19);
    bool success;
    CU_ASSERT_PTR_NOT_NULL(ioopm_hash_table_lookup(ht, str_elem("Ost"), &success).merch_ptr);

    CU_ASSERT_EQUAL(1, ioopm_hash_table_size(ht));

    CU_ASSERT_TRUE(name_exists(ht, str_elem("Ost")));

    delete_merch(ht, item);
    ioopm_hash_table_destroy(ht);
}

void test_get_desc(void)
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(string_to_int, compare_str, NULL);
    bool success;

    CU_ASSERT_PTR_NULL(get_desc(ht, str_elem("Ost"), &success));
    CU_ASSERT_FALSE(success);

    merch_create(ht, str_elem("Ost"), "Mat", 19);
    merch_create(ht, str_elem("Korv"), "Godare mat", 44);
    merch_create(ht, str_elem("Fisk"), "Helt och hållet MUMS", 500);

    CU_ASSERT_EQUAL(0, strcmp(get_desc(ht, str_elem("Ost"), &success), "Mat"));
    CU_ASSERT_TRUE(success);
    CU_ASSERT_EQUAL(0, strcmp(get_desc(ht, str_elem("Korv"), &success), "Godare mat"));
    CU_ASSERT_TRUE(success);
    CU_ASSERT_EQUAL(0, strcmp(get_desc(ht, str_elem("Fisk"), &success), "Helt och hållet MUMS"));
    CU_ASSERT_TRUE(success);

    delete_all_items(ht);
    ioopm_hash_table_destroy(ht);
}

void test_get_price(void)
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(string_to_int, compare_str, NULL);
    bool success;

    CU_ASSERT_EQUAL(0, get_price(ht, str_elem("Ost"), &success));
    CU_ASSERT_FALSE(success);

    merch_create(ht, str_elem("Ost"), "Mat", 19);
    merch_create(ht, str_elem("Korv"), "Godare mat", 44);
    merch_create(ht, str_elem("Fisk"), "Helt och hållet MUMS", 500);

    CU_ASSERT_EQUAL(19, get_price(ht, str_elem("Ost"), &success));
    CU_ASSERT_TRUE(success);
    CU_ASSERT_EQUAL(44, get_price(ht, str_elem("Korv"), &success));
    CU_ASSERT_TRUE(success);
    CU_ASSERT_EQUAL(500, get_price(ht, str_elem("Fisk"), &success));
    CU_ASSERT_TRUE(success);
    
    delete_all_items(ht);
    ioopm_hash_table_destroy(ht);
}

void test_delete_all_items(void)
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(string_to_int, compare_str, NULL);
    bool success;

    delete_all_items(ht);

    CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 0);

    merch_create(ht, str_elem("Ost"), "Mat", 19);
    merch_create(ht, str_elem("Korv"), "Mat", 44);
    merch_create(ht, str_elem("Fisk"), "Mat", 500);

    delete_all_items(ht);

    ioopm_hash_table_lookup(ht, str_elem("Ost"), &success);
    CU_ASSERT_FALSE(success)

    CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 0);

    ioopm_hash_table_destroy(ht);
}

void test_name_exists(void)
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(string_to_int, compare_str, NULL);

    CU_ASSERT_FALSE(name_exists(ht, str_elem("Ost")));

    merch_create(ht, str_elem("Ost"), "Mat", 19);
    merch_create(ht, str_elem("Korv"), "Mat", 44);
    merch_create(ht, str_elem("Fisk"), "Mat", 500);

    CU_ASSERT_TRUE(name_exists(ht, str_elem("Ost")));
    CU_ASSERT_TRUE(name_exists(ht, str_elem("Korv")));
    CU_ASSERT_TRUE(name_exists(ht, str_elem("Fisk")));

    delete_all_items(ht);
    ioopm_hash_table_destroy(ht);
}

void test_list_merch(void) 
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(string_to_int, compare_str, NULL);
    int zero = 0;
    bool list_empty = list_merch(ht, 20, 0, &zero);
    CU_ASSERT_FALSE(list_empty);

    merch_create(ht, str_elem("Ost"), "Mat", 19);
    merch_create(ht, str_elem("Korv"), "Mat", 44);
    merch_create(ht, str_elem("Fisk"), "Mat", 500);
    bool under_twenty = list_merch(ht, 20, 1, &zero);
    CU_ASSERT_FALSE(under_twenty);

    merch_create(ht, str_elem("Apelsin"), "Mat", 19);
    merch_create(ht, str_elem("Potatis"), "Mat", 44);
    merch_create(ht, str_elem("Banan"), "Mat", 500);
    merch_create(ht, str_elem("Kiwi"), "Mat", 19);
    merch_create(ht, str_elem("Blodbudding"), "Mat", 44);
    merch_create(ht, str_elem("Kyckling"), "Mat", 500);
    merch_create(ht, str_elem("Flingor"), "Mat", 19);
    merch_create(ht, str_elem("Paprika"), "Mat", 44);
    merch_create(ht, str_elem("Toapapper"), "Mat", 500);
    merch_create(ht, str_elem("Papper"), "Mat", 19);
    merch_create(ht, str_elem("Godis"), "Mat", 44);
    merch_create(ht, str_elem("Pasta"), "Mat", 500);
    merch_create(ht, str_elem("Ris"), "Mat", 19);
    merch_create(ht, str_elem("Paj"), "Mat", 44);
    merch_create(ht, str_elem("Kaka"), "Mat", 500);
    merch_create(ht, str_elem("Chips"), "Mat", 19);
    merch_create(ht, str_elem("Gurka"), "Mat", 44);
    merch_create(ht, str_elem("Salt"), "Mat", 500);
    
    bool over_twenty = list_merch(ht, 20, 21, &zero);
    CU_ASSERT_TRUE(over_twenty);
    int twenty = 20;
    over_twenty = list_merch(ht, 40, 21, &twenty);
    CU_ASSERT_FALSE(over_twenty);

    delete_all_items(ht);
    ioopm_hash_table_destroy(ht);
}

void test_delete_merch(void) 
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(string_to_int, compare_str, NULL);

    CU_ASSERT_FALSE(delete_merch(ht, str_elem("Ost")));

    merch_create(ht, str_elem("Ost"), "Mat", 19);
    
    CU_ASSERT_TRUE(name_exists(ht, str_elem("Ost")));
    
    bool success;
    delete_merch(ht, str_elem("Ost"));

    ioopm_hash_table_lookup(ht, str_elem("Ost"), &success);
    CU_ASSERT_FALSE(success);

    ioopm_hash_table_destroy(ht);
}

void test_change_name(void) 
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(string_to_int, compare_str, NULL);
    
    merch_create(ht, str_elem("Ost"), "Mat", 19);
    merch_create(ht, str_elem("Korv"), "Mat", 44);
    merch_create(ht, str_elem("Potatis"), "Mat", 500);

    bool existing_item = change_name(ht, "Pannkaka", &str_elem("Ost"));
    CU_ASSERT_TRUE(existing_item);

    CU_ASSERT_TRUE(name_exists(ht, str_elem("Pannkaka")));

    // Change name on an item that doesn't exist
    bool non_existing_item = change_name(ht, "Tacos", &str_elem("Bröd"));
    CU_ASSERT_FALSE(non_existing_item);


    // This will never happen since our ask_question_string won't accept an empty string
    bool change_to_empty_str = change_name(ht, "", &str_elem("Korv"));
    CU_ASSERT_TRUE(change_to_empty_str);

    delete_all_items(ht);
    ioopm_hash_table_destroy(ht);
}

void test_change_desc() {
    ioopm_hash_table_t *ht = ioopm_hash_table_create(string_to_int, compare_str, NULL);
    bool success;

    merch_create(ht, str_elem("Ost"), "Mat", 19);
    merch_create(ht, str_elem("Korv"), "Mat", 44);
    merch_create(ht, str_elem("Potatis"), "Mat", 500);

    change_desc(ht, "Hej", &str_elem("Ost"));
    change_desc(ht, "Hejsan", &str_elem("Korv"));
    change_desc(ht, "Tjena", &str_elem("Potatis"));

    CU_ASSERT_EQUAL("Hej", get_desc(ht, str_elem("Ost"), &success));
    CU_ASSERT_EQUAL("Hejsan", get_desc(ht, str_elem("Korv"), &success));
    CU_ASSERT_EQUAL("Tjena", get_desc(ht, str_elem("Potatis"), &success));

    delete_all_items(ht);
    ioopm_hash_table_destroy(ht);
}

void test_change_price() {
    ioopm_hash_table_t *ht = ioopm_hash_table_create(string_to_int, compare_str, NULL);
    bool success;
    
    merch_create(ht, str_elem("Ost"), "Mat", 19);
    merch_create(ht, str_elem("Korv"), "Mat", 44);
    merch_create(ht, str_elem("Potatis"), "Mat", 500);

    change_price(ht, 100, &str_elem("Ost"));
    change_price(ht, 200, &str_elem("Korv"));
    change_price(ht, 300, &str_elem("Potatis"));

    CU_ASSERT_EQUAL(100, get_price(ht, str_elem("Ost"), &success));
    CU_ASSERT_EQUAL(200, get_price(ht, str_elem("Korv"), &success));
    CU_ASSERT_EQUAL(300, get_price(ht, str_elem("Potatis"), &success));

    delete_all_items(ht);
    ioopm_hash_table_destroy(ht);
}

void test_replenish_stock(void)
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(string_to_int, compare_str, NULL);

    merch_create(ht, str_elem("Ost"), "Mat", 19);
    merch_create(ht, str_elem("Korv"), "Mat", 44);
    merch_create(ht, str_elem("Potatis"), "Mat", 500);

    // Replenish on a non-existing item
    CU_ASSERT_FALSE(replenish_stock(ht, &str_elem("Popcorn"), "A34", 50));

    // Create a shelf and change one stock
    CU_ASSERT_TRUE(replenish_stock(ht, &str_elem("Ost"), "A34", 50));
    CU_ASSERT_TRUE(replenish_stock(ht, &str_elem("Ost"), "A34", 100));

    // Create a second shelf
    CU_ASSERT_TRUE(replenish_stock(ht, &str_elem("Ost"), "A45", 75));
    
    // Create a shelf on a second item
    CU_ASSERT_TRUE(replenish_stock(ht, &str_elem("Ost"), "A45", 75));

    delete_all_items(ht);
    ioopm_hash_table_destroy(ht);
}

void test_show_stock(void)
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(string_to_int, compare_str, NULL);

    merch_create(ht, str_elem("Ost"), "Mat", 19);
    merch_create(ht, str_elem("Korv"), "Mat", 44);
    merch_create(ht, str_elem("Potatis"), "Mat", 500);

    // Show stock of a non-existing item
    CU_ASSERT_FALSE(show_stock(ht, str_elem("Popcorn")));

    // Show stock of an item with no shelfes
    CU_ASSERT_FALSE(show_stock(ht, str_elem("Ost")));

    replenish_stock(ht, &str_elem("Ost"), "A34", 50);
    CU_ASSERT_TRUE(show_stock(ht, str_elem("Ost")));

    delete_all_items(ht);
    ioopm_hash_table_destroy(ht);
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
        (CU_add_test(my_test_suite, "Tests for delete_all_items function", test_delete_all_items) == NULL) ||
        (CU_add_test(my_test_suite, "Tests for test_get_desc function", test_get_desc) == NULL) ||
        (CU_add_test(my_test_suite, "Tests for test_get_price function", test_get_price) == NULL) ||
        (CU_add_test(my_test_suite, "Tests for test_name_exists function", test_name_exists) == NULL) ||
        (CU_add_test(my_test_suite, "Tests for merch_create function", test_add_merch) == NULL) ||
        (CU_add_test(my_test_suite, "Tests for list_merch function", test_list_merch) == NULL) ||
        (CU_add_test(my_test_suite, "Tests for delete_merch function", test_delete_merch) == NULL) ||
        (CU_add_test(my_test_suite, "Tests for change_name function", test_change_name) == NULL) ||
        (CU_add_test(my_test_suite, "Tests for change_desc function", test_change_desc) == NULL) ||
        (CU_add_test(my_test_suite, "Tests for change_price function", test_change_price) == NULL) ||
        (CU_add_test(my_test_suite, "Tests for test_replenish_stock function", test_replenish_stock) == NULL) ||
        (CU_add_test(my_test_suite, "Tests for test_show_stock function", test_show_stock) == NULL) ||
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