#include "c-map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Comparison function for string keys
int string_compare(void *a, void *b)
{
    return strcmp((char *)a, (char *)b);
}

// Cleanup function to free both key and value
void string_cleanup(void *key, void *value)
{
    free(key);
    free(value);
}

// Print key-value pair (used in map_foreach)
void print_pair(key_t key, value_t value)
{
    printf("Key: %s, Value: %s\n", (char *)key, (char *)value);
}

// Insert and verify retrieval and containment
void test_insert_and_lookup(map_t *map)
{
    char *k1 = strdup("apple");
    char *v1 = strdup("Apple");
    map_insert(map, k1, v1);

    char *k2 = strdup("banana");
    char *v2 = strdup("Banana");
    map_insert(map, k2, v2);

    char *k3 = strdup("orange");
    char *v3 = strdup("Orange");
    map_insert(map, k3, v3);

    printf("get('banana') = %s\n", (char *)map_get(map, "banana"));
    printf("contains('orange') = %d\n", map_contains(map, "orange"));
    printf("contains('grape') = %d\n", map_contains(map, "grape"));
}

// Overwrite test
void test_overwrite(map_t *map)
{
    char *new_val = strdup("Green Apple");
    map_insert(map, strdup("apple"), new_val);

    printf("get('apple') = %s\n", (char *)map_get(map, "apple"));
}

// Remove test
void test_removal(map_t *map)
{
    map_remove(map, "banana");

    printf("contains('banana') = %d\n", map_contains(map, "banana"));
    printf("get('banana') = %s\n", (char *)map_get(map, "banana"));
}

// Traverse map
void test_foreach(map_t *map)
{
    map_foreach(map, print_pair);
}

// Collect keys and free memory
void test_key_collection(map_t *map)
{
    size_t count = 0;
    key_t *keys = map_keys(map, &count);

    for (size_t i = 0; i < count; ++i)
    {
        printf("Key[%zu]: %s\n", i + 1, (char *)keys[i]);
    }

    free(keys);
}

int main(void)
{
    map_t *map = map_create(string_compare, string_cleanup);

    test_insert_and_lookup(map);
    test_overwrite(map);
    test_removal(map);
    test_foreach(map);
    test_key_collection(map);

    map_free(map);
    printf("\nMap successfully freed.\n");

    return 0;
}
