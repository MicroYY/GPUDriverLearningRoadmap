#include <stdio.h>
#include <string.h>

#include "job_queue.h"
#include "lab02_list.h"

#define ASSERT_TRUE(expr)                                                       \
    do {                                                                        \
        if (!(expr)) {                                                          \
            fprintf(stderr, "FAIL: %s:%d: expected true: %s\n", __FILE__,       \
                    __LINE__, #expr);                                           \
            return 1;                                                           \
        }                                                                       \
    } while (0)

#define ASSERT_EQ_INT(expected, actual)                                         \
    do {                                                                        \
        int expected_value = (expected);                                        \
        int actual_value = (actual);                                            \
        if (expected_value != actual_value) {                                   \
            fprintf(stderr, "FAIL: %s:%d: expected %d, got %d\n", __FILE__,     \
                    __LINE__, expected_value, actual_value);                    \
            return 1;                                                           \
        }                                                                       \
    } while (0)

#define ASSERT_EQ_SIZE(expected, actual)                                        \
    do {                                                                        \
        size_t expected_value = (expected);                                     \
        size_t actual_value = (actual);                                         \
        if (expected_value != actual_value) {                                   \
            fprintf(stderr, "FAIL: %s:%d: expected %zu, got %zu\n", __FILE__,   \
                    __LINE__, expected_value, actual_value);                    \
            return 1;                                                           \
        }                                                                       \
    } while (0)

#define ASSERT_PTR_EQ(expected, actual)                                         \
    do {                                                                        \
        const void *expected_value = (expected);                                \
        const void *actual_value = (actual);                                    \
        if (expected_value != actual_value) {                                   \
            fprintf(stderr, "FAIL: %s:%d: expected %p, got %p\n", __FILE__,     \
                    __LINE__, expected_value, actual_value);                    \
            return 1;                                                           \
        }                                                                       \
    } while (0)

#define ASSERT_STR_EQ(expected, actual)                                         \
    do {                                                                        \
        const char *expected_value = (expected);                                \
        const char *actual_value = (actual);                                    \
        if (strcmp(expected_value, actual_value) != 0) {                        \
            fprintf(stderr, "FAIL: %s:%d: expected \"%s\", got \"%s\"\n",       \
                    __FILE__, __LINE__, expected_value, actual_value);          \
            return 1;                                                           \
        }                                                                       \
    } while (0)

static int test_container_of(void)
{
    struct sample {
        int id;
        struct list_head link;
        int payload;
    };

    struct sample item;
    struct list_head *link = &item.link;

    ASSERT_PTR_EQ(&item, container_of(link, struct sample, link));
    return 0;
}

static int test_list_add_head_order(void)
{
    struct list_head head;
    struct job first;
    struct job second;

    list_init(&head);
    job_init(&first, 1, 10);
    job_init(&second, 2, 20);

    list_add(&first.link, &head);
    list_add(&second.link, &head);

    ASSERT_PTR_EQ(&second, list_first_entry(&head, struct job, link));
    ASSERT_PTR_EQ(&first, list_entry(second.link.next, struct job, link));
    return 0;
}

static int test_intrusive_list_basics(void)
{
    struct list_head head;
    struct job first;
    struct job second;

    list_init(&head);
    job_init(&first, 1, 10);
    job_init(&second, 2, 20);

    ASSERT_TRUE(list_empty(&head));

    list_add_tail(&first.link, &head);
    ASSERT_TRUE(!list_empty(&head));
    ASSERT_PTR_EQ(&first, list_first_entry(&head, struct job, link));

    list_add_tail(&second.link, &head);
    ASSERT_PTR_EQ(&first, list_first_entry(&head, struct job, link));

    list_del(&first.link);
    ASSERT_PTR_EQ(&second, list_first_entry(&head, struct job, link));

    list_del(&second.link);
    ASSERT_TRUE(list_empty(&head));
    return 0;
}

static int test_job_queue_state_flow(void)
{
    struct job_queue queue;
    struct job first;
    struct job second;
    struct job *done = NULL;

    job_queue_init(&queue, "pending-jobs");
    job_init(&first, 1, 10);
    job_init(&second, 2, 20);

    ASSERT_STR_EQ("pending-jobs", queue.name);
    ASSERT_EQ_INT(1, (int)queue.refcount);
    ASSERT_EQ_INT(0, (int)queue.flags);
    ASSERT_EQ_SIZE(0, job_queue_pending_count(&queue));
    ASSERT_EQ_SIZE(0, job_queue_done_count(&queue));

    ASSERT_EQ_INT(0, job_queue_submit(&queue, &first));
    ASSERT_EQ_INT(0, job_queue_submit(&queue, &second));
    ASSERT_EQ_INT(-1, job_queue_submit(&queue, &first));
    ASSERT_EQ_INT(JOB_PENDING, first.state);
    ASSERT_EQ_INT(JOB_PENDING, second.state);
    ASSERT_EQ_SIZE(2, job_queue_pending_count(&queue));

    ASSERT_EQ_INT(0, job_queue_complete_next(&queue, &done));
    ASSERT_PTR_EQ(&first, done);
    ASSERT_EQ_INT(JOB_DONE, first.state);
    ASSERT_EQ_SIZE(1, job_queue_pending_count(&queue));
    ASSERT_EQ_SIZE(1, job_queue_done_count(&queue));

    ASSERT_EQ_INT(0, job_queue_complete_next(&queue, &done));
    ASSERT_PTR_EQ(&second, done);
    ASSERT_EQ_INT(JOB_DONE, second.state);
    ASSERT_EQ_SIZE(0, job_queue_pending_count(&queue));
    ASSERT_EQ_SIZE(2, job_queue_done_count(&queue));

    ASSERT_EQ_INT(-1, job_queue_complete_next(&queue, &done));
    return 0;
}

static int test_job_queue_complete_with_null_output(void)
{
    struct job_queue queue;
    struct job job;

    job_queue_init(&queue, "null-output");
    job_init(&job, 7, 70);

    ASSERT_EQ_INT(0, job_queue_submit(&queue, &job));
    ASSERT_EQ_INT(0, job_queue_complete_next(&queue, NULL));
    ASSERT_EQ_INT(JOB_DONE, job.state);
    ASSERT_EQ_SIZE(0, job_queue_pending_count(&queue));
    ASSERT_EQ_SIZE(1, job_queue_done_count(&queue));
    return 0;
}

int main(void)
{
    int rc;

    rc = test_container_of();
    if (rc != 0)
        return rc;

    rc = test_list_add_head_order();
    if (rc != 0)
        return rc;

    rc = test_intrusive_list_basics();
    if (rc != 0)
        return rc;

    rc = test_job_queue_state_flow();
    if (rc != 0)
        return rc;

    rc = test_job_queue_complete_with_null_output();
    if (rc != 0)
        return rc;

    printf("PASS: all Lab 02 tests passed\n");
    return 0;
}
