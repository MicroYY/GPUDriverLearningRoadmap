#ifndef LAB02_LIST_H
#define LAB02_LIST_H

#include <stddef.h>

struct list_head {
    struct list_head *next;
    struct list_head *prev;
};

/*
 * TODO(student):
 * Implement the classic container_of pattern.
 *
 * Given a pointer to a member, return a pointer to the outer structure.
 * Formula:
 *
 *   container = member_pointer - offsetof(container_type, member)
 *
 * Hint:
 *   Cast the member pointer to char * before subtracting byte offsets.
 */
#define container_of(ptr, type, member) ((void)(ptr), (type *)0)

#define list_entry(ptr, type, member) container_of(ptr, type, member)

#define list_first_entry(head, type, member) \
    list_entry((head)->next, type, member)

void list_init(struct list_head *head);
int list_empty(const struct list_head *head);
void list_add(struct list_head *node, struct list_head *head);
void list_add_tail(struct list_head *node, struct list_head *head);
void list_del(struct list_head *node);

#endif
