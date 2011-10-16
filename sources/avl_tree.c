#include "avl_tree.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

struct avl_tree_node {
    char* key;
    int value;

    int height;
    struct avl_tree_node* left;
    struct avl_tree_node* right;
};

struct avl_tree_node* avl_tree_create(char* key, int value) {

    struct avl_tree_node* T = malloc(sizeof(struct avl_tree_node));
    T->height = 0;
    T->key = key;
    T->value = value;

    return T;
}

void avl_tree_destroy(struct avl_tree_node* root) {
    if (root->right != NULL)
        avl_tree_destroy(root->right);
    if (root->left != NULL)
        avl_tree_destroy(root->left);
    free(root);
}

void single_rotate_right(struct avl_tree_node* root) {

}

void double_rotate_right(struct avl_tree_node* root) {

}

void single_rotate_left(struct avl_tree_node* root) {

}

void double_rotate_left(struct avl_tree_node* root) {

}


void avl_tree_insert(struct avl_tree_node* root, char* key, int value) {
    assert(root);
    if (strcmp(key, root->key) < 0){
        if (root->left == NULL) {
            struct avl_tree_node* T = avl_tree_create(key, value);
            root->left = T;
        }
        avl_tree_insert(root->left, key, value);
    }
    if (strcmp(key, root->key) > 0){
        if (root->right == NULL) {
            struct avl_tree_node* T = avl_tree_create(key, value);
            root->right = T;
        }
        avl_tree_insert(root->right, key, value);
    }
    if (strcmp(key, root->key) == 0)
        root->value++;
}

int* avl_tree_find(struct avl_tree_node* root, char* key) {
    assert(root);
    if (strcmp(key, root->key) < 0)
        if (root->left == NULL)
            return 0;
        else
            return avl_tree_find(root->left, key);
    else
        if (strcmp(key, root->key) > 0)
        if (root->right == NULL)
            return 0;
        else
            return avl_tree_find(root->right, key);
    else
        return &root->value;
}




