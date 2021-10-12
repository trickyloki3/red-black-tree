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
    if(rbt->node == NULL)
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

int rbt_add(struct rbt * rbt, void * key, void * value) {
    int p;
    int n;
    int c;

    int g;
    int s;

    p = 0;
    n = rbt->root;
    while(n) {
        p = n;
        c = rbt->compare(key, rbt->node[n].key);
        if(c < 0) {
            n = rbt->node[n].left;
        } else if(c > 0) {
            n = rbt->node[n].right;
        } else {
            return panic("duplicate key");
        }
    }

    if(rbt->next >= rbt->size)
        return panic("out of memory");

    n = rbt->next++;

    rbt->node[n].key = key;
    rbt->node[n].value = value;
    rbt->node[n].color = red;
    rbt->node[n].left = 0;
    rbt->node[n].right = 0;
    rbt->node[n].parent = p;

    if(p) {
        if(c < 0) {
            rbt->node[p].left = n;
        } else {
            rbt->node[p].right = n;
        }
    } else {
        rbt->root = n;
    }

    while(rbt->node[p].color == red) {
        g = rbt->node[p].parent;
        if(rbt->node[g].left == p) {
            s = rbt->node[g].right;
            if(rbt->node[s].color == red) {
                rbt->node[p].color = black;
                rbt->node[g].color = red;
                rbt->node[s].color = black;
                n = g;
                p = rbt->node[g].parent;
            } else {
                if(rbt->node[p].right == n) {
                    left_rotate(rbt, p, n);
                    p = n;
                }
                rbt->node[p].color = black;
                rbt->node[g].color = red;
                right_rotate(rbt, g, p);
            }
        } else {
            s = rbt->node[g].left;
            if(rbt->node[s].color == red) {
                rbt->node[p].color = black;
                rbt->node[g].color = red;
                rbt->node[s].color = black;
                n = g;
                p = rbt->node[g].parent;
            } else {
                if(rbt->node[p].left == n) {
                    right_rotate(rbt, p, n);
                    p = n;
                }
                rbt->node[p].color = black;
                rbt->node[g].color = red;
                left_rotate(rbt, g, p);
            }
        }
    }

    rbt->node[rbt->root].color = black;

    return 0;
}

int rbt_remove(struct rbt * rbt, void * key) {
    int x;
    int c;

    x = rbt->root;
    while(x) {
        c = rbt->compare(key, rbt->node[x].key);
        if(c < 0) {
            x = rbt->node[x].left;
        } else if(c > 0) {
            x = rbt->node[x].right;
        } else {
            break;
        }
    }

    if(x == 0)
        return panic("invalid key");

    return 0;
}

void * rbt_search(struct rbt * rbt, void * key) {
    int n;
    int c;

    n = rbt->root;
    while(n) {
        c = rbt->compare(key, rbt->node[n].key);
        if(c < 0) {
            n = rbt->node[n].left;
        } else if(c > 0) {
            n = rbt->node[n].right;
        } else {
            return rbt->node[n].value;
        }
    }

    return NULL;
}
