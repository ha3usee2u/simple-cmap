#include "map_internal.h"

// 查找最小節點
rb_node_t* rb_minimum(map_t* map, rb_node_t* node) {
    while (node->left != map->nil)
        node = node->left;
    return node;
}

// 節點替換（transplant）
void rb_transplant(map_t* map, rb_node_t* u, rb_node_t* v) {
    if (u->parent == map->nil)
        map->root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
}

// 刪除修復：確保紅黑樹性質維持
void rb_delete_fixup(map_t* map, rb_node_t* x) {
    while (x != map->root && x->color == BLACK) {
        int is_left = (x == x->parent->left);
        rb_node_t* w = is_left ? x->parent->right : x->parent->left;

        if (w->color == RED) {
            w->color = BLACK;
            x->parent->color = RED;
            is_left ? rotate_left(map, x->parent) : rotate_right(map, x->parent);
            w = is_left ? x->parent->right : x->parent->left;
        }

        if ((w->left->color == BLACK) && (w->right->color == BLACK)) {
            w->color = RED;
            x = x->parent;
        } else {
            if ((is_left && w->right->color == BLACK) || (!is_left && w->left->color == BLACK)) {
                if (is_left) w->left->color = BLACK;
                else w->right->color = BLACK;
                w->color = RED;
                is_left ? rotate_right(map, w) : rotate_left(map, w);
                w = is_left ? x->parent->right : x->parent->left;
            }

            w->color = x->parent->color;
            x->parent->color = BLACK;
            if (is_left) w->right->color = BLACK;
            else w->left->color = BLACK;
            is_left ? rotate_left(map, x->parent) : rotate_right(map, x->parent);
            x = map->root;
        }
    }
    x->color = BLACK;
}

// 刪除節點主流程
int rb_delete(map_t* map, key_t key) {
    rb_node_t* z = rb_search(map, key);
    if (z == map->nil) return 0;

    rb_node_t *y = z, *x;
    color_t y_original_color = y->color;

    if (z->left == map->nil) {
        x = z->right;
        rb_transplant(map, z, z->right);
    } else if (z->right == map->nil) {
        x = z->left;
        rb_transplant(map, z, z->left);
    } else {
        y = rb_minimum(map, z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z)
            x->parent = y;
        else {
            rb_transplant(map, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        rb_transplant(map, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (y_original_color == BLACK)
        rb_delete_fixup(map, x);

    if (map->cleanup_fn)
        map->cleanup_fn(z->key, z->value);
    free(z);
    return 1;
}
