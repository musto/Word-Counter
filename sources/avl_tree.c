#include "avl_tree.h"

#include <stdlib.h>

struct avl_tree_node
{
	char* key;
	int value;

	int height;
	struct avl_tree_node* left;
	struct avl_tree_node* right;
};

struct avl_tree_node* avl_tree_create(char* key, int value) {
	return NULL;
}

void avl_tree_destroy(struct avl_tree_node* root) {
}

void avl_tree_insert(struct avl_tree_node* root, char* key, int value) {
}

int* avl_tree_find(struct avl_tree_node* root, char* key) {
	return 0;
}


