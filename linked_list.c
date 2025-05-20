#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define RUN_EXAMPLES 1

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

node *delete_before_no_free(node *n)
{
    node *deleted = n->prev;

    node *r = n;
    node *l = n->prev->prev;

    l->next = n;
    r->prev = n;
    return deleted;
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

node *delete_after_no_free(node *n)
{
    node *deleted = n->next;

    node *r = n->next->next;
    node *l = n;

    r->prev = n;
    n->next = r;
    return deleted;
}

void delete_between(node *l, node *r)
{
    node *deleted = l->next;

    l->next = deleted->next;
    r->prev = deleted->prev;
    free(deleted);
}

node *delete_between_no_free(node *l, node *r)
{
    node *deleted = l->next;

    l->next = deleted->next;
    r->prev = deleted->prev;
    return deleted;
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

void exchange_after(node *to_exchange_after_l, node *to_exchange_after_r)
{
    node *l = delete_after_no_free(to_exchange_after_l);
    node *r = delete_after_no_free(to_exchange_after_r);
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

    node *one = insert_between(head, end, 111);
    node *two = insert_between(one, end, 222);
    node *three = insert_between(two, end, 333);
    node *four = insert_between(three, end, 444);
    node *five = insert_between(four, end, 555);
    node *six= insert_between(five, end, 666);

    print_linked_list_forward();
    printf("print_linked_list_backward\n");
    print_linked_list_backward();

    node *to_insert_after = two;
    printf("to_insert_after %d\n", to_insert_after->val);
    node *middle_a = insert_after(to_insert_after, 888);
    print_linked_list_forward();

    node *to_insert_before = middle_a;
    printf("insert_before %d\n", to_insert_before->val);
    node *middle_b = insert_before(to_insert_before, 777);
    print_linked_list_forward();

    node *to_delete_after = middle_a;
    printf("delete_after %d\n", to_delete_after->val);
    delete_after(to_delete_after);
    print_linked_list_forward();

    node *to_delete_before = four;
    printf("delete_before %d\n", to_delete_before->val);
    delete_before(to_delete_before);
    print_linked_list_forward();

    node *to_delete_betweeen_l = four;
    node *to_delete_betweeen_r = six;
    printf("delete_between %d and %d\n", to_delete_betweeen_l->val, to_delete_betweeen_r->val);
    delete_between(to_delete_betweeen_l, to_delete_betweeen_r);
    print_linked_list_forward();

    node *to_move_next_to_front = six;
    printf("move_next_to_front %d\n", to_move_next_to_front->val);
    move_next_to_front(to_move_next_to_front);
    print_linked_list_forward();

    node *to_exchange_after_l = to_move_next_to_front;
    node *to_exchange_after_r = two;
    printf("exchange_after %d and %d\n", to_exchange_after_l->val, to_exchange_after_r->val);
    exchange_after(to_exchange_after_l, to_exchange_after_r);
    print_linked_list_forward();

    printf("WARN: some functions left without examples\n");
}
