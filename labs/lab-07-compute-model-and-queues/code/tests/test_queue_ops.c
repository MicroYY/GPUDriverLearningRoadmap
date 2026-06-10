#include <stdio.h>

#include "queue_ops.h"

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

static int test_fifo_ops(void)
{
    struct gpu_queue queue;
    struct gpu_job first;
    struct gpu_job second;
    struct gpu_job *done = NULL;

    gpu_queue_init(&queue, "fifo", &fifo_queue_ops);
    gpu_job_init(&first, 1);
    gpu_job_init(&second, 2);

    ASSERT_PTR_EQ(&fifo_queue_ops, queue.ops);
    ASSERT_EQ_SIZE(0, queue.ops->pending_count(&queue));

    ASSERT_EQ_INT(0, queue.ops->submit(&queue, &first));
    ASSERT_EQ_INT(0, queue.ops->submit(&queue, &second));
    ASSERT_EQ_INT(JOB_PENDING, first.state);
    ASSERT_EQ_INT(JOB_PENDING, second.state);
    ASSERT_EQ_SIZE(2, queue.ops->pending_count(&queue));

    ASSERT_EQ_INT(0, queue.ops->complete_next(&queue, &done));
    ASSERT_PTR_EQ(&first, done);
    ASSERT_EQ_INT(JOB_COMPLETED, first.state);

    ASSERT_EQ_INT(0, queue.ops->complete_next(&queue, &done));
    ASSERT_PTR_EQ(&second, done);
    ASSERT_EQ_INT(JOB_COMPLETED, second.state);

    ASSERT_EQ_SIZE(0, queue.ops->pending_count(&queue));
    ASSERT_EQ_SIZE(2, queue.completed_count);
    ASSERT_EQ_INT(-1, queue.ops->complete_next(&queue, &done));
    return 0;
}

static int test_lifo_ops(void)
{
    struct gpu_queue queue;
    struct gpu_job first;
    struct gpu_job second;
    struct gpu_job *done = NULL;

    gpu_queue_init(&queue, "lifo", &lifo_queue_ops);
    gpu_job_init(&first, 1);
    gpu_job_init(&second, 2);

    ASSERT_PTR_EQ(&lifo_queue_ops, queue.ops);
    ASSERT_EQ_INT(0, queue.ops->submit(&queue, &first));
    ASSERT_EQ_INT(0, queue.ops->submit(&queue, &second));

    ASSERT_EQ_INT(0, queue.ops->complete_next(&queue, &done));
    ASSERT_PTR_EQ(&second, done);

    ASSERT_EQ_INT(0, queue.ops->complete_next(&queue, &done));
    ASSERT_PTR_EQ(&first, done);

    ASSERT_EQ_SIZE(0, queue.ops->pending_count(&queue));
    ASSERT_EQ_SIZE(2, queue.completed_count);
    return 0;
}

static int test_queue_capacity(void)
{
    struct gpu_queue queue;
    struct gpu_job jobs[JOB_QUEUE_CAPACITY + 1];
    size_t i;

    gpu_queue_init(&queue, "capacity", &fifo_queue_ops);

    for (i = 0; i < JOB_QUEUE_CAPACITY + 1; i++) {
        gpu_job_init(&jobs[i], (int)i);
    }

    for (i = 0; i < JOB_QUEUE_CAPACITY; i++) {
        ASSERT_EQ_INT(0, queue.ops->submit(&queue, &jobs[i]));
    }

    ASSERT_EQ_SIZE(JOB_QUEUE_CAPACITY, queue.ops->pending_count(&queue));
    ASSERT_EQ_INT(-1, queue.ops->submit(&queue, &jobs[JOB_QUEUE_CAPACITY]));
    ASSERT_EQ_INT(JOB_IDLE, jobs[JOB_QUEUE_CAPACITY].state);
    return 0;
}

int main(void)
{
    int rc;

    rc = test_fifo_ops();
    if (rc != 0)
        return rc;

    rc = test_lifo_ops();
    if (rc != 0)
        return rc;

    rc = test_queue_capacity();
    if (rc != 0)
        return rc;

    printf("PASS: all Lab 07 queue ops tests passed\n");
    return 0;
}
