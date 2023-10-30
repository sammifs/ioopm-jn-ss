CC =gcc
FLAGS =-Wall -g
GCOVFLAGS = -fprofile-arcs -ftest-coverage
MEM = valgrind --leak-check=full

INLUPP2 = ioopm_store.c shelf_list.c merch_hash_table.c cart_hash_table.c datastructures/hash_table.c datastructures/linked_list.c utils.c

%.o: %.c %.h
	$(CC) $(FLAGS) $< -c

event_loop: event_loop.c 
	$(CC) $(FLAGS) $^ $(INLUPP2) -o $@

build_store_test: ioopm_store_test.c
	$(CC) $(FLAGS) $^ $(INLUPP2) -lcunit -o $@

mem_store_test: 
	make build_store_test
	$(MEM) ./build_store_test

gcov_store:	ioopm_store.o
	$(CC) $(GCOVFLAGS) $(FLAGS) -o ioopm_store $(INLUPP2) ioopm_store_test.c -lcunit
	./ioopm_store
	gcov ioopm_store.c


clean:
	rm -f *.o
	rm -f *.gcov
	rm -f *.gcda
	rm -f *.gcno
	rm -f event_loop build_store_test ioopm_store

.PHONY: event_loop build_store_test gcov_store