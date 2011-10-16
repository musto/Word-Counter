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

int main(void)
{
	test_creation();
	test_finding();

	return 0;
}

