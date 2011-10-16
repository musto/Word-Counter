#include "test.h"
#include "avl_tree.h"

void test_creation()
{
	struct avl_tree_node* root;

	root = avl_tree_create("esa", 0);
	avl_tree_destroy(root);
}

void test_finding()
{
	struct avl_tree_node* root;
	int* value;

	root = avl_tree_create("esa", 3);

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

	root = avl_tree_create("esa", 3);
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

int main(void)
{
	test_creation();
	test_finding();
	test_inserting_and_finding();

	return 0;
}

