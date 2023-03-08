#ifndef __simple_c_map_h__
#define __simple_c_map_h__

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

rb_node_t* rb_node_create(map_t* map, int key, char* value);
map_t* map_create(cmp_func_t cmp_func);
void rb_node_destroy(rb_node_t* node);
void map_destroy(map_t* map);
rb_node_t* map_search(map_t* map, int key);
void rotate_left(map_t* map, rb_node_t* node);
void rotate_right(map_t* map, rb_node_t* node);
void rb_insert_fixup(map_t* map, rb_node_t* node);
void map_insert(map_t* map, int key, char* value);
void rb_transplant(map_t* map, rb_node_t* u, rb_node_t* v);
rb_node_t* rb_minimum(map_t* map, rb_node_t* node);
void rb_delete_fixup(map_t* map, rb_node_t* x);
void map_delete(map_t* map, int key);

int map_cmp_int(int key1, int key2);

#endif