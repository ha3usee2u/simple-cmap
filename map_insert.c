#include "map_internal.h"

// 插入修復紅黑樹性質
void rb_insert_fixup(map_t *map, rb_node_t *node)
{
    while (node->parent->color == RED)
    {
        int is_left = (node->parent == node->parent->parent->left);
        rb_node_t *uncle =
            is_left ? node->parent->parent->right : node->parent->parent->left;

        if (uncle->color == RED)
        {
            node->parent->color = BLACK;
            uncle->color = BLACK;
            node->parent->parent->color = RED;
            node = node->parent->parent;
        }
        else
        {
            if ((is_left && node == node->parent->right) ||
                (!is_left && node == node->parent->left))
            {
                node = node->parent;
                is_left ? rotate_left(map, node) : rotate_right(map, node);
            }
            node->parent->color = BLACK;
            node->parent->parent->color = RED;
            is_left ? rotate_right(map, node->parent->parent)
                    : rotate_left(map, node->parent->parent);
        }
    }
    map->root->color = BLACK;
}

// 插入節點到紅黑樹中
int rb_insert(map_t *map, key_t key, value_t value)
{
    rb_node_t *node = map->root;
    rb_node_t *parent = map->nil;

    while (node != map->nil)
    {
        parent = node;
        int cmp = map->cmp_func(key, node->key);

        if (cmp == 0)
        {
            // 替換 value，但記得釋放原來的（若 map 有清理函式）
            if (map->cleanup_fn)
                map->cleanup_fn(node->key, node->value);
            node->key = key; // 更新 key
            node->value = value;
            return 0; // 替換成功，不需要插入新節點
        }
        node = (cmp < 0) ? node->left : node->right;
    }

    // 建立新節點並插入
    rb_node_t *new_node = rb_node_create(map, key, value);
    new_node->parent = parent;

    if (parent == map->nil)
        map->root = new_node;
    else if (map->cmp_func(key, parent->key) < 0)
        parent->left = new_node;
    else
        parent->right = new_node;

    rb_insert_fixup(map, new_node);
    return 1; // 插入成功
}
