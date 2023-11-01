#include <CUnit/Basic.h>
#include "ioopm_store.h"
#include "merch_hash_table.h"

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

    CU_ASSERT_FALSE(ioopm_store_add_merch(store, "Ost", "Mat", 20));

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

void test_list_merch_many() {
    ioopm_store_t *store = ioopm_store_create();
    CU_ASSERT_EQUAL(-1, ioopm_store_list_merch(store, 0));
    ioopm_store_add_merch(store, strdup("Ost"), strdup("Mat"), 20);
    ioopm_store_add_merch(store, strdup("Korv"), strdup("Mat"), 20);
    ioopm_store_add_merch(store, strdup("Bord"), strdup("Möbel"), 20);
    ioopm_store_add_merch(store, strdup("Potatis"), strdup("Mat"), 20);
    ioopm_store_add_merch(store, strdup("Sten"), strdup("Ting"), 20);
    ioopm_store_add_merch(store, strdup("Stol"), strdup("Möbel"), 20);
    ioopm_store_add_merch(store, strdup("Tröja"), strdup("Kläder"), 20);
    ioopm_store_add_merch(store, strdup("Stone"), strdup("Name"), 20);
    ioopm_store_add_merch(store, strdup("Food"), strdup("Name"), 20);
    ioopm_store_add_merch(store, strdup("Cheese"), strdup("Name"), 20);
    ioopm_store_add_merch(store, strdup("Sausage"), strdup("Name"), 20);
    ioopm_store_add_merch(store, strdup("Potato"), strdup("Name"), 20);
    ioopm_store_add_merch(store, strdup("Shirt"), strdup("Name"), 20);
    ioopm_store_add_merch(store, strdup("T-shirt"), strdup("Name"), 20);
    ioopm_store_add_merch(store, strdup("Car"), strdup("Name"), 20);
    ioopm_store_add_merch(store, strdup("Hamburger"), strdup("Name"), 20);
    ioopm_store_add_merch(store, strdup("Hot dog"), strdup("Name"), 20);
    ioopm_store_add_merch(store, strdup("Cup"), strdup("Name"), 20);
    ioopm_store_add_merch(store, strdup("Byxor"), strdup("Name"), 20);
    ioopm_store_add_merch(store, strdup("Sladd"), strdup("Name"), 20);
    ioopm_store_add_merch(store, strdup("Dator"), strdup("Name"), 20);
    ioopm_store_add_merch(store, strdup("Tandkräm"), strdup("Name"), 20);
    ioopm_store_add_merch(store, strdup("Computer"), strdup("Name"), 20);
    ioopm_store_add_merch(store, strdup("Pasta"), strdup("Name"), 20);
    ioopm_store_add_merch(store, strdup("Bok"), strdup("Name"), 20);
    CU_ASSERT_EQUAL(0, ioopm_store_list_merch(store, 0));
    CU_ASSERT_EQUAL(1, ioopm_store_list_merch(store, 1));
    ioopm_store_destroy(store);
}

void test_list_merch_few() {

    ioopm_store_t *store = ioopm_store_create();
    CU_ASSERT_EQUAL(-1, ioopm_store_list_merch(store, 0));
    CU_ASSERT_EQUAL(-2, ioopm_store_list_merch(store, -100));

    ioopm_store_add_merch(store, strdup("Ost"), strdup("Mat"), 20);
    ioopm_store_add_merch(store, strdup("Korv"), strdup("Mat"), 20);
    ioopm_store_add_merch(store, strdup("Bord"), strdup("Möbel"), 20);
    ioopm_store_add_merch(store, strdup("Potatis"), strdup("Mat"), 20);
    ioopm_store_add_merch(store, strdup("Sten"), strdup("Ting"), 20);
    
    CU_ASSERT_EQUAL(1, ioopm_store_list_merch(store, 0));

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

void test_edit_with_the_same_name(void) {
    ioopm_store_t *store = ioopm_store_create();

    ioopm_store_add_merch(store, strdup("Ost"), strdup("Mat"), 20);

    CU_ASSERT_EQUAL(1, ioopm_store_edit_merch(store, "Ost", "Ost", strdup("Very good"), 152));

    ioopm_store_destroy(store);
}

void test_edit_nonexisting_merch(void) {
    ioopm_store_t *store = ioopm_store_create();

    CU_ASSERT_EQUAL(-1, ioopm_store_edit_merch(store, "Ost", "Bord", "Möbel", 240));

    ioopm_store_destroy(store);
}

void test_edit_merch_to_already_existing_name(void) {
    ioopm_store_t *store = ioopm_store_create();

    ioopm_store_add_merch(store, strdup("Ost"), strdup("Mat"), 20);
    ioopm_store_add_merch(store, strdup("Bord"), strdup("Möbel"), 20);

    CU_ASSERT_EQUAL(-2, ioopm_store_edit_merch(store, "Ost", "Bord", "SDF", 152));

    ioopm_store_destroy(store);
}

void test_edit_merch_with_stock(void) {
    ioopm_store_t *store = ioopm_store_create();

    bool success;
    ioopm_store_add_merch(store, strdup("Ost"), strdup("Mat"), 20);
    CU_ASSERT_TRUE(shelf_list_is_empty(merch_get_locs(merch_hash_table_lookup(store_get_warehouse(store), "Ost", &success))));
    ioopm_store_replenish_stock(store, "Ost", strdup("A34"), 10);

    CU_ASSERT_STRING_EQUAL("Ost", hash_table_lookup(store_get_shelves(store), str_elem("A34"), &success).str_value);

    CU_ASSERT_EQUAL(0, ioopm_store_edit_merch(store, "Ost", strdup("Bord"), strdup("Mat"), 150));
    
    CU_ASSERT_FALSE(shelf_list_is_empty(merch_get_locs(merch_hash_table_lookup(store_get_warehouse(store), "Bord", &success))));

    ioopm_store_destroy(store);
}

void test_show_stock() {
    ioopm_store_t *store = ioopm_store_create();

    ioopm_store_show_stock(store, "Ost");

    ioopm_store_add_merch(store, strdup("Ost"), strdup("Mat"), 20);

    CU_ASSERT_TRUE(ioopm_store_show_stock(store, "Ost"));
    ioopm_store_replenish_stock(store, "Ost", strdup("A34"), 10);
    ioopm_store_replenish_stock(store, "Ost", strdup("L10"), 10);
    CU_ASSERT_TRUE(ioopm_store_show_stock(store, "Ost"));
    CU_ASSERT_FALSE(ioopm_store_show_stock(store, "Korv"));

    ioopm_store_destroy(store);
}

void test_replenish_of_self_owned_shelf(void)
{
    ioopm_store_t *store = ioopm_store_create();
    
    ioopm_store_add_merch(store, strdup("Ost"), strdup("Mat"), 109); 
    ioopm_store_add_merch(store, strdup("Korv"), strdup("Mat"), 59); 

    // Create a new shelfs
    CU_ASSERT_EQUAL(0, ioopm_store_replenish_stock(store, "Ost", strdup("G17"), 100));
    CU_ASSERT_EQUAL(0, ioopm_store_replenish_stock(store, "Ost", strdup("A12"), 100));
    CU_ASSERT_EQUAL(0, ioopm_store_replenish_stock(store, "Ost", strdup("D45"), 100));

    // Replenish the both shelves
    CU_ASSERT_EQUAL(1, ioopm_store_replenish_stock(store, "Ost", "G17", 50));
    CU_ASSERT_EQUAL(1, ioopm_store_replenish_stock(store, "Ost", "A12", 100));
    CU_ASSERT_EQUAL(1, ioopm_store_replenish_stock(store, "Ost", "D45", 10));

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

void test_add_cart() {
    ioopm_store_t *store = ioopm_store_create();

    ioopm_store_create_cart(store);

    CU_ASSERT_EQUAL(1, ioopm_store_get_cart_index(store));
    ioopm_store_create_cart(store);
    CU_ASSERT_EQUAL(2, ioopm_store_get_cart_index(store));
    CU_ASSERT_TRUE(ioopm_store_has_cart(store, 1));
    CU_ASSERT_TRUE(ioopm_store_has_cart(store, 2));

    ioopm_store_destroy(store);
}

void test_remove_cart() {
    ioopm_store_t *store = ioopm_store_create();

    ioopm_store_create_cart(store);
    CU_ASSERT_EQUAL(1, ioopm_store_get_cart_index(store));
    CU_ASSERT_TRUE(ioopm_store_has_cart(store, 1));

    ioopm_store_remove_cart(store, 1);
    CU_ASSERT_FALSE(ioopm_store_has_cart(store, 1));

    CU_ASSERT_FALSE(ioopm_store_remove_cart(store, 1));

    ioopm_store_destroy(store);
}

void test_add_to_cart() {
    ioopm_store_t *store = ioopm_store_create();

    ioopm_store_create_cart(store);
    ioopm_store_add_merch(store, strdup("Ost"), strdup("Mat"), 20);
    ioopm_store_add_merch(store, strdup("Korv"), strdup("Mat"), 50);
    ioopm_store_replenish_stock(store, "Ost", strdup("A34"), 10);
    ioopm_store_replenish_stock(store, "Korv", strdup("G84"), 40);

    CU_ASSERT_EQUAL(0, ioopm_store_add_to_cart(store, 1, strdup("Ost"), 5));
    CU_ASSERT_EQUAL(0, ioopm_store_add_to_cart(store, 1, strdup("Korv"), 20));
    CU_ASSERT_EQUAL(-2, ioopm_store_add_to_cart(store, 1, "BOrd", 5));
    CU_ASSERT_EQUAL(-1, ioopm_store_add_to_cart(store, 2, "Ost", 5));
    CU_ASSERT_EQUAL(-3, ioopm_store_add_to_cart(store, 1, "Ost", 6));

    ioopm_store_destroy(store);
}

void test_remove_from_cart() {
    ioopm_store_t *store = ioopm_store_create();

    ioopm_store_create_cart(store);
    ioopm_store_add_merch(store, strdup("Ost"), strdup("Mat"), 20);
    ioopm_store_replenish_stock(store, "Ost", strdup("A34"), 10);

    ioopm_store_add_merch(store, strdup("Bord"), strdup("Möbel"), 20);
    ioopm_store_replenish_stock(store, "Bord", strdup("L10"), 10);
    
    ioopm_store_add_merch(store, strdup("Korv"), strdup("Mat"), 20);
    ioopm_store_replenish_stock(store, "Korv", strdup("U19"), 10);

    CU_ASSERT_EQUAL(0, ioopm_store_add_to_cart(store, 1, strdup("Ost"), 5));
    CU_ASSERT_EQUAL(0, ioopm_store_add_to_cart(store, 1, strdup("Bord"), 10));
    CU_ASSERT_EQUAL(0, ioopm_store_add_to_cart(store, 1, strdup("Korv"), 10));

    CU_ASSERT_EQUAL(-1, ioopm_store_remove_from_cart(store, 2, "Ost", 5));
    CU_ASSERT_EQUAL(-2, ioopm_store_remove_from_cart(store, 1, "BORD", 5));
    CU_ASSERT_EQUAL(-3, ioopm_store_remove_from_cart(store, 1, "Ost", 500));
    CU_ASSERT_EQUAL(0, ioopm_store_remove_from_cart(store, 1, "Korv", 5));
    CU_ASSERT_EQUAL(0, ioopm_store_remove_from_cart(store, 1, "Korv", 5));
    CU_ASSERT_EQUAL(0, ioopm_store_remove_from_cart(store, 1, "Ost", 5));
    CU_ASSERT_EQUAL(0, ioopm_store_remove_from_cart(store, 1, "Bord", 10));    

    ioopm_store_destroy(store);
}

void test_calculate_cart_cost() {
    ioopm_store_t *store = ioopm_store_create();

    ioopm_store_create_cart(store);
    ioopm_store_add_merch(store, strdup("Ost"), strdup("Mat"), 20);
    ioopm_store_replenish_stock(store, "Ost", strdup("A34"), 10);

    CU_ASSERT_EQUAL(0, ioopm_store_add_to_cart(store, 1, strdup("Ost"), 5));

    bool success;
    ioopm_store_calculate_cost_cart(store, 50, &success);
    CU_ASSERT_FALSE(success);

    CU_ASSERT_EQUAL(100, ioopm_store_calculate_cost_cart(store, 1, &success));
    CU_ASSERT_TRUE(success);
    ioopm_store_destroy(store);
}

void test_cart_checkout() {
    ioopm_store_t *store = ioopm_store_create();

    ioopm_store_create_cart(store);
    ioopm_store_add_merch(store, strdup("Ost"), strdup("Mat"), 20);
    ioopm_store_replenish_stock(store, "Ost", strdup("A34"), 10);

    CU_ASSERT_EQUAL(0, ioopm_store_add_to_cart(store, 1, strdup("Ost"), 5));

    CU_ASSERT_FALSE(ioopm_store_checkout_cart(store, 50));
    CU_ASSERT_TRUE(ioopm_store_checkout_cart(store, 1));

    ioopm_store_destroy(store);
}

void test_cart_checkout_empty_cart() {
    ioopm_store_t *store = ioopm_store_create();

    ioopm_store_create_cart(store);

    CU_ASSERT_TRUE(ioopm_store_checkout_cart(store, 1));

    ioopm_store_destroy(store);
}

void test_cart_checkout_with_shelves_to_destroy() {
    ioopm_store_t *store = ioopm_store_create();

    ioopm_store_create_cart(store);
    ioopm_store_add_merch(store, strdup("Ost"), strdup("Mat"), 20);
    ioopm_store_replenish_stock(store, "Ost", strdup("A34"), 5);
    ioopm_store_replenish_stock(store, "Ost", strdup("L10"), 5);

    CU_ASSERT_EQUAL(0, ioopm_store_add_to_cart(store, 1, strdup("Ost"), 10));
    
    CU_ASSERT_TRUE(ioopm_store_checkout_cart(store, 1));

    ioopm_store_destroy(store);
}

void test_delete_merch_with_order_in_cart() {
    ioopm_store_t *store = ioopm_store_create();

    ioopm_store_create_cart(store);
    ioopm_store_add_merch(store, strdup("Ost"), strdup("Mat"), 20);
    ioopm_store_replenish_stock(store, "Ost", strdup("A34"), 10);

    ioopm_store_add_merch(store, strdup("Bord"), strdup("Möbel"), 15);
    ioopm_store_replenish_stock(store, "Bord", strdup("L10"), 10);

    CU_ASSERT_EQUAL(0, ioopm_store_add_to_cart(store, 1, strdup("Ost"), 10));
    CU_ASSERT_EQUAL(0, ioopm_store_add_to_cart(store, 1, strdup("Bord"), 10));

    ioopm_store_delete_merch(store, "Ost");
    bool success;
    CU_ASSERT_EQUAL(150, ioopm_store_calculate_cost_cart(store, 1, &success));

    ioopm_store_delete_merch(store, "Bord");
    CU_ASSERT_EQUAL(0, ioopm_store_calculate_cost_cart(store, 1, &success));
    CU_ASSERT_TRUE(ioopm_store_checkout_cart(store, 1));

    ioopm_store_destroy(store);   
}

void test_replenish_with_order_in_cart() {
    ioopm_store_t *store = ioopm_store_create();

    ioopm_store_create_cart(store);
    ioopm_store_add_merch(store, strdup("Ost"), strdup("Mat"), 20);
    ioopm_store_replenish_stock(store, "Ost", strdup("A34"), 10);

    ioopm_store_add_merch(store, strdup("Bord"), strdup("Möbel"), 15);
    ioopm_store_replenish_stock(store, "Bord", strdup("L10"), 10);

    CU_ASSERT_EQUAL(0, ioopm_store_add_to_cart(store, 1, strdup("Ost"), 10));
    CU_ASSERT_EQUAL(0, ioopm_store_add_to_cart(store, 1, strdup("Bord"), 10));

    ioopm_store_replenish_stock(store, "Ost", strdup("A34"), 10);

    ioopm_store_destroy(store); 
}

void test_edit_merch_with_order_in_cart() {
    ioopm_store_t *store = ioopm_store_create();

    ioopm_store_create_cart(store);
    ioopm_store_create_cart(store);
    ioopm_store_add_merch(store, strdup("Ost"), strdup("Mat"), 20);
    ioopm_store_add_merch(store, strdup("Macka"), strdup("Mat"), 20);
    ioopm_store_replenish_stock(store, "Macka", strdup("B86"), 30);
    ioopm_store_replenish_stock(store, "Ost", strdup("A34"), 5);
    ioopm_store_replenish_stock(store, "Ost", strdup("L10"), 10);
    // TODO : Det blir invalid read här!! Ser ut som att "A34" & "L10" blir free() i 
    // ioopm_store_edit_merch men sedan blir de lästa i ioopm_store_checkout_cart.
    CU_ASSERT_EQUAL(0, ioopm_store_add_to_cart(store, 1, strdup("Ost"), 15));
    CU_ASSERT_EQUAL(0, ioopm_store_add_to_cart(store, 2, strdup("Macka"), 15));

    CU_ASSERT_EQUAL(0, ioopm_store_edit_merch(store, "Ost", strdup("Bord"), strdup("HEJ"), 40));

    bool success;
    CU_ASSERT_EQUAL(600, ioopm_store_calculate_cost_cart(store, 1, &success));
    CU_ASSERT_TRUE(ioopm_store_checkout_cart(store, 1));

    ioopm_store_destroy(store);
}

void test_delete_cart_with_orders(){
    ioopm_store_t *store = ioopm_store_create();

    ioopm_store_create_cart(store);

    ioopm_store_add_merch(store, strdup("Ost"), strdup("Mat"), 20);
    ioopm_store_replenish_stock(store, "Ost", strdup("A34"), 10);

    ioopm_store_add_merch(store, strdup("Bord"), strdup("Möbel"), 15);
    ioopm_store_replenish_stock(store, "Bord", strdup("L10"), 10);

    ioopm_store_add_merch(store, strdup("Macka"), strdup("Mat"), 15);
    ioopm_store_replenish_stock(store, "Macka", strdup("K39"), 10);

    CU_ASSERT_EQUAL(0, ioopm_store_add_to_cart(store, 1, strdup("Ost"), 10));
    CU_ASSERT_EQUAL(0, ioopm_store_add_to_cart(store, 1, strdup("Bord"), 10));
    CU_ASSERT_EQUAL(0, ioopm_store_add_to_cart(store, 1, strdup("Macka"), 10));

    CU_ASSERT_TRUE(ioopm_store_remove_cart(store, 1));

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
        (CU_add_test(my_test_suite, "ioopm_store_list_merch_many", test_list_merch_many) == NULL) ||
        (CU_add_test(my_test_suite, "ioopm_store_list_merch_few", test_list_merch_few) == NULL) ||
        (CU_add_test(my_test_suite, "ioopm_store_delete_merch", test_delete_merch) == NULL) ||
        (CU_add_test(my_test_suite, "ioopm_store_has_merch", test_has_merch) == NULL) ||
        (CU_add_test(my_test_suite, "ioopm_store_edit_merch", test_edit_merch) == NULL) ||
        (CU_add_test(my_test_suite, "ioopm_store_edit_merch while not changing name", test_edit_with_the_same_name) == NULL) ||
        (CU_add_test(my_test_suite, "ioopm_store_edit_merch for nonexisting merch", test_edit_nonexisting_merch) == NULL) ||
        (CU_add_test(my_test_suite, "ioopm_store_edit_merch to already existing name", test_edit_merch_to_already_existing_name) == NULL) ||
        (CU_add_test(my_test_suite, "ioopm_store_edit_merch on merch with stock", test_edit_merch_with_stock) == NULL) ||
        (CU_add_test(my_test_suite, "ioopm_store_show_stock", test_show_stock) == NULL) ||
        (CU_add_test(my_test_suite, "ioopm_store_replenish_merch to shelf owned by right merch", test_replenish_of_self_owned_shelf) == NULL) ||
        (CU_add_test(my_test_suite, "ioopm_store_replenish_merch to shelf owned by other merch", test_replenish_already_owned_shelf) == NULL) ||
        (CU_add_test(my_test_suite, "ioopm_store_replenish_merch to a merch not found in the warehouse", test_replenish_not_found_item) == NULL) ||
        (CU_add_test(my_test_suite, "ioopm_store_replenish_merch to a shelf that was just deleted by ioopm_store_delete_merch", test_replenish_on_deleted_shelf) == NULL) ||
        (CU_add_test(my_test_suite, "ioopm_store_create_cart", test_add_cart) == NULL) ||
        (CU_add_test(my_test_suite, "ioopm_store_remove_cart", test_remove_cart) == NULL) ||
        (CU_add_test(my_test_suite, "ioopm_store_add_to_cart", test_add_to_cart) == NULL) ||
        (CU_add_test(my_test_suite, "ioopm_store_remove_from_cart", test_remove_from_cart) == NULL) ||
        (CU_add_test(my_test_suite, "ioopm_store_calculate_cost_cart", test_calculate_cart_cost) == NULL) ||
        (CU_add_test(my_test_suite, "ioopm_store_checkout_cart", test_cart_checkout) == NULL) ||
        (CU_add_test(my_test_suite, "ioopm_store_checkout_cart on empty cart", test_cart_checkout_empty_cart) == NULL) ||
        (CU_add_test(my_test_suite, "ioopm_store_checkout_cart resulting in multiple shelves to destroy", test_cart_checkout_with_shelves_to_destroy) == NULL) ||
        (CU_add_test(my_test_suite, "Creating order of merch and then deleting the merch before checkout", test_delete_merch_with_order_in_cart) == NULL) || 
        (CU_add_test(my_test_suite, "Creating order of merch and then editing the merch before checkout", test_edit_merch_with_order_in_cart) == NULL) ||
        (CU_add_test(my_test_suite, "Creating order of merch and then removing the cart", test_delete_cart_with_orders) == NULL) ||
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