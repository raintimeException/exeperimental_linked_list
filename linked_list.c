#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node {
    int val;
    struct node *next;
    struct node *prev;
} node;
node *head, *end;

void init_linked_list(void)
{
    head = (node *)malloc(sizeof(node *));
    assert(head != NULL);
    end = (node *)malloc(sizeof(node *));
    assert(head != NULL);
    head->val = 0;
    head->next = end;
    head->prev = NULL;
    end->val = 0;
    end->next = NULL;
    end->prev = head;
}

node *insert_before(node *n, int val)
{
    node *new = (node *)malloc(sizeof(node *));
    assert(new != NULL);

    new->prev = n->prev;
    n->prev->next = new;
    new->next = n;
    n->prev = new;

    new->val = val;
    return new;
}

node *insert_after(node *n, int val)
{
    node *new = (node *)malloc(sizeof(node *));
    assert(new != NULL);

    new->next = n->next;
    n->next->prev = new;
    new->prev = n;
    n->next = new;
    new->val = val;
    return new;
}

node *insert_between(node *l, node *r, int val)
{
    node *new = (node *)malloc(sizeof(node *));
    assert(new != NULL);

    new->next = r;
    new->prev = l;
    new->val = val;

    l->next = new;
    r->prev = new;
    return new;
}

void delete_before(node *n)
{
    node *deleted = n->prev;

    node *r = n;
    node *l = n->prev->prev;

    l->next = n;
    r->prev = n;
    free(deleted);
}

void delete_after(node *n)
{
    node *deleted = n->next;

    node *r = n->next->next;
    node *l = n;

    r->prev = n;
    n->next = r;
    free(deleted);
}

void delete_between(node *l, node *r)
{
    node *deleted = l->next;

    l->next = deleted->next;
    r->prev = deleted->prev;
    free(deleted);
}

void move_next_to_front(node *n)
{
    n->prev->next = n->next;
    n->next->prev = n->prev;

    head->next->prev = n;
    n->next = head->next;
    head->next = n;
    n->prev = head;
}

void print_linked_list_forward(void)
{
    node *t = head;

    while (t->next != NULL) {
        printf(" %d", t->val);
        t = t->next;
    }
    printf(" %d\n", t->val);
}

void print_linked_list_backward(void)
{
    node *t = end;

    while (t->prev != NULL) {
        printf(" %d", t->val);
        t = t->prev;
    }
    printf(" %d\n", t->val);
}


int main(void)
{
    init_linked_list();
    print_linked_list_forward();

    node *one = insert_between(head, end, 111);
    node *two = insert_between(one, end, 222);
    node *three = insert_between(two, end, 333);
    node *four = insert_between(three, end, 444);
    node *five = insert_between(four, end, 555);
    node *six= insert_between(five, end, 666);

    printf("forward\n");
    print_linked_list_forward();
    printf("backward\n");
    print_linked_list_backward();

    printf("insert after %d\n", two->val);
    node *middle_a = insert_after(two, 888);
    print_linked_list_forward();

    printf("insert before %d\n", middle_a->val);
    node *middle_b = insert_before(middle_a, 777);
    print_linked_list_forward();

    printf("delete_after %d\n", one->val);
    delete_after(one);
    print_linked_list_forward();

    printf("delete_before %d\n", four->val);
    delete_before(four);
    print_linked_list_forward();

    printf("delete_between %d and %d\n", four->val, six->val);
    delete_between(four, six);
    print_linked_list_forward();

    // move_next_to_front(two);
    print_linked_list_forward();
    return 0;
}
