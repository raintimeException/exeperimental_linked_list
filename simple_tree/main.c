#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct tnode_t {
    int data;
    struct tnode_t *l, *r;
} tnode_t;

tnode_t *create_node(void)
{
    tnode_t *t = (tnode_t *)malloc(sizeof(tnode_t));
    assert(t != NULL);
    fprintf(stdout, "Insert data (int):\n");
    fscanf(stdin, "%d", &t->data);
    t->l = t->r = NULL;
    return t;
}

void put_node(tnode_t *root, tnode_t *n)
{
    if (root->data > n->data) {
        if (root->l != NULL)
            put_node(root->l, n);
        else
            root->l = n;
    } else {
        if (root->r != NULL)
            put_node(root->r, n);
        else
            root->r = n;
    }
}

void print_nodes(tnode_t *root)
{
    tnode_t *t = root;
    fprintf(stdout, "root: %d\n", t->data);
    for (t = root->l; t != NULL; t = t->l)
        fprintf(stdout, "l: %d ", t->data);
    fprintf(stdout, "\n");
    for (t = root->r; t != NULL; t = t->r)
        fprintf(stdout, "r: %d ", t->data);
    fprintf(stdout, "\n");
}

int main(void)
{
    char decision;
    tnode_t *root = NULL, *t = NULL;

    do {
        t = create_node();
        if (!root)
            root = t;
        else
            put_node(root, t);

        fprintf(stdout, "Do you want to continue (Y/N)?\n");
        fscanf(stdin, "%s", &decision);
    } while (decision == 'Y' || decision == 'y');
    print_nodes(root);
    return 0;
}
