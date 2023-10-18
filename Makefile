CC =gcc
FLAGS =-Wall -g
GCOVFLAGS = -fprofile-arcs -ftest-coverage
MEM = valgrind --leak-check=full


%.o: %.c %.h
	$(CC) $(FLAGS) $< -c

event_loop:
	$(CC) $(FLAGS) event_loop.c hash_table.c linked_list.c utils.c interface.c logic.c -o $@



build_logic_test: logic_tests.c logic.o linked_list.o hash_table.o utils.o
	$(CC) $(FLAGS) $^ -lcunit -o $@

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

gcov_logic: logic.o hash_table.o linked_list.o utils.o 
	$(CC) $(GCOVFLAGS) $(FLAGS) -o logic logic.c logic_tests.c -lcunit
	./logic
	gcov logic.c

gcov_ht: hash_table.o 
	$(CC) $(GCOVFLAGS) $(FLAGS) -o hash_table hash_table.c hash_table_tests.c -lcunit
	./hash_table
	gcov hash_table.c

gcov_ll: linked_list.o 
	$(CC) $(GCOVFLAGS) -o linked_list linked_list.c linked_list_tests.c -lcunit
	./linked_list
	gcov linked_list.c


freq_count: hash_table.c freq-count.c
	$(CC) $(FLAGS) freq-count.c -o freq_count


freq_16k: freq_count 16k-words.txt
	$(MEM) ./freq_count 16k-words.txt

gprof_16k: freq-count.c
	$(CC) -pg freq-count.c -o freq_count
	./freq_count 16k-words.txt
	gprof freq_count gmon.out > prof_output


test:
	make freq_small
	make freq_1k
	make freq_10k
	make freq_16k

clean:
	rm -f *.o
	rm -f *.gcov
	rm -f *.gcda
	rm -f *.gcno
	rm -f freq_count build_ht_test build_ll_test freq-count gmon.out hash_table event_loop build_logic_test

.PHONY: build_logic_test event_loop test clean gprof_16k gcov_ht gcov_ll test_ht_mem test_ll_mem