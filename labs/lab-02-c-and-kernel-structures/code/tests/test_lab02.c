#include <stdio.h>
#include <string.h>

#include "job_queue.h"
#include "lab02_list.h"

#define ASSERT_TRUE(expr)                                                       \
    do {                                                                        \
        if (!(expr)) {                                                          \
            printf("FAIL: %s:%d: expected true: %s\n", __FILE__, __LINE__,      \
                   #expr);                                                      \
            return 1;                                                           \
        }                                                                       \
    } while (0)

#define ASSERT_EQ_INT(expected, actual)                                         \
    do {                                                                        \
        int expected_value = (expected);                                        \
        int actual_value = (actual);                                            \
        if (expected_value != actual_value) {                                   \
            printf("FAIL: %s:%d: expected %d, got %d\n", __FILE__, __LINE__,    \
                   expected_value, actual_value);                               \
            return 1;                                                           \
        }                                                                       \
    } while (0)

#define ASSERT_EQ_SIZE(expected, actual)                                        \
    do {                                                                        \
        size_t expected_value = (expected);                                     \
        size_t actual_value = (actual);                                         \
        if (expected_value != actual_value) {                                   \
            printf("FAIL: %s:%d: expected %zu, got %zu\n", __FILE__, __LINE__,  \
                   expected_value, actual_value);                               \
            return 1;                                                           \
        }                                                                       \
    } while (0)

#define ASSERT_PTR_EQ(expected, actual)                                         \
    do {                                                                        \
        const void *expected_value = (expected);                                \
        const void *actual_value = (actual);                                    \
        if (expected_value != actual_value) {                                   \
            printf("FAIL: %s:%d: expected %p, got %p\n", __FILE__, __LINE__,    \
                   expected_value, actual_value);                               \
            return 1;                                                           \
        }                                                                       \
    } while (0)

#define ASSERT_STR_EQ(expected, actual)                                         \
    do {                                                                        \
        const char *expected_value = (expected);                                \
        const char *actual_value = (actual);                                    \
        if ((expected_value == NULL) != (actual_value == NULL) ||               \
            (expected_value != NULL &&                                          \
             strcmp(expected_value, actual_value) != 0)) {                      \
            printf("FAIL: %s:%d: expected \"%s\", got \"%s\"\n", __FILE__,      \
                   __LINE__,                                                    \
                   expected_value == NULL ? "(null)" : expected_value,          \
                   actual_value == NULL ? "(null)" : actual_value);             \
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

static int test_list_init_and_empty(void)
{
    struct list_head head;

    list_init(&head);

    ASSERT_PTR_EQ(&head, head.next);
    ASSERT_PTR_EQ(&head, head.prev);
    ASSERT_TRUE(list_empty(&head));
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

    ASSERT_PTR_EQ(&second.link, head.next);
    ASSERT_PTR_EQ(&head, second.link.prev);
    ASSERT_PTR_EQ(&first.link, second.link.next);
    ASSERT_PTR_EQ(&second.link, first.link.prev);
    ASSERT_PTR_EQ(&head, first.link.next);
    ASSERT_PTR_EQ(&first.link, head.prev);
    return 0;
}

static int test_list_add_tail_and_delete(void)
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
    ASSERT_PTR_EQ(&first.link, head.next);
    ASSERT_PTR_EQ(&first.link, head.prev);
    ASSERT_PTR_EQ(&head, first.link.next);
    ASSERT_PTR_EQ(&head, first.link.prev);

    list_add_tail(&second.link, &head);
    ASSERT_PTR_EQ(&first.link, head.next);
    ASSERT_PTR_EQ(&second.link, head.prev);
    ASSERT_PTR_EQ(&second.link, first.link.next);
    ASSERT_PTR_EQ(&first.link, second.link.prev);

    list_del(&first.link);
    ASSERT_PTR_EQ(&second.link, head.next);
    ASSERT_PTR_EQ(&second.link, head.prev);
    ASSERT_PTR_EQ(&first.link, first.link.next);
    ASSERT_PTR_EQ(&first.link, first.link.prev);

    list_del(&second.link);
    ASSERT_TRUE(list_empty(&head));
    ASSERT_PTR_EQ(&second.link, second.link.next);
    ASSERT_PTR_EQ(&second.link, second.link.prev);
    return 0;
}

static int test_job_queue_init(void)
{
    struct job_queue queue;

    memset(&queue, 0, sizeof(queue));

    job_queue_init(&queue, "pending-jobs");

    ASSERT_STR_EQ("pending-jobs", queue.name);
    ASSERT_EQ_INT(1, (int)queue.refcount);
    ASSERT_EQ_INT(0, (int)queue.flags);
    ASSERT_PTR_EQ(&queue.pending, queue.pending.next);
    ASSERT_PTR_EQ(&queue.pending, queue.pending.prev);
    ASSERT_PTR_EQ(&queue.done, queue.done.next);
    ASSERT_PTR_EQ(&queue.done, queue.done.prev);
    ASSERT_EQ_SIZE(0, job_queue_pending_count(&queue));
    ASSERT_EQ_SIZE(0, job_queue_done_count(&queue));
    return 0;
}

static int test_job_queue_submit(void)
{
    struct job_queue queue;
    struct job first;
    struct job second;

    job_queue_init(&queue, "pending-jobs");
    job_init(&first, 1, 10);
    job_init(&second, 2, 20);

    ASSERT_EQ_INT(0, job_queue_submit(&queue, &first));
    ASSERT_EQ_INT(0, job_queue_submit(&queue, &second));
    ASSERT_EQ_INT(-1, job_queue_submit(&queue, &first));
    ASSERT_EQ_INT(JOB_PENDING, first.state);
    ASSERT_EQ_INT(JOB_PENDING, second.state);
    ASSERT_EQ_SIZE(2, job_queue_pending_count(&queue));
    ASSERT_PTR_EQ(&first.link, queue.pending.next);
    ASSERT_PTR_EQ(&second.link, queue.pending.prev);
    return 0;
}

static int test_job_queue_complete_next(void)
{
    struct job_queue queue;
    struct job first;
    struct job second;
    struct job *done = NULL;

    job_queue_init(&queue, "pending-jobs");
    job_init(&first, 1, 10);
    job_init(&second, 2, 20);

    ASSERT_EQ_INT(0, job_queue_submit(&queue, &first));
    ASSERT_EQ_INT(0, job_queue_submit(&queue, &second));

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

typedef int (*test_fn)(void);

static int run_test(const char *label, test_fn fn)
{
    int rc;

    rc = fn();
    if (rc != 0) {
        printf("[FAIL] %s\n", label);
        return 1;
    }

    printf("[PASS] %s\n", label);
    return 0;
}

static int skip_test(const char *label, const char *reason)
{
    printf("[SKIP] %s (%s)\n", label, reason);
    return 1;
}

int main(void)
{
    int failures = 0;
    int skipped = 0;
    int container_failed;
    int list_init_failed;
    int list_add_failed = 1;
    int list_tail_failed = 1;
    int queue_init_failed = 1;
    int queue_submit_failed = 1;
    int queue_complete_failed = 1;

    container_failed = run_test("1. container_of",
                                test_container_of);
    failures += container_failed;

    list_init_failed = run_test("2. list_init/list_empty",
                                test_list_init_and_empty);
    failures += list_init_failed;

    if (list_init_failed == 0) {
        list_add_failed = run_test("3. list_add",
                                   test_list_add_head_order);
        failures += list_add_failed;
        list_tail_failed = run_test("4. list_add_tail/list_del",
                                    test_list_add_tail_and_delete);
        failures += list_tail_failed;
    } else {
        skipped += skip_test("3. list_add",
                             "needs list_init/list_empty");
        skipped += skip_test("4. list_add_tail/list_del",
                             "needs list_init/list_empty");
    }

    if (list_init_failed == 0) {
        queue_init_failed = run_test("5. job_queue_init",
                                     test_job_queue_init);
        failures += queue_init_failed;
    } else {
        skipped += skip_test("5. job_queue_init",
                             "needs list_init/list_empty");
    }

    if (queue_init_failed == 0 && list_add_failed == 0 &&
        list_tail_failed == 0) {
        queue_submit_failed = run_test("6. job_queue_submit",
                                       test_job_queue_submit);
        failures += queue_submit_failed;
    } else {
        skipped += skip_test("6. job_queue_submit",
                             "needs queue init and list add/delete");
    }

    if (container_failed == 0 && queue_submit_failed == 0) {
        queue_complete_failed = run_test("7. job_queue_complete_next",
                                         test_job_queue_complete_next);
        failures += queue_complete_failed;
    } else {
        skipped += skip_test("7. job_queue_complete_next",
                             "needs container_of and queue submit");
    }

    if (queue_complete_failed == 0) {
        failures += run_test("8. complete_next with NULL output",
                             test_job_queue_complete_with_null_output);
    } else {
        skipped += skip_test("8. complete_next with NULL output",
                             "needs complete_next");
    }

    if (failures != 0) {
        printf("\nSummary: %d failed, %d skipped\n", failures,
               skipped);
        return 1;
    }

    printf("\nSummary: all Lab 02 tests passed\n");
    return 0;
}
