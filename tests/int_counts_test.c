#include "test.h"
#include "int_counts.h"


void test_creation()
{
	struct int_counts* container = int_counts_create();
	int_counts_destroy(container);
}

void test_insertion()
{
	struct int_counts* container = int_counts_create();
	int_counts_add(container, 10);
	int_counts_add(container, 2);
	int_counts_add(container, 13);
	int_counts_add(container, 10);
	int_counts_destroy(container);
}

void test_min_and_max()
{
	struct int_counts* container = int_counts_create();

	assertHigher(int_counts_min(container), int_counts_max(container));

	int_counts_add(container, 2);
	assertIntEquals(2, int_counts_min(container));
	assertIntEquals(2, int_counts_max(container));

	int_counts_add(container, 1);
	assertIntEquals(1, int_counts_min(container));
	assertIntEquals(2, int_counts_max(container));

	int_counts_add(container, 13);
	assertIntEquals(1, int_counts_min(container));
	assertIntEquals(13, int_counts_max(container));

	int_counts_destroy(container);
}

void test_retrieval()
{
	struct int_counts* container = int_counts_create();
	int_counts_add(container, 10);
	int_counts_add(container, 2);
	int_counts_add(container, 13);
	int_counts_add(container, 10);
	int_counts_add(container, 10);
	int_counts_add(container, 13);

	assertIntEquals(0, int_counts_get(container, 1));
	assertIntEquals(1, int_counts_get(container, 2));
	assertIntEquals(0, int_counts_get(container, 3));
	assertIntEquals(3, int_counts_get(container, 10));
	assertIntEquals(0, int_counts_get(container, 11));
	assertIntEquals(2, int_counts_get(container, 13));
	assertIntEquals(0, int_counts_get(container, 14));

	int_counts_destroy(container);
}

int main(void)
{
	test_creation();
	test_insertion();
	test_min_and_max();
	test_retrieval();

	return 0;
}

