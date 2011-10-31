#include "avl_tree.h"

#include <assert.h>
#include <string.h>
#include <stdlib.h>

#ifndef max
    #define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif

struct avl_tree_node {
    char* key;
    int value;

    int height;
    struct avl_tree_node* left;
    struct avl_tree_node* right;
};

static int invariant(struct avl_tree_node* node);
static int height(struct avl_tree_node* node);

/* When this is defined as 1, the binary search tree is balanced; otherwise it is not balanced. */
#define AVL_BALANCE 1

#if AVL_BALANCE == 1
static struct avl_tree_node* single_rotate_right(struct avl_tree_node* root);
static struct avl_tree_node* rotate_right_left(struct avl_tree_node* root);
static struct avl_tree_node* single_rotate_left(struct avl_tree_node* root);
static struct avl_tree_node* rotate_left_right(struct avl_tree_node* root);
static int balance(struct avl_tree_node* node);
#endif
static struct avl_tree_node* balance_update(struct avl_tree_node* node);


/*
 * Returns 1 if the tree is in valid shape and 0 otherwise.
 */
int invariant(struct avl_tree_node* node)
{
    if(!node) {
        return 0;
    }

    if(!node->key) {
        if(node->height != 0) {
            assert(0);
        }
        if(node->left || node->right || node->height != 0) {
            return 0;
        }
        return 1;
    }

    if(node->height != max(height(node->left), height(node->right)) + 1) {
        return 0;
    }
#if AVL_BALANCE == 1
    if(balance(node) > 1 || balance(node) < -1) {
        return 0;
    }
#endif

    return (!node->left || invariant(node->left)) && (!node->right || invariant(node->right));
}


struct avl_tree_node* avl_tree_create()
{
    struct avl_tree_node* root = malloc(sizeof(struct avl_tree_node));
    if(!root) {
        return NULL;
    }

    root->height = 0;
    root->key = NULL;
    root->value = 0;
    root->left = NULL;
    root->right = NULL;

    assert(invariant(root));

    return root;
}

void avl_tree_destroy(struct avl_tree_node* root)
{
    assert(invariant(root));

    if (root->right != NULL) {
        avl_tree_destroy(root->right);
    }

    if (root->left != NULL) {
        avl_tree_destroy(root->left);
    }

    if(root->key) {
        free(root->key);
    }
    free(root);
}

int height(struct avl_tree_node* node)
{
    return node ? node->height : 0;
}

struct avl_tree_node* balance_update(struct avl_tree_node* node)
{
    struct avl_tree_node* new_root = node;
#if AVL_BALANCE == 1
    int bal = balance(node);

    assert(bal >= -2 && bal <= 2);

    if(bal == -2) {
        int bal_right = balance(node->right);
        if(bal_right == -1) {
            new_root = single_rotate_left(node);
        } else {
            assert(bal_right == 1);
            new_root = rotate_right_left(node);
        }
    } else if(bal == 2) {
        int bal_left = balance(node->left);
        if(bal_left == 1) {
            new_root = single_rotate_right(node);
        } else {
            assert(bal_left == -1);
            new_root = rotate_left_right(node);
        }
    }
#endif
    assert(invariant(new_root));
    return new_root;
}

#if AVL_BALANCE == 1
struct avl_tree_node* single_rotate_left(struct avl_tree_node* root)
{
    struct avl_tree_node* node = root->right;
    root->right = node->left;
    node->left = root;

    root->height = max(height(root->left), height(root->right)) + 1;
    node->height = max(height(node->left), height(node->right)) + 1;
    return node;
}

struct avl_tree_node* single_rotate_right(struct avl_tree_node* root)
{
    struct avl_tree_node* node = root->left;
    root->left = node->right;
    node->right = root;

    root->height = max(height(root->left), height(root->right)) + 1;
    node->height = max(height(node->left), height(node->right)) + 1;
    return node;
}

struct avl_tree_node* rotate_right_left(struct avl_tree_node* root)
{
    root->right = single_rotate_right(root->right);
    return  single_rotate_left(root);
}

struct avl_tree_node* rotate_left_right(struct avl_tree_node* root)
{
    root->left = single_rotate_left(root->left);
    return single_rotate_right(root);
}

int balance(struct avl_tree_node* node)
{
    return node ? height(node->left) - height(node->right) : 0;
}

#endif

struct avl_tree_node* avl_tree_insert(struct avl_tree_node* root, const char* key, int value)
{
    assert(invariant(root));

    if (!root->key) {
        root->key = malloc(strlen(key) + 1);
        strcpy(root->key, key);
        root->value = value;
        root->height = 1;

        assert(invariant(root));
        return root;
    }

    int comparison = strcmp(key, root->key);
    if (comparison < 0) {
        if (root->left == NULL) {
            root->left = avl_tree_create();
        }
        root->left = avl_tree_insert(root->left, key, value);
        root->height = max(height(root->left), height(root->right)) + 1;

        return balance_update(root);
    } else if (comparison > 0) {
        if (root->right == NULL) {
            root->right = avl_tree_create();
        }
        root->right = avl_tree_insert(root->right, key, value);
        root->height = max(height(root->left), height(root->right)) + 1;

        return balance_update(root);
    } else {
        root->value = value;
        return root;
    }
}

int* avl_tree_find(struct avl_tree_node* root, const char* key)
{
    assert(invariant(root));

    if (!root->key) {
        return NULL;
    }

    int comparison = strcmp(key, root->key);
    if (comparison < 0) {
        if (root->left == NULL) {
            return NULL;
        } else {
            return avl_tree_find(root->left, key);
        }
    } else if (comparison > 0) {
        if (root->right == NULL) {
            return NULL;
        } else {
            return avl_tree_find(root->right, key);
        }
    } else {
        return &root->value;
    }
}


void avl_tree_for_each(struct avl_tree_node* root, void (*function)(const char* key, int value))
{
    assert(invariant(root));

    if (root->left) {
        avl_tree_for_each(root->left, function);
    }
    if(root->key) {
        function(root->key, root->value);
    }

    if (root->right) {
        avl_tree_for_each(root->right, function);
    }

    assert(invariant(root));
}

struct avl_tree_node* avl_tree_increase(struct avl_tree_node* root, const char* key)
{
    assert(invariant(root));

    int* newvalue = avl_tree_find(root, key);

    if (!newvalue) {
        return avl_tree_insert(root, key, 1);
    } else {
        ++*newvalue;
        return root;
    }
}

