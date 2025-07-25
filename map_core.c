#include "map_internal.h"

rb_node_t* rb_node_create(map_t* map, key_t key, value_t value) {
    rb_node_t* node = malloc(sizeof(rb_node_t));
    node->key = key;
    node->value = value;
    node->color = RED;
    node->left = node->right = node->parent = map->nil;
    return node;
}

static void recurse(rb_node_t* node, map_free_fn destroy_fn, rb_node_t* nil) {
    if (node == nil) return;
    recurse(node->left, destroy_fn, nil);
    recurse(node->right, destroy_fn, nil);
    if (destroy_fn) destroy_fn(node->key, node->value);
    free(node);
}

void map_destroy_with(map_t* map, map_free_fn destroy_fn) {
    if (!map) return;
    recurse(map->root, destroy_fn, map->nil);
    free(map->nil);
    free(map);
}

void map_destroy(map_t* map) {
    map_destroy_with(map, map ? map->cleanup_fn : NULL);
}
