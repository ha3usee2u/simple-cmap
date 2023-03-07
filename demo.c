#include "c-map.h"


int main() {
    
    map_t* my_map = map_create(map_cmp_int);
    int a[3] = { 1, 2, 3 };
    
    map_insert(my_map, 20, "hello");
    map_insert(my_map, 10, "world");
    map_insert(my_map, 30, "@");
    map_insert(my_map, 40, "!");
    map_insert(my_map, 50, "#");

    printf("%s ", map_search(my_map, 20) -> value);
    printf("%s ", map_search(my_map, 10) -> value);

    //根據紅黑樹規則，輸出"!"
    printf("%s ", map_search(my_map, 20) -> right -> value);

    map_delete(my_map, 40);
    printf("%s ", map_search(my_map, 40) -> value);

    return 0;
}