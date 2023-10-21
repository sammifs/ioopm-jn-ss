CC =gcc
FLAGS =-Wall -g
GCOVFLAGS = -fprofile-arcs -ftest-coverage
MEM = valgrind --leak-check=full

INLUPP2 = ioopm_store.c shelf_list.c merch_hash_table.c datastructures/hash_table.c datastructures/linked_list.c utils.c

%.o: %.c %.h
	$(CC) $(FLAGS) $< -c

event_loop: event_loop.c 
	$(CC) $(FLAGS) $^ $(INLUPP2) -o $@

clean:
	rm -f event_loop

.PHONY: event_loop