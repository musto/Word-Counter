#ifndef INT_COUNTS_H
#define INT_COUNTS_H
/*
 * Int_counts is used to store words and sentences and perform basic functions.
 * The methods are create, add, get, destroy, min and max.
 */

struct int_counts;
/*
 * Creates a new int_counts struct.
 */
struct int_counts* int_counts_create(void);
/*
 * Add function is basically like the increase function in AVL_tree: it increases 
 * the value of a node by one. Parameter key indicates the index of the node, and
 * container the struct. Also checks if the value of the node is higher
 * or lower than current min or max, and updates them if required. Returns void.
 */
void int_counts_add(struct int_counts* container, int key);
/*
 * Get function returns the node in the index of the parameter key.
 */
int int_counts_get(struct int_counts* container, int key);
/*
 * Total functions returns the number of times the add function has been
 * called for the given container.
 */
int int_counts_total(struct int_counts* container);
/*
 * Min function returns the lowest value of all of the nodes.
 */
int int_counts_min(struct int_counts* container);
/*
 * Max function returns the highest value of all of the nodes.
 */
int int_counts_max(struct int_counts* container);
/*
 * Destroy function frees the memory of the container.
 */
void int_counts_destroy(struct int_counts* container);

#endif

