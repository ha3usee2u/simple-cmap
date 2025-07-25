#include <string.h>
#include "map_internal.h"

// 比較整數：升序
int map_cmp_int(void* a, void* b) {
    return *(int*)a - *(int*)b;
}

// 比較字串：使用 strcmp
int map_cmp_str(void* a, void* b) {
    return strcmp((char*)a, (char*)b);
}

// 自訂結構（例如 my_key_t）的比較範例
int map_cmp_mykey(void* a, void* b) {
    typedef struct { int id; char* label; } my_key_t;
    my_key_t* ka = (my_key_t*)a;
    my_key_t* kb = (my_key_t*)b;

    if (ka->id != kb->id) return ka->id - kb->id;
    return strcmp(ka->label, kb->label);
}
