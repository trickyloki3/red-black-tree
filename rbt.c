#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "panic.c"

#include "rbt.h"

enum {
    red,
    black
};

static inline void change_heir(struct rbt *, int, int);
static inline void left_rotate(struct rbt *, int, int);
static inline void right_rotate(struct rbt *, int, int);

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

static inline void change_heir(struct rbt * rbt, int x, int y) {
    int i;

    i = rbt->node[x].parent;
    rbt->node[y].parent = i;
    if(i) {
        if(rbt->node[i].left == x) {
            rbt->node[i].left = y;
        } else {
            rbt->node[i].right = y;
        }
    } else {
        rbt->root = y;
    }
}

static inline void left_rotate(struct rbt * rbt, int x, int y) {
    int i;

    i = rbt->node[y].left;
    rbt->node[x].right = i;
    rbt->node[i].parent = x;

    change_heir(rbt, x, y);

    rbt->node[y].left = x;
    rbt->node[x].parent = y;
}

static inline void right_rotate(struct rbt * rbt, int x, int y) {
    int i;

    i = rbt->node[y].right;
    rbt->node[x].left = i;
    rbt->node[i].parent = x;

    change_heir(rbt, x, y);

    rbt->node[y].right = x;
    rbt->node[x].parent = y;
}
