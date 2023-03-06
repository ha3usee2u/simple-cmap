#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK } color_t;

typedef struct rb_node {
    int key;
    void* value;

    color_t color;
    
    struct rb_node* left;
    struct rb_node* right;
    struct rb_node* parent;
} rb_node_t;

typedef int (*cmp_func_t)(int, int);

typedef struct map {
    rb_node_t* root;
    rb_node_t* nil;

    cmp_func_t cmp_func;
} map_t;

rb_node_t* rb_node_create(map_t* map, int key, void* value);
map_t* map_create(cmp_func_t cmp_func);
void rb_node_destroy(map_t* map, rb_node_t* node);
void map_destroy(map_t* map);
rb_node_t* rb_node_search(map_t* map, int key);