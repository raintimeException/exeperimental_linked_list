#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define RUN_EXAMPLES 1

typedef struct node_t {
    int val;
    struct node_t *next;
    struct node_t *prev;
} node_t;
node_t *head, *end;

void init_linked_list(void)
{
    head = (node_t  *)malloc(sizeof(node_t));
    assert(head != NULL);
    end = (node_t *)malloc(sizeof(node_t));
    assert(head != NULL);
    head->val = 0;
    head->next = end;
    head->prev = NULL;
    end->val = 0;
    end->next = NULL;
    end->prev = head;
}

node_t *insert_before(node_t *n, int val)
{
    node_t *new = (node_t *)malloc(sizeof(node_t));
    assert(new != NULL);

    new->prev = n->prev;
    n->prev->next = new;
    new->next = n;
    n->prev = new;
    new->val = val;
    return new;
}

node_t *insert_after(node_t *n, int val)
{
    node_t *new = (node_t *)malloc(sizeof(node_t));
    assert(new != NULL);

    new->next = n->next;
    n->next->prev = new;
    new->prev = n;
    n->next = new;
    new->val = val;
    return new;
}

node_t *insert_between(node_t *l, node_t *r, int val)
{
    node_t *new = (node_t *)malloc(sizeof(node_t));
    assert(new != NULL);

    new->next = r;
    new->prev = l;
    new->val = val;
    l->next = new;
    r->prev = new;
    return new;
}

void delete_before(node_t *n)
{
    node_t *deleted = n->prev;

    node_t *r = n;
    node_t *l = n->prev->prev;
    l->next = n;
    r->prev = n;
    free(deleted);
}

node_t *delete_before_no_free(node_t *n)
{
    node_t *deleted = n->prev;

    node_t *r = n;
    node_t *l = n->prev->prev;
    l->next = n;
    r->prev = n;
    return deleted;
}

void delete_after(node_t *n)
{
    node_t *deleted = n->next;

    node_t *r = n->next->next;
    node_t *l = n;
    r->prev = n;
    l->next = r;
    free(deleted);
}

node_t *delete_after_no_free(node_t *n)
{
    node_t *deleted = n->next;

    node_t *r = n->next->next;
    node_t *l = n;
    r->prev = n;
    l->next = r;
    return deleted;
}

void delete_between(node_t *l, node_t *r)
{
    node_t *deleted = l->next;

    l->next = deleted->next;
    r->prev = deleted->prev;
    free(deleted);
}

node_t *delete_between_no_free(node_t *l, node_t *r)
{
    node_t *deleted = l->next;

    l->next = deleted->next;
    r->prev = deleted->prev;
    return deleted;
}

void move_next_to_front(node_t *n)
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
    node_t *t = head;

    while (t->next != NULL) {
        printf(" %d", t->val);
        t = t->next;
    }
    printf(" %d\n", t->val);
}

void print_linked_list_backward(void)
{
    node_t *t = end;

    while (t->prev != NULL) {
        printf(" %d", t->val);
        t = t->prev;
    }
    printf(" %d\n", t->val);
}

void exchange_after(node_t *to_exchange_after_l, node_t *to_exchange_after_r)
{
    node_t *l = delete_after_no_free(to_exchange_after_l);
    node_t *r = delete_after_no_free(to_exchange_after_r);
    insert_after(to_exchange_after_l, r->val);
    insert_after(to_exchange_after_r, l->val);
}

int main(void)
{
#if RUN_EXAMPLES
    void examples(void);
    examples();
#endif
    return 0;
}

void examples(void)
{
    init_linked_list();
    printf("print_linked_list_forward()\n");
    print_linked_list_forward();

    node_t *one = insert_between(head, end, 111);
    node_t *two = insert_between(one, end, 222);
    node_t *three = insert_between(two, end, 333);
    node_t *four = insert_between(three, end, 444);
    node_t *five = insert_between(four, end, 555);
    node_t *six= insert_between(five, end, 666);

    print_linked_list_forward();
    printf("print_linked_list_backward\n");
    print_linked_list_backward();

    node_t *to_insert_after = two;
    printf("to_insert_after %d\n", to_insert_after->val);
    node_t *middle_a = insert_after(to_insert_after, 888);
    print_linked_list_forward();

    node_t *to_insert_before = middle_a;
    printf("insert_before %d\n", to_insert_before->val);
    node_t *middle_b = insert_before(to_insert_before, 777);
    (void)middle_b;
    print_linked_list_forward();

    node_t *to_delete_after = middle_a;
    printf("delete_after %d\n", to_delete_after->val);
    delete_after(to_delete_after);
    print_linked_list_forward();

    node_t *to_delete_before = four;
    printf("delete_before %d\n", to_delete_before->val);
    delete_before(to_delete_before);
    print_linked_list_forward();

    node_t *to_delete_betweeen_l = four;
    node_t *to_delete_betweeen_r = six;
    printf("delete_between %d and %d\n", to_delete_betweeen_l->val, to_delete_betweeen_r->val);
    delete_between(to_delete_betweeen_l, to_delete_betweeen_r);
    print_linked_list_forward();

    node_t *to_move_next_to_front = six;
    printf("move_next_to_front %d\n", to_move_next_to_front->val);
    move_next_to_front(to_move_next_to_front);
    print_linked_list_forward();

    node_t *to_exchange_after_l = to_move_next_to_front;
    node_t *to_exchange_after_r = two;
    printf("exchange_after %d and %d\n", to_exchange_after_l->val, to_exchange_after_r->val);
    exchange_after(to_exchange_after_l, to_exchange_after_r);
    print_linked_list_forward();

    printf("WARN: some functions left without examples\n");
}
