#include "map_internal.h"

void rotate_left(map_t* map, rb_node_t* x) {
    rb_node_t* y = x->right;
    x->right = y->left;
    if (y->left != map->nil)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == map->nil)
        map->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void rotate_right(map_t* map, rb_node_t* y) {
    rb_node_t* x = y->left;
    y->left = x->right;
    if (x->right != map->nil)
        x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == map->nil)
        map->root = x;
    else if (y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left = x;
    x->right = y;
    y->parent = x;
}
