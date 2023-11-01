CC =gcc
FLAGS =-Wall -g
GCOVFLAGS = -fprofile-arcs -ftest-coverage
MEM = valgrind --leak-check=full

INLUPP2 = business_logic/ioopm_store.c business_logic/shelf_list.c business_logic/merch_hash_table.c business_logic/cart_hash_table.c datastructures/hash_table.c datastructures/linked_list.c utils/utils.c

%.o: %.c %.h
	$(CC) $(FLAGS) $< -c

event_loop: event_loop.c 
	$(CC) $(FLAGS) $^ $(INLUPP2) -o $@
	./event_loop

build_store_test: business_logic/ioopm_store_test.c
	$(CC) $(FLAGS) $^ $(INLUPP2) -lcunit -o $@

mem_store_test: 
	make build_store_test
	$(MEM) ./build_store_test

gcov_tests:	business_logic/ioopm_store.o
	$(CC) $(GCOVFLAGS) $(FLAGS) -o ioopm_store $(INLUPP2) business_logic/ioopm_store_test.c -lcunit
	./ioopm_store
	gcov ioopm_store.c 
	gcov merch_hash_table.c
	gcov cart_hash_table.c
	gcov shelf_list.c
	gcov utils.c


clean:
	rm -f *.o
	rm -f *.gcov
	rm -f *.gcda
	rm -f *.gcno
	rm -f event_loop build_store_test ioopm_store 

.PHONY: event_loop build_store_test gcov_store