#include "linked_list.h"
#include "iterator.h"
#include <CUnit/Basic.h>
#include <stdbool.h>


static bool int_compare(elem_t a, elem_t b) { return a.int_value == b.int_value;}


typedef struct list list_t;
typedef struct link link_t;

struct link
{
    elem_t element;
    link_t *next;
};

struct list
{
    link_t *first;
    link_t *last;
    size_t size;
    eq_function equal_fun;
};

struct iter 
{
  link_t *current;
  list_t *list; /// New field
};


int init_suite(void) {
  // Change this function if you want to do something *before* you
  // run a test suite
  return 0;
}

int clean_suite(void) {
  // Change this function if you want to do something *after* you
  // run a test suite
  return 0;
}

void test_create_list(void)
{
    list_t *new_list = linked_list_create(int_compare);
    CU_ASSERT_PTR_NULL(new_list->first);
    CU_ASSERT_PTR_NULL(new_list->last);

    linked_list_destroy(new_list);
}


void test_destroy_list(void)
{
  list_t *new_list = linked_list_create(int_compare);

  linked_list_append(new_list, int_elem(2));
  linked_list_append(new_list, int_elem(3));
  CU_ASSERT_PTR_NOT_NULL(new_list->last);
  linked_list_destroy(new_list);
}

void test_append_link(void)
{
    list_t *new_list = linked_list_create(int_compare);

    linked_list_append(new_list, int_elem(2));
    CU_ASSERT_EQUAL(new_list->last->element.int_value, 2);
    linked_list_append(new_list, int_elem(10));
    linked_list_append(new_list, int_elem(9));
    linked_list_append(new_list, int_elem(6));
    CU_ASSERT_EQUAL(new_list->last->element.int_value, 6);
    CU_ASSERT_EQUAL(new_list->first->element.int_value, 2);
    CU_ASSERT_EQUAL(new_list->first->next->element.int_value, 10);

    linked_list_destroy(new_list);
}

void test_prepend_link(void)
{
    list_t *new_list = linked_list_create(int_compare);
  
    linked_list_prepend(new_list, int_elem(2));
    CU_ASSERT_EQUAL(new_list->first->element.int_value, 2);
    linked_list_prepend(new_list, int_elem(5));
    CU_ASSERT_EQUAL(new_list->first->element.int_value, 5);
    linked_list_prepend(new_list, int_elem(1239013));
    CU_ASSERT_EQUAL(new_list->first->element.int_value, 1239013);

    linked_list_destroy(new_list);
}

void test_insert_link(void) {
  list_t *new_list = linked_list_create(int_compare);
  
  linked_list_prepend(new_list, int_elem(2));
  linked_list_prepend(new_list, int_elem(5));
  linked_list_prepend(new_list, int_elem(124));
  linked_list_prepend(new_list, int_elem(19824));
  linked_list_prepend(new_list, int_elem(1274));

  // Checks that inserting before first works
  linked_list_insert(new_list, 0, int_elem(69));
  CU_ASSERT_EQUAL(new_list->first->element.int_value, 69);

  // Checks that inserting after last works
  linked_list_insert(new_list, linked_list_size(new_list), int_elem(100));
  CU_ASSERT_EQUAL(new_list->last->element.int_value, 100);

  // Checks that inserting on a key that already exists, updates elements value
  linked_list_insert(new_list, 2, int_elem(1337));
  CU_ASSERT_EQUAL(new_list->first->next->element.int_value, 1337);
  linked_list_insert(new_list, 4, int_elem(420));
  CU_ASSERT_EQUAL(new_list->first->next->next->next->element.int_value, 420);
  
  linked_list_destroy(new_list);
}

void test_size_n_empty_list(void) {
  list_t *new_list = linked_list_create(int_compare);

  bool is_empty = linked_list_is_empty(new_list);
  CU_ASSERT_TRUE(is_empty);
  for (int i = 0; i < 20; i++) {
    linked_list_prepend(new_list, int_elem(i));
  }

  CU_ASSERT_EQUAL(linked_list_size(new_list), 20);

  is_empty = linked_list_is_empty(new_list);
  CU_ASSERT_FALSE(is_empty);

  linked_list_destroy(new_list);
}

void test_link_contains(void) {
  list_t *new_list = linked_list_create(int_compare);
  CU_ASSERT_FALSE(linked_list_contains(new_list, int_elem(2)));

  linked_list_append(new_list, int_elem(2));
  linked_list_append(new_list, int_elem(5));
  linked_list_append(new_list, int_elem(124));

  CU_ASSERT_TRUE(linked_list_contains(new_list, int_elem(2)));
  CU_ASSERT_FALSE(linked_list_contains(new_list, int_elem(7)));

  linked_list_destroy(new_list);
}

void test_get_link(void)
{
  list_t *new_list = linked_list_create(int_compare);
  
  linked_list_append(new_list, int_elem(2));
  linked_list_append(new_list, int_elem(5));
  linked_list_append(new_list, int_elem(124));

  CU_ASSERT_EQUAL(linked_list_get(new_list, 2).int_value, 124);

  linked_list_destroy(new_list);
}

void test_remove_element_from_list(void) {
  list_t *new_list = linked_list_create(int_compare);
  linked_list_prepend(new_list, int_elem(1));
  linked_list_prepend(new_list, int_elem(100));
  linked_list_prepend(new_list, int_elem(69));
  linked_list_prepend(new_list, int_elem(420));
  linked_list_prepend(new_list, int_elem(3));
  linked_list_prepend(new_list, int_elem(20));
  
  // Tests for removing first element
  int removed_first_element = linked_list_remove(new_list, 0).int_value;
  CU_ASSERT_EQUAL(removed_first_element, 20); // Ensure that the removed element is 20
  CU_ASSERT_EQUAL(new_list->first->element.int_value, 3);
  CU_ASSERT_EQUAL(new_list->last->element.int_value, 1);

  // Tests for removing last element
  int remove_last_element = new_list->size - 1;
  int removed_last_element = linked_list_remove(new_list, remove_last_element).int_value;
  CU_ASSERT_EQUAL(removed_last_element, 1);
  CU_ASSERT_EQUAL(new_list->last->element.int_value, 100);

  // Tests for removing element in the middle
  int removed_element = linked_list_remove(new_list, 2).int_value;
  CU_ASSERT_EQUAL(removed_element, 69);
  CU_ASSERT_FALSE(linked_list_contains(new_list, int_elem(69)));

  // Check that the rest of the elements are in the list and in same order
  CU_ASSERT_EQUAL(new_list->first->element.int_value, 3);
  CU_ASSERT_EQUAL(new_list->first->next->element.int_value, 420);
  CU_ASSERT_EQUAL(new_list->last->element.int_value, 100);

  int another_removed_element = linked_list_remove(new_list, 1).int_value;
  CU_ASSERT_EQUAL(another_removed_element, 420);

  // Check that the rest of the elements are in the list and in same order
  CU_ASSERT_EQUAL(new_list->first->element.int_value, 3);
  CU_ASSERT_EQUAL(new_list->first->next->element.int_value, 100);
  CU_ASSERT_EQUAL(new_list->last->element.int_value, 100);

  linked_list_destroy(new_list);
}

void test_clear_list(void) {
  list_t *new_list = linked_list_create(int_compare);
  linked_list_prepend(new_list, int_elem(1));
  linked_list_prepend(new_list, int_elem(100));
  linked_list_prepend(new_list, int_elem(69));
  linked_list_prepend(new_list, int_elem(420));
  linked_list_prepend(new_list, int_elem(3));
  linked_list_prepend(new_list, int_elem(20));
  linked_list_prepend(new_list, int_elem(3));
  
  linked_list_clear(new_list);

  CU_ASSERT_PTR_NULL(new_list->first);
  CU_ASSERT_PTR_NULL(new_list->last);

  linked_list_destroy(new_list);
  
}

bool is_even(elem_t value, void *extra)
{
    if(value.int_value % 2 == 0) {
        return true;
    } else {
        return false;
    }
}

void test_linked_list_all(void)
{
    list_t *new_list = linked_list_create(int_compare);

    CU_ASSERT_TRUE(linked_list_all(new_list, is_even, new_list));

    linked_list_prepend(new_list, int_elem(2));
    linked_list_prepend(new_list, int_elem(100));
    linked_list_prepend(new_list, int_elem(-68));

    CU_ASSERT_TRUE(linked_list_all(new_list, is_even, new_list));

    linked_list_prepend(new_list, int_elem(69));

    CU_ASSERT_FALSE(linked_list_all(new_list, is_even, new_list));

    linked_list_destroy(new_list);
}

void test_linked_list_any(void)
{
    list_t *new_list = linked_list_create(int_compare);

    CU_ASSERT_FALSE(linked_list_any(new_list, is_even, new_list)); 

    linked_list_prepend(new_list, int_elem(3));
    linked_list_prepend(new_list, int_elem(15));
    linked_list_prepend(new_list, int_elem(-68));

    CU_ASSERT_TRUE(linked_list_any(new_list, is_even, new_list));

    linked_list_remove(new_list, 0);
    linked_list_prepend(new_list, int_elem(69));

    CU_ASSERT_FALSE(linked_list_any(new_list, is_even, new_list));

    linked_list_destroy(new_list);
}

void is_odd_add_one(elem_t *elem, void *extra) 
{
    if(elem->int_value % 2 != 0) {
        elem->int_value = elem->int_value + 1;
    }
}

void multiply_by(elem_t *elem, void *extra)
{
    int *plol = extra;
    elem->int_value = (elem->int_value) * (*plol);
}


void test_linked_list_fun_all(void)
{
    list_t *new_list = linked_list_create(int_compare);

    linked_list_apply_to_all(new_list, is_odd_add_one, new_list); 
    CU_ASSERT_TRUE(linked_list_all(new_list, is_even, new_list));

    linked_list_prepend(new_list, int_elem(3));
    linked_list_prepend(new_list, int_elem(15));
    linked_list_prepend(new_list, int_elem(-68));

    linked_list_apply_to_all(new_list, is_odd_add_one, new_list);
    CU_ASSERT_TRUE(linked_list_all(new_list, is_even, new_list));

    linked_list_prepend(new_list, int_elem(2));
    linked_list_prepend(new_list, int_elem(64));

    linked_list_apply_to_all(new_list, is_odd_add_one, new_list);
    CU_ASSERT_TRUE(linked_list_all(new_list, is_even, new_list));
    
    linked_list_destroy(new_list);
}

void test_iter_create(void)
{
    list_t *new_list = linked_list_create(int_compare);

    linked_list_prepend(new_list, int_elem(1));
    linked_list_prepend(new_list, int_elem(100));
    linked_list_prepend(new_list, int_elem(69));
    linked_list_prepend(new_list, int_elem(420));

    list_iterator_t *new_iter = list_iterator(new_list);
    CU_ASSERT_EQUAL(iterator_next(new_iter).int_value, 420);

    iterator_destroy(new_iter);
    linked_list_destroy(new_list);
}

void test_iter_next(void)
{
    list_t *new_list = linked_list_create(int_compare);
    
    linked_list_prepend(new_list, int_elem(1));
    linked_list_prepend(new_list, int_elem(100));
    linked_list_prepend(new_list, int_elem(69));
    linked_list_prepend(new_list, int_elem(420));

    list_iterator_t *new_iter = list_iterator(new_list);

    CU_ASSERT_EQUAL(iterator_next(new_iter).int_value, 420);
    iterator_next(new_iter);
    iterator_next(new_iter);
    iterator_next(new_iter);
    CU_ASSERT_PTR_NULL(iterator_next(new_iter).ptr_value);

    iterator_destroy(new_iter);
    linked_list_destroy(new_list);
}

void test_iter_current(void)
{
    list_t *new_list = linked_list_create(int_compare);
    
    linked_list_prepend(new_list, int_elem(1));
    linked_list_prepend(new_list, int_elem(100));
    linked_list_prepend(new_list, int_elem(69));
    linked_list_prepend(new_list, int_elem(420));

    list_iterator_t *new_iter = list_iterator(new_list);
    iterator_next(new_iter);
    CU_ASSERT_EQUAL(iterator_current(new_iter).int_value, 420);

    iterator_destroy(new_iter);
    linked_list_destroy(new_list);
}

void test_iter_reset(void)
{
    list_t *new_list = linked_list_create(int_compare);
    
    linked_list_prepend(new_list, int_elem(1));
    linked_list_prepend(new_list, int_elem(100));
    linked_list_prepend(new_list, int_elem(69));
    linked_list_prepend(new_list, int_elem(420));


    list_iterator_t *new_iter = list_iterator(new_list);
    iterator_next(new_iter);
    CU_ASSERT_EQUAL(iterator_next(new_iter).int_value, 69);
    iterator_next(new_iter);
    iterator_reset(new_iter);
    CU_ASSERT_EQUAL(iterator_next(new_iter).int_value, 420);

    iterator_destroy(new_iter);
    linked_list_destroy(new_list);
}


int main() {
  // First we try to set up CUnit, and exit if we fail
  if (CU_initialize_registry() != CUE_SUCCESS)
    return CU_get_error();

  // We then create an empty test suite and specify the name and
  // the init and cleanup functions
  CU_pSuite my_test_suite = CU_add_suite("My awesome test suite", init_suite, clean_suite);
  if (my_test_suite == NULL) {
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
    (CU_add_test(my_test_suite, "Test for create_list functionality", test_create_list) == NULL) || 
    (CU_add_test(my_test_suite, "Test for destroy_list functionality", test_destroy_list) == NULL) ||
    (CU_add_test(my_test_suite, "Test for append_link functionality", test_append_link) == NULL) ||
    (CU_add_test(my_test_suite, "Test for prepend_link functionality", test_prepend_link) == NULL) ||
    (CU_add_test(my_test_suite, "Test for insert_link functionality", test_insert_link) == NULL) ||
    (CU_add_test(my_test_suite, "Test for link_contains functionality", test_link_contains) == NULL) ||
    (CU_add_test(my_test_suite, "Test for get_link functionality", test_get_link) == NULL) ||
    (CU_add_test(my_test_suite, "Test for size_n_empty_link functionality", test_size_n_empty_list) == NULL) ||
    (CU_add_test(my_test_suite, "Test for remove_link functionality", test_remove_element_from_list) == NULL) ||
    (CU_add_test(my_test_suite, "Test for clearing the list", test_clear_list) == NULL) ||
    (CU_add_test(my_test_suite, "Test for linked_list_all functionality", test_linked_list_all) == NULL) ||
    (CU_add_test(my_test_suite, "Test for linked_list_any functionality", test_linked_list_any) == NULL) ||
    (CU_add_test(my_test_suite, "Test for apply_to_all functionality", test_linked_list_fun_all) == NULL) ||

    (CU_add_test(my_test_suite, "Test for iter_create functionality", test_iter_create) == NULL) ||
    (CU_add_test(my_test_suite, "Test for iter_next functionality", test_iter_next) == NULL) ||
    (CU_add_test(my_test_suite, "Test for iter_current functionality", test_iter_current) == NULL) ||
    (CU_add_test(my_test_suite, "Test for iter_reset functionality", test_iter_reset) == NULL) ||
    0
  )
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