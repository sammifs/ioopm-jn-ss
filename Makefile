CC =gcc
FLAGS =-Wall -g
GCOVFLAGS = -fprofile-arcs -ftest-coverage
MEM = valgrind --leak-check=full

BL = business_logic/
DS = datastructures/

INLUPP2_C = $(BL)ioopm_store.c $(BL)shelf_list.c $(BL)merch_hash_table.c $(BL)cart_hash_table.c $(DS)hash_table.c $(DS)linked_list.c utils/utils.c

event_loop: event_loop.c $(INLUPP2_C)
	$(CC) $(FLAGS) $^ -o $@
	./event_loop

build_store_test: $(BL)ioopm_store_test.c $(INLUPP2_C)
	$(CC) $(FLAGS) $? -lcunit -o $@

mem_store_test: build_store_test
	$(MEM) ./build_store_test

gcov_test: $(INLUPP2_C)
	$(CC) $(GCOVFLAGS) $(FLAGS) -o ioopm_store $? $(BL)ioopm_store_test.c -lcunit
	./ioopm_store
	gcov ioopm_store.c
	gcov merch_hash_table.c
	gcov cart_hash_table.c
	gcov shelf_list.c
	gcov utils.c

clean:
	rm -f *.gcov
	rm -f *.gcda
	rm -f *.gcno
	rm -f event_loop build_store_test ioopm_store 

.PHONY: print event_loop build_store_test gcov_tests