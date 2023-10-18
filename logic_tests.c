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

    
    merch_t *merch = merch_create(ht, str_elem("Ost"), "Mat", 19);

    CU_ASSERT_PTR_NOT_NULL(merch);

    CU_ASSERT_EQUAL(1, ioopm_hash_table_size(ht));

    CU_ASSERT_TRUE(name_exists(ht, str_elem("Ost")));

    merch_destroy(merch);
    ioopm_hash_table_destroy(ht);
}

void test_list_merch(void) 
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(string_to_int, compare_str, NULL);
    int zero = 0;
    bool list_empty = list_merch(ht, 20, 0, &zero);
    CU_ASSERT_FALSE(list_empty);

    merch_t *merge1 = merch_create(ht, str_elem("Ost"), "Mat", 19);
    merch_t *merge2 = merch_create(ht, str_elem("Korv"), "Mat", 44);
    merch_t *merge3 = merch_create(ht, str_elem("Fisk"), "Mat", 500);
    bool under_twenty = list_merch(ht, 20, 1, &zero);
    CU_ASSERT_FALSE(under_twenty);

    merch_t *merge4 = merch_create(ht, str_elem("Apelsin"), "Mat", 19);
    merch_t *merge5 = merch_create(ht, str_elem("Potatis"), "Mat", 44);
    merch_t *merge6 = merch_create(ht, str_elem("Banan"), "Mat", 500);
    merch_t *merge7 = merch_create(ht, str_elem("Kiwi"), "Mat", 19);
    merch_t *merge8 = merch_create(ht, str_elem("Blodbudding"), "Mat", 44);
    merch_t *merge9 = merch_create(ht, str_elem("Kyckling"), "Mat", 500);
    merch_t *merge10 = merch_create(ht, str_elem("Flingor"), "Mat", 19);
    merch_t *merge11 = merch_create(ht, str_elem("Paprika"), "Mat", 44);
    merch_t *merge12 = merch_create(ht, str_elem("Toapapper"), "Mat", 500);
    merch_t *merge13 = merch_create(ht, str_elem("Papper"), "Mat", 19);
    merch_t *merge14 = merch_create(ht, str_elem("Godis"), "Mat", 44);
    merch_t *merge15 = merch_create(ht, str_elem("Pasta"), "Mat", 500);
    merch_t *merge16 = merch_create(ht, str_elem("Ris"), "Mat", 19);
    merch_t *merge17 = merch_create(ht, str_elem("Paj"), "Mat", 44);
    merch_t *merge18 = merch_create(ht, str_elem("Kaka"), "Mat", 500);
    merch_t *merge19 = merch_create(ht, str_elem("Chips"), "Mat", 19);
    merch_t *merge20 = merch_create(ht, str_elem("Gurka"), "Mat", 44);
    merch_t *merge21 = merch_create(ht, str_elem("Salt"), "Mat", 500);
    
    bool over_twenty = list_merch(ht, 20, 21, &zero);
    CU_ASSERT_TRUE(over_twenty);
    int twenty = 20;
    over_twenty = list_merch(ht, 40, 21, &twenty);
    CU_ASSERT_FALSE(over_twenty);

    delete_merch(merge1);
    delete_merch(merge2);
    delete_merch(merge3);
    delete_merch(merge4);
    delete_merch(merge5);
    delete_merch(merge6);
    delete_merch(merge7);
    delete_merch(merge8);
    delete_merch(merge9);
    delete_merch(merge10);
    delete_merch(merge11);
    delete_merch(merge12);
    delete_merch(merge13);
    delete_merch(merge14);
    delete_merch(merge15);
    delete_merch(merge16);
    delete_merch(merge17);
    delete_merch(merge18);
    delete_merch(merge19);
    delete_merch(merge20);
    delete_merch(merge21);
    
    ioopm_hash_table_destroy(ht);
}

void test_delete_merch() 
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(string_to_int, compare_str, NULL);

    merch_create(ht, str_elem("Ost"), "Mat", 19);
    
    CU_ASSERT_TRUE(name_exists(ht, str_elem("Ost")));
    
    bool success;
    delete_merch(ioopm_hash_table_lookup(ht, str_elem("Ost"), &success).merch_ptr);
    
    ioopm_hash_table_lookup(ht, str_elem("Ost"), &success);
    CU_ASSERT_FALSE(success);

    ioopm_hash_table_destroy(ht);
}

void test_change_name(void) 
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(string_to_int, compare_str, NULL);

    bool lookup_success;
    
    merch_t *merge1 = merch_create(ht, str_elem("Ost"), "Mat", 19);
    merch_t *merge2 = merch_create(ht, str_elem("Korv"), "Mat", 44);
    merch_t *merge3 = merch_create(ht, str_elem("Potatis"), "Mat", 500);

    bool existing_item = change_name(ht, "Pannkaka", &str_elem("Ost"));
    CU_ASSERT_TRUE(existing_item);

    ioopm_hash_table_lookup(ht, str_elem("Pannkaka"), &lookup_success);
    CU_ASSERT_TRUE(lookup_success);


    // This will never happen since our ask_question_string won't accept an empty string
    bool change_to_empty_str = change_name(ht, "", &str_elem("Ost"));
    CU_ASSERT_TRUE(change_to_empty_str);

    delete_merch(merge1);
    delete_merch(merge2);
    delete_merch(merge3);
    
    ioopm_hash_table_destroy(ht);
}

void test_change_desc() {
    ioopm_hash_table_t *ht = ioopm_hash_table_create(string_to_int, compare_str, NULL);

    change_desc(ht, "Hej", &str_elem(NULL));

    merch_t *merge1 = merch_create(ht, str_elem("Ost"), "Mat", 19);
    merch_t *merge2 = merch_create(ht, str_elem("Korv"), "Mat", 44);
    merch_t *merge3 = merch_create(ht, str_elem("Potatis"), "Mat", 500);

    change_desc(ht, "Hej", &str_elem("Ost"));
    change_desc(ht, "Hej", &str_elem("Korv"));
    change_desc(ht, "Hej", &str_elem("Potatis"));

    CU_ASSERT_EQUAL("Hej", merge1->desc);
    CU_ASSERT_EQUAL("Hej", merge2->desc);
    CU_ASSERT_EQUAL("Hej", merge3->desc);
    
    delete_merch(merge1);
    delete_merch(merge2);
    delete_merch(merge3);

    ioopm_hash_table_destroy(ht);
}

void test_change_price() {
    ioopm_hash_table_t *ht = ioopm_hash_table_create(string_to_int, compare_str, NULL);

    change_price(ht, 100, NULL);
    
    merch_t *merge1 = merch_create(ht, str_elem("Ost"), "Mat", 19);
    merch_t *merge2 = merch_create(ht, str_elem("Korv"), "Mat", 44);
    merch_t *merge3 = merch_create(ht, str_elem("Potatis"), "Mat", 500);

    change_price(ht, 100, &str_elem("Ost"));
    change_price(ht, 100, &str_elem("Korv"));
    change_price(ht, 100, &str_elem("Potatis"));

    CU_ASSERT_EQUAL(100, merge1->price)
    CU_ASSERT_EQUAL(100, merge2->price)
    CU_ASSERT_EQUAL(100, merge3->price)

    delete_merch(merge1);
    delete_merch(merge2);
    delete_merch(merge3);
    
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
        (CU_add_test(my_test_suite, "Tests for merch_create function", test_add_merch) == NULL) ||
        (CU_add_test(my_test_suite, "Tests for list_merch function", test_list_merch) == NULL) ||
        (CU_add_test(my_test_suite, "Tests for delete_merch function", test_delete_merch) == NULL) ||
        (CU_add_test(my_test_suite, "Tests for change_name function", test_change_name) == NULL) ||
        (CU_add_test(my_test_suite, "Tests for change_desc function", test_change_desc) == NULL) ||
        (CU_add_test(my_test_suite, "Tests for change_price function", test_change_price) == NULL) ||
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