#include "avl_tree.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

struct avl_tree_node {
    const char* key;
    int value;

    int height;
    struct avl_tree_node* left;
    struct avl_tree_node* right;
};

struct avl_tree_node* avl_tree_create() {
    struct avl_tree_node* root = malloc(sizeof(struct avl_tree_node));
    root->height = 0;
    root->key = NULL;
    root->value = 0;
    root->left = NULL;
    root->right = NULL;
    return root;
}

void avl_tree_destroy(struct avl_tree_node* root) {
    if (root->right != NULL) {
        avl_tree_destroy(root->right);
    }

    if (root->left != NULL) {
        avl_tree_destroy(root->left);
    }
    free(root);
}

static void single_rotate_right(struct avl_tree_node* root) {

}

static void double_rotate_right(struct avl_tree_node* root) {


}

static void single_rotate_left(struct avl_tree_node* root) {
}

static void double_rotate_left(struct avl_tree_node* root) {
}

void avl_tree_insert(struct avl_tree_node* root, const char* key, int value) {
    int comparison;
    assert(root);

    if (!root->key) {
        assert(root->left == NULL);
        assert(root->right == NULL);

        root->key = key;
        root->value = value;
        return;
    }

    comparison = strcmp(key, root->key);
    if (comparison < 0) {
        if (root->left == NULL) {
            root->left = avl_tree_create();
        }
        avl_tree_insert(root->left, key, value);
    } else if (comparison > 0) {
        if (root->right == NULL) {
            root->right = avl_tree_create();
        }
        avl_tree_insert(root->right, key, value);
    } else {
        root->value = value;;
    }
}

int* avl_tree_find(struct avl_tree_node* root, const char* key) {
    int comparison;
    assert(root);
    if (!root->key) {
        assert(root->left == NULL);
        assert(root->right == NULL);

        return NULL;
    }
    comparison = strcmp(key, root->key);
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


void avl_tree_for_each(struct avl_tree_node* root, void (*f)(const char* key, int value))
{
    f(root->key, root->value);
}

void avl_tree_increase(struct avl_tree_node* root, const char* key)
{
}

