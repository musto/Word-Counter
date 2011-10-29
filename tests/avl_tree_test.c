#include "test.h"
#include "avl_tree.h"

void test_creation()
{
	struct avl_tree_node* root;
	root = avl_tree_create();
	avl_tree_destroy(root);
}

void test_insertion()
{
	struct avl_tree_node* root;
	root = avl_tree_create();
	avl_tree_insert(root, "esa", 0);
	avl_tree_insert(root, "vesa", 1);
	avl_tree_insert(root, "hesa", 2);
	avl_tree_destroy(root);
}

void test_finding()
{
	struct avl_tree_node* root;
	int* value;

	root = avl_tree_create();
	avl_tree_insert(root, "esa", 3);

	value = avl_tree_find(root, "vesa");
	assertNull(value);

	value = avl_tree_find(root, "esa");
	assertIntEquals(3, *value);

	avl_tree_destroy(root);
}

void test_inserting_and_finding()
{
	struct avl_tree_node* root;
	int* value;

	root = avl_tree_create();
	avl_tree_insert(root, "esa", 3);
	avl_tree_insert(root, "vesa", 4);
	avl_tree_insert(root, "vvv", 5);
	avl_tree_insert(root, "aaa", 7);

	value = avl_tree_find(root, "vesa");
	assertIntEquals(4, *value);

	value = avl_tree_find(root, "esa");
	assertIntEquals(3, *value);

	value = avl_tree_find(root, "vvv");
	assertIntEquals(5, *value);

	value = avl_tree_find(root, "aaa");
	assertIntEquals(7, *value);

	value = avl_tree_find(root, "bbb");
	assertNull(value);

	avl_tree_destroy(root);
}

void test_that_keys_are_copied()
{
	struct avl_tree_node* root;
	int* value;
	char key[] = "esa";
	root = avl_tree_create();

	avl_tree_insert(root, key, 3);

	value = avl_tree_find(root, "esa");
	assertIntEquals(3, *value);

	key[0] = 'a';
	value = avl_tree_find(root, "esa");
	assertIntEquals(3, *value);

	avl_tree_destroy(root);
}

static int TOTAL = 1;

void test_function(const char* key, int value)
{
	(void)key; /* gcc is broken. */
	TOTAL *= value;
}

void test_for_each()
{
	struct avl_tree_node* root;
	root = avl_tree_create();
	avl_tree_insert(root, "aaa", 3);
	avl_tree_insert(root, "vesa", 5);
	avl_tree_insert(root, "esa", 7);
	TOTAL = 1;
	avl_tree_for_each(root, test_function);
	assertIntEquals(3*5*7, TOTAL);

	avl_tree_destroy(root);
}

void test_increasing()
{
	struct avl_tree_node* root;
	root = avl_tree_create();
	avl_tree_increase(root, "moi");
	avl_tree_increase(root, "hello");
	avl_tree_increase(root, "abc");
	avl_tree_increase(root, "hello");
	avl_tree_increase(root, "hello");
	avl_tree_increase(root, "eee");
	avl_tree_increase(root, "moi");
	assertIntEquals(3, *avl_tree_find(root, "hello"));
	assertIntEquals(1, *avl_tree_find(root, "abc"));
	assertIntEquals(2, *avl_tree_find(root, "moi"));
	assertIntEquals(1, *avl_tree_find(root, "eee"));
	assertNull(avl_tree_find(root, "dummy"));

	avl_tree_destroy(root);
}

int main(void)
{
	test_creation();
	test_finding();
	test_inserting_and_finding();

	test_that_keys_are_copied();
	test_for_each();
	test_increasing();

	return 0;
}

