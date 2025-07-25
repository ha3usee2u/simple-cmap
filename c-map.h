#ifndef GUANGONGDOUDIANTOU_SIMPLE_C_MAP
#define GUANGONGDOUDIANTOU_SIMPLE_C_MAP

#include <stdio.h>
#include <stddef.h>  // for size_t

#ifdef __cplusplus
extern "C" {
#endif

// 類型別名（由 map_internal 提供）
typedef void* key_t;
typedef void* value_t;
typedef struct map map_t;
typedef int (*cmp_func_t)(key_t, key_t);
typedef void (*map_free_fn)(key_t, value_t);

// 建立與釋放
map_t* map_create(cmp_func_t cmp_func, map_free_fn cleanup_fn);
void map_free(map_t* map);

// 操作函式
int map_insert(map_t* map, key_t key, value_t value);
value_t map_get(map_t* map, key_t key);
int map_remove(map_t* map, key_t key);
int map_contains(map_t* map, key_t key);

// 枚舉與工具
void map_foreach(map_t* map, void (*callback)(key_t, value_t));
key_t* map_keys(map_t* map, size_t* out_count);

// （可選：延伸功能）
value_t* map_values(map_t* map, size_t* out_count);
void map_clear(map_t* map);
size_t map_size(map_t* map);

#ifdef __cplusplus
}
#endif

#endif
