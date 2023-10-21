CC =gcc
FLAGS =-Wall -g
GCOVFLAGS = -fprofile-arcs -ftest-coverage
MEM = valgrind --leak-check=full

INLUPP2 = ioopm_store.c shelf_list.c merch_hash_table.c datastructures/hash_table.c datastructures/linked_list.c utils.c

%.o: %.c %.h
	$(CC) $(FLAGS) $< -c

event_loop: event_loop.c 
	$(CC) $(FLAGS) $^ $(INLUPP2) -o $@

build_ll_test: linked_list.o  linked_list_tests.c
	$(CC) $(FLAGS) $^ -lcunit -o $@

test_ll: build_ll_test
	./build_ll_test	

test_ll_mem: linked_list.o build_ll_test
	$(MEM) ./build_ll_test


build_ht_test: hash_table.o linked_list.o hash_table_tests.c
	$(CC) $(FLAGS) hash_table.c hash_table_tests.c linked_list.c -o $@ -lcunit

test_ht: build_ht_test
	./build_ht_test

test_ht_mem: build_ht_test
	$(MEM) ./build_ht_test


memtest:
	make test_ll_mem 
	make test_ht_mem
	

gcov_ht: hash_table.o 
	$(CC) $(GCOVFLAGS) $(FLAGS) -o hash_table hash_table.c hash_table_tests.c -lcunit
	./hash_table
	gcov hash_table.c

gcov_ll: linked_list.o 
	$(CC) $(GCOVFLAGS) -o linked_list linked_list.c linked_list_tests.c -lcunit
	./linked_list
	gcov linked_list.c


clean:
	rm -f *.o
	rm -f *.gcov
	rm -f *.gcda
	rm -f *.gcno
	rm -f freq_count build_ht_test build_ll_test freq-count gmon.out hash_table event_loop

.PHONY: event_loop test clean freq_small freq_1k freq_10k freq_16k gprof_small gprof_1k gprof_10k gprof_16k gcov_ht gcov_ll test_ht_mem test_ll_mem