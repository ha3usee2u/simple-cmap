#include "c-map.h"

//建立紅黑樹的節點，在執行map_insert時用到
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

//建立map的核心
//其中cmp_func作為一個function pointer指向自定義比較的函數
extern map_t* map_create(cmp_func_t cmp_func) {
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

//清除節點的資源
void rb_node_destroy(rb_node_t* node) {
    free(node);
}

//清除整個map的資源，循環刪除map上的任何節點
extern void map_destroy(map_t* map) {
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

//使用指定的key查詢指定map上的對應value
extern rb_node_t* map_search(map_t* map, int key) {
    rb_node_t* node = map -> root;
    while (node != map -> nil) {
        int cmp = map -> cmp_func(key, node -> key);
        if (cmp == 0) {
            return node;
        }
        else if (cmp < 0) {
            node = node -> left;
        }
        else {
            node = node -> right;
        }
    }

    return map -> nil;
}

//針對node、node右子節點的換位，node變成(node右子節點)的左子節點
void rotate_left(map_t* map, rb_node_t* node) {
    rb_node_t* right = node -> right;
    node -> right = right -> left;
    if (right -> left != map -> nil) {
        right -> left -> parent = node;
    }

    right -> parent = node -> parent;

    //當node原本為頂點的情況
    if (node -> parent == map -> nil) {
        map -> root = right;
    }
    //由node右子節點取代原本node在親代節點的位置
    else if (node == node -> parent -> left) {
        node -> parent -> left = right;
    }
    else {
        node -> parent -> right = right;
    }

    right -> left = node;
    node -> parent = right;
}

//針對node、node左子節點的換位，node變成(node左子節點)的右子節點
void rotate_right(map_t* map, rb_node_t* node) {
    rb_node_t* left = node -> left;
    node -> left = left -> right;
    if (left -> right != map -> nil) {
        left -> right -> parent = node;
    }

    left -> parent = node -> parent;
    
    //當node原本為頂點的情況
    if (node -> parent == map -> nil) {
        map -> root = left;
    }
    //由node左子節點取代原本node在親代節點的位置
    else if (node == node -> parent -> right) {
        node -> parent -> right = left;
    }
    else {
        node -> parent -> right = left;
    }

    left -> right = node;
    node -> parent = left;
}

void rb_insert_fixup(map_t* map, rb_node_t* node) {
    while (node -> parent -> color == RED) {
        if (node -> parent == node -> parent -> parent -> left) {
            rb_node_t* uncle = node -> parent -> parent -> right;
            if (uncle -> color == RED) {
                node -> parent -> color = BLACK;
                uncle -> color = BLACK;
                node -> parent -> parent -> color = RED;
                node = node -> parent -> parent;
            }
            else {
                if (node == node -> parent -> right) {
                    node = node -> parent;
                    rotate_left(map, node);
                }

                node -> parent -> color = BLACK;
                node -> parent -> parent -> color = RED;
                rotate_right(map, node -> parent -> parent);
            }
        }
        else {
            rb_node_t* uncle = node -> parent -> parent -> left;
            if (uncle -> color == RED) {
                node -> parent -> color = BLACK;
                uncle -> color = BLACK;
                node -> parent -> parent -> color = RED;
                node = node -> parent -> parent;
            }
            else {
                if (node == node -> parent -> left) {
                    node = node -> parent;
                    rotate_right(map, node);
                }

                node -> parent -> color = BLACK;
                node -> parent -> parent -> color = RED;
                rotate_left(map, node -> parent -> parent);
            }
        }
    }

    map -> root -> color = BLACK;
}

//在map裡插入一個節點(key: value)，並按照紅黑樹的規則平衡
extern void map_insert(map_t* map, int key, void* value) {
    rb_node_t* parent = map -> nil;
    rb_node_t* node = map -> root;
    while (node != map -> nil) {
        parent = node;

        //加入自定義的比較函數作為排序的原則
        int cmp = map -> cmp_func(key, node -> key);
        if (cmp < 0) {  
            node = node -> left;
        }
        else if (cmp > 0) {
            node = node -> right;
        }
        //如果在指定的map裡找到與key相同的節點，則更新其對應的value，不新增節點
        else {
            node -> value = value;
            return;
        }
    }
    
    //找到存放的位置後，建立節點
    rb_node_t* new_node = rb_node_create(map, key, value);
    new_node -> parent = parent;
    
    if (parent == map -> nil) {
        map -> root = new_node;
    }
    else if (key < parent -> key) {
        parent -> left = new_node;
    }
    else {
        parent -> right = new_node;
    }

    rb_insert_fixup(map, new_node);
}

void rb_transplant(map_t* map, rb_node_t* u, rb_node_t* v) {
    if (u -> parent == map -> nil) {
        map -> root = v;
    }
    else if (u == u -> parent -> left) {
        u -> parent -> left = v;
    }
    else {
        u -> parent -> left = v;
    }

    v -> parent = u -> parent;
}

rb_node_t* rb_minimum(map_t* map, rb_node_t* node) {
    while (node -> left != map -> nil) {
        node = node -> left;
    }

    return node;
}

void rb_delete_fixup(map_t* map, rb_node_t* x) {
    while (x != map -> root && x -> color == BLACK) {
        if (x == x -> parent -> left) {
            rb_node_t* w = x -> parent -> right;
            if (w -> color == RED) {
                w -> color = BLACK;
                x -> parent -> color = RED;
                rotate_left(map, x -> parent);
                w = x -> parent -> right;
            }

            if (w -> left -> color == BLACK && w -> right -> color == BLACK) {
                w -> color = RED;
                x = x -> parent;
            }
            else {
                if (w -> right -> color == BLACK) {
                    w -> left -> color = BLACK;
                    w -> color = RED;
                    rotate_right(map, w);
                    w = x -> parent -> right;
                }

                w -> color = x -> parent -> color;
                x -> parent -> color = BLACK;
                w -> right -> color = BLACK;
                rotate_left(map, x -> parent);
                x = map -> root;
            }
        }
        else {
            rb_node_t* w = x -> parent -> left;
            if (w -> color == RED) {
                w -> color = BLACK;
                x -> parent -> color = RED;
                rotate_right(map, x -> parent);
                w = x -> parent -> left;
            }

            if (w -> right -> color == BLACK && w -> left -> color == BLACK) {
                w -> color = RED;
                x = x -> parent;
            }
            else {
                if (w -> left -> color == BLACK) {
                    w -> right -> color = BLACK;
                    w -> color = RED;
                    rotate_left(map, w);
                    w = x -> parent -> left;
                }

                w -> color = x -> parent -> color;
                x -> parent -> color = BLACK;
                w -> left -> color = BLACK;
                rotate_right(map, x -> parent);
                x = map -> root;
            }
        }
    }

    x -> color = BLACK;
}

extern void map_delete(map_t* map, int key) {
    rb_node_t* node = map_search(map, key);
    
    if (node == map -> nil) {
        return;
    }

    rb_node_t* y = node;
    color_t y_original_color = y -> color;
    rb_node_t* x;
    
    if (node -> left == map -> nil) {
        x = node -> right;
        rb_transplant(map, node, node -> right);
    }
    else if (node -> right == map -> nil) {
        x = node -> left;
        rb_transplant(map, node, node -> left);
    }
    else {
        y = rb_minimum(map, node -> right);
        y_original_color = y -> color;
        x = y -> right;

        if (y -> parent == node) {
            x -> parent = y;
        }
        else {
            rb_transplant(map, y, y -> right);
            y -> right = node -> right;
            y -> right -> parent = y;
        }

        rb_transplant(map, node, y);
        y -> left = node -> left;
        y -> left -> parent = y;
        y -> color = node -> color;
    }

    if (y_original_color == BLACK) {
        rb_delete_fixup(map, x);
    }

    rb_node_destroy(node);
}

extern int map_cmp_int(int key1, int key2) {
        if (key1 < key2) {
            return -1;
        }
        else if (key1 > key2) {
            return 1;
        }
        else {
            return 0;
        }
}