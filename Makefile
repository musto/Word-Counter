CC= gcc
LD= gcc
CFLAGS= -Wall -Werror -pedantic -std=c99 -g -O0 -I sources

.PHONY: clean

all: test wordcount

test: tests/test.o tests/avl_tree_test.o sources/avl_tree.o
	$(LD) $^ -o $@

wordcount: sources/wordcount.o sources/avl_tree.o
	$(LD) $^ -o $@


run_test: test
	valgrind --leak-check=full --show-reachable=yes ./test

run_test2: wordcount
	cd tests && ./test.sh

clean:
	$(RM) tests/*.o sources/*.o test tests/testoutput

