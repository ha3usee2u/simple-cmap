#include "map_internal.h"

// 根據 key 在 map 中查找節點
rb_node_t* rb_search(map_t* map, key_t key) {
    rb_node_t* node = map->root;

    while (node != map->nil) {
        int cmp = map->cmp_func(key, node->key);

        if (cmp == 0)
            return node;

        node = (cmp < 0) ? node->left : node->right;
    }

    return map->nil; // 查無結果時回傳 nil 節點
}
