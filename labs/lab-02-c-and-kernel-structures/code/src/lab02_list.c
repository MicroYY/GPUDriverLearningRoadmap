#include "lab02_list.h"

void list_init(struct list_head *head)
{
    /* TODO(student): initialize an empty circular doubly linked list. */
    (void)head;
}

int list_empty(const struct list_head *head)
{
    /* TODO(student): return non-zero when the list has no entries. */
    (void)head;
    return 1;
}

void list_add(struct list_head *node, struct list_head *head)
{
    /*
     * TODO(student):
     * Insert node right after head.
     *
     * Before:
     *   head <-> first
     *
     * After:
     *   head <-> node <-> first
     */
    (void)node;
    (void)head;
}

void list_add_tail(struct list_head *node, struct list_head *head)
{
    /*
     * TODO(student):
     * Insert node right before head.
     *
     * Before:
     *   last <-> head
     *
     * After:
     *   last <-> node <-> head
     */
    (void)node;
    (void)head;
}

void list_del(struct list_head *node)
{
    /*
     * TODO(student):
     * Remove node from its current list and make it standalone again.
     */
    (void)node;
}
