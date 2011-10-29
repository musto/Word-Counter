CC= gcc
LD= gcc
CFLAGS= -Wall -Wextra -pedantic -std=c99 -g -O0 -I sources

.PHONY: clean

all: unit_tests wordcount

unit_tests: avl_tree_test int_counts_test

int_counts_test: tests/test.o tests/int_counts_test.o sources/int_counts.o
	$(LD) $^ -o $@

avl_tree_test: tests/test.o tests/avl_tree_test.o sources/avl_tree.o
	$(LD) $^ -o $@

wordcount: sources/wordcount.o sources/avl_tree.o
	$(LD) $^ -o $@


run_tests: unit_tests
	valgrind --leak-check=full --show-reachable=yes ./avl_tree_test
	valgrind --leak-check=full --show-reachable=yes ./int_counts_test

run_tests2: wordcount
	cd tests && ./test.sh

clean:
	$(RM) tests/*.o sources/*.o avl_tree_test int_counts_test tests/testoutput

