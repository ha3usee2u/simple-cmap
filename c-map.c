#include <c-map.h>

rb_node_t* rb_node_create(map_t* map, int key, void* value) {
    rb_node_t* node = malloc(sizeof(rb_node_t));
    node -> left = map -> nil;
    node -> right = map -> nil;
    node -> parent = map -> nil;
    node -> color = RED;
    node -> key = key;
    node -> value = value;
    return node;
}

map_t* map_create(cmp_func_t cmp_func) {
    map_t* map = malloc(sizeof(map_t));
    rb_node_t* nil = malloc(sizeof(rb_node_t));
    
    nil -> left = nil;
    nil -> right = nil;
    nil -> parent = nil;
    nil -> color = BLACK;
    nil -> key = 0;
    nil -> value = NULL;

    map -> root = nil;
    map -> nil = nil;
    map -> cmp_func = cmp_func;

    return map;
}

void rb_node_destroy(rb_node_t* node) {
    free(node);
}

void map_destroy(map_t* map) {
    rb_node_t* node = map -> root;
    while (node != map -> nil) {
        if (node -> left != map -> nil) {
            node = node -> left;
        }
        else if (node -> right != map -> nil) {
            node = node -> right;
        }
        else {
            rb_node_t* parent = node -> parent;
            if (parent != map -> nil) {
                if (parent -> left == node) {
                    parent -> left = map -> nil;
                }
                else {
                    parent -> right = map -> nil;
                }
            }
            
            rb_node_destroy(node);
            node = parent;
        }
    }

    free(map -> nil);
    free(map);
}
