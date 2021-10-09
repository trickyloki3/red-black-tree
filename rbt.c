#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "panic.c"

#include "rbt.h"

enum {
    red,
    black
};

int rbt_create(struct rbt * rbt, int size, rbt_compare compare) {
    rbt->node = malloc(size * sizeof(*rbt->node));
    if(!rbt->node)
        return panic("out of memory");

    rbt->root = 0;
    rbt->next = 1;
    rbt->size = size;
    rbt->compare = compare;

    rbt->node[0].key = NULL;
    rbt->node[0].value = NULL;
    rbt->node[0].color = black;
    rbt->node[0].left = 0;
    rbt->node[0].right = 0;
    rbt->node[0].parent = 0;

    return 0;
}

void rbt_delete(struct rbt * rbt) {
    free(rbt->node);
}
