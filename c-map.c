#include "c-map.h"
#include "map_internal.h" // 包含 map_t 和 rb_node 結構定義與內部函式

map_t *map_create(cmp_func_t cmp_func, map_free_fn cleanup_fn)
{
    if (!cmp_func)
        return NULL; // 確保比較函式不為 NULL
    map_t *map = malloc(sizeof(map_t));
    if (!map)
        return NULL; // 分配失敗

    map->nil = malloc(sizeof(rb_node_t)); // 需初始化 nil 節點
    map->nil->color = BLACK;
    map->nil->left = map->nil->right = map->nil->parent = NULL;

    map->root = map->nil;
    map->cmp_func = cmp_func;
    map->cleanup_fn = cleanup_fn;
    return map;
}

static void cleanup(rb_node_t *node, map_t *map)
{
    if (node == map->nil)
        return;
    cleanup(node->left, map);
    cleanup(node->right, map);
    if (map->cleanup_fn)
        map->cleanup_fn(node->key, node->value);
    free(node);
}

void map_free(map_t *map)
{
    if (!map)
        return;
    cleanup(map->root, map);
    free(map->nil);
    free(map);
}

int map_insert(map_t *map, key_t key, value_t value)
{
    if (!map || !key)
        return -1; // 檢查 map 和 key 是否有效
    // 呼叫你內部的 insert 函式
    return rb_insert(map, key, value);
}

value_t map_get(map_t *map, key_t key)
{
    if (!map || !key)
        return NULL; // 檢查 map 和 key 是否有效
    rb_node_t *node = rb_search(map, key);
    return (node != map->nil) ? node->value : NULL;
}

int map_contains(map_t *map, key_t key)
{
    if (!map || !key)
        return 0; // 檢查 map 和 key 是否有效
    return rb_search(map, key) != map->nil;
}

int map_remove(map_t *map, key_t key)
{
    if (!map || !key)
        return -1;              // 檢查 map 和 key 是否有效
    return rb_delete(map, key); // 你內部應該實作好這個
}

static void traverse(rb_node_t *node, void (*callback)(key_t, value_t),
                     rb_node_t *nil)
{
    if (node == nil)
        return;
    traverse(node->left, callback, nil);
    callback(node->key, node->value);
    traverse(node->right, callback, nil);
}

void map_foreach(map_t *map, void (*callback)(key_t, value_t))
{
    if (!map || !callback)
        return;
    traverse(map->root, callback, map->nil);
}

static void collect(rb_node_t *node, key_t **keys, size_t *count, size_t *cap,
                    rb_node_t *nil)
{
    if (node == nil)
        return;
    collect(node->left, keys, count, cap, nil);
    if (*count == *cap)
    {
        *cap *= 2;
        key_t *temp = realloc(*keys, *cap * sizeof(key_t));
        if (!temp)
        {
            perror("Key reallocation failed");
            exit(EXIT_FAILURE);
        }
        *keys = temp;
    }
    (*keys)[(*count)++] = node->key;
    collect(node->right, keys, count, cap, nil);
}

key_t *map_keys(map_t *map, size_t *out_count)
{
    if (!map)
        return NULL;

    size_t cap = 16, count = 0;
    key_t *keys = malloc(cap * sizeof(key_t));

    if (!keys)
    {
        perror("Failed to allocate initial key array");
        return NULL;
    }

    collect(map->root, &keys, &count, &cap, map->nil);
    if (out_count)
        *out_count = count;
    return keys;
}
