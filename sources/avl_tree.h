#ifndef AVL_TREE_H
#define AVL_TREE_H

/*
 * Contains AVL tree with create, destroy, insert, find, for-each and increase functions.
 * AVL tree is used to store the words and their appearances, as well as sentences of
 * different lengths.
 */

struct avl_tree_node;


/*
 * Creates an empty AVL tree.
 * Returns the root node.
 */
struct avl_tree_node* avl_tree_create(void);

/*
 * Destroys the tree freeing the memory recursively.
 * Parameter is the root of the tree.
 */
void avl_tree_destroy(struct avl_tree_node* root);

/*
 * Inserts a new node into the tree. 
 * Parameters are root, key and value. Key and value are assigned to the new node.
 * Returns void.
 */
void avl_tree_insert(struct avl_tree_node* root, const char* key, int value);

/*
 * Searches for a key in the tree.
 * Parameter is the key to be searched.
 * Returns the nodes value or NULL.
 */
int* avl_tree_find(struct avl_tree_node* root, const char* key);


void avl_tree_for_each(struct avl_tree_node* root, void (*f)(const char* key, int value));

/*
 * Increases the value of a node. Parameter key is the nodes key.
 * Returns void.
 */
void avl_tree_increase(struct avl_tree_node* root, const char* key);

#endif

