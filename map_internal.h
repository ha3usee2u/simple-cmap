#ifndef GUANGONGDOUDIANTOU_SIMPLE_C_MAP_INTERNAL_H
#define GUANGONGDOUDIANTOU_SIMPLE_C_MAP_INTERNAL_H

#include <stdlib.h>

// 顏色類型：紅黑樹節點顏色
typedef enum { RED, BLACK } color_t;

// 泛型 key/value 類型
typedef void* key_t;
typedef void* value_t;

// key 比較函式指針
typedef int (*cmp_func_t)(key_t, key_t);

// key/value 清理函式指針
typedef void (*map_free_fn)(key_t, value_t);

// 紅黑樹節點定義
typedef struct rb_node {
    key_t key;
    value_t value;
    color_t color;
    struct rb_node* left;
    struct rb_node* right;
    struct rb_node* parent;
} rb_node_t;

// map 主結構體
typedef struct map {
    rb_node_t* root;
    rb_node_t* nil;
    cmp_func_t cmp_func;
    map_free_fn cleanup_fn;
} map_t;

// ✨ ✅ 內部函式宣告（避免 implicit declaration warning）
map_t* rb_create(cmp_func_t cmp_func);
rb_node_t* rb_search(map_t* map, key_t key);
int rb_insert(map_t* map, key_t key, value_t value);
int rb_delete(map_t* map, key_t key);
void rotate_left(map_t* map, rb_node_t* node);
void rotate_right(map_t* map, rb_node_t* node);
rb_node_t* rb_node_create(map_t* map, key_t key, value_t value);
void map_destroy_with(map_t* map, map_free_fn destroy_fn);
void map_destroy(map_t* map);

#endif
