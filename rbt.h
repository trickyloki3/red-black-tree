#ifndef rbt_h
#define rbt_h

typedef int (* rbt_compare) (const void *, const void *);

struct rbt_node {
    void * key;
    void * value;
    int color;
    int left;
    int right;
    int parent;
};

struct rbt {
    struct rbt_node * node;
    int root;
    int next;
    int size;
    rbt_compare compare;
};

int rbt_create(struct rbt *, int, rbt_compare);
void rbt_delete(struct rbt *);
int rbt_add(struct rbt *, void *, void *);
void * rbt_search(struct rbt *, void *);

#endif
