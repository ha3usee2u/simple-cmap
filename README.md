# simple-cmap
## Compile & Run demo
`gcc -o demo demo.c c-map.c`

`./demo`
## Usage
### Create a new map
`map_t* map_create(cmp_func_t cmp_func)`

`cmp_func` is the function for key comparison in the map, and the default is in ascending order.
###
### Insert the node into the map
`void map_insert(map_t* map, int key, char* value)`
###
### Search the node from the map
`rb_node_t* map_search(map_t* map, int key)`

The output is the node from the map. If the search failed, the output will be a nil node of map instead.
###
### Delete a node from the map
`void map_delete(map_t* map, int key)`
###
