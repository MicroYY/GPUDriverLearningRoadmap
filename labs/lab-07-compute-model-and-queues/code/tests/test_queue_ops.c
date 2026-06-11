#include <stdio.h>

#include "queue_ops.h"

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

static int test_gpu_queue_init(void)
{
    const char *name = "fifo";
    struct gpu_queue queue = {0};
    size_t i;

    gpu_queue_init(&queue, name, &fifo_queue_ops);

    ASSERT_PTR_EQ(name, queue.name);
    ASSERT_PTR_EQ(&fifo_queue_ops, queue.ops);
    ASSERT_EQ_SIZE(0, queue.count);
    ASSERT_EQ_SIZE(0, queue.completed_count);

    for (i = 0; i < JOB_QUEUE_CAPACITY; i++) {
        ASSERT_PTR_EQ(NULL, queue.pending[i]);
    }

    return 0;
}

static int test_pending_count(void)
{
    struct gpu_queue queue = {0};

    queue.count = 3;

    ASSERT_EQ_SIZE(3, fifo_queue_ops.pending_count(&queue));
    ASSERT_EQ_SIZE(3, lifo_queue_ops.pending_count(&queue));
    return 0;
}

static int test_fifo_submit_tail(void)
{
    struct gpu_queue queue = {0};
    struct gpu_job first;
    struct gpu_job second;

    gpu_job_init(&first, 1);
    gpu_job_init(&second, 2);

    ASSERT_EQ_INT(0, fifo_queue_ops.submit(&queue, &first));
    ASSERT_EQ_INT(0, fifo_queue_ops.submit(&queue, &second));
    ASSERT_EQ_INT(JOB_PENDING, first.state);
    ASSERT_EQ_INT(JOB_PENDING, second.state);
    ASSERT_EQ_SIZE(2, queue.count);
    ASSERT_PTR_EQ(&first, queue.pending[0]);
    ASSERT_PTR_EQ(&second, queue.pending[1]);
    return 0;
}

static int test_lifo_submit_head(void)
{
    struct gpu_queue queue = {0};
    struct gpu_job first;
    struct gpu_job second;

    gpu_job_init(&first, 1);
    gpu_job_init(&second, 2);

    ASSERT_EQ_INT(0, lifo_queue_ops.submit(&queue, &first));
    ASSERT_EQ_INT(0, lifo_queue_ops.submit(&queue, &second));
    ASSERT_EQ_INT(JOB_PENDING, first.state);
    ASSERT_EQ_INT(JOB_PENDING, second.state);
    ASSERT_EQ_SIZE(2, queue.count);
    ASSERT_PTR_EQ(&second, queue.pending[0]);
    ASSERT_PTR_EQ(&first, queue.pending[1]);
    return 0;
}

static int test_complete_next(void)
{
    struct gpu_queue queue = {0};
    struct gpu_job first;
    struct gpu_job second;
    struct gpu_job *done = NULL;

    gpu_job_init(&first, 1);
    gpu_job_init(&second, 2);
    first.state = JOB_PENDING;
    second.state = JOB_PENDING;
    queue.pending[0] = &first;
    queue.pending[1] = &second;
    queue.count = 2;

    ASSERT_EQ_INT(0, fifo_queue_ops.complete_next(&queue, &done));
    ASSERT_PTR_EQ(&first, done);
    ASSERT_EQ_INT(JOB_COMPLETED, first.state);
    ASSERT_EQ_INT(JOB_PENDING, second.state);
    ASSERT_EQ_SIZE(1, queue.count);
    ASSERT_EQ_SIZE(1, queue.completed_count);
    ASSERT_PTR_EQ(&second, queue.pending[0]);

    ASSERT_EQ_INT(0, fifo_queue_ops.complete_next(&queue, &done));
    ASSERT_PTR_EQ(&second, done);
    ASSERT_EQ_INT(JOB_COMPLETED, second.state);
    ASSERT_EQ_SIZE(0, queue.count);
    ASSERT_EQ_SIZE(2, queue.completed_count);

    ASSERT_EQ_INT(-1, fifo_queue_ops.complete_next(&queue, &done));
    return 0;
}

static int test_queue_capacity(void)
{
    struct gpu_queue queue = {0};
    struct gpu_job jobs[JOB_QUEUE_CAPACITY + 1];
    size_t i;

    for (i = 0; i < JOB_QUEUE_CAPACITY + 1; i++) {
        gpu_job_init(&jobs[i], (int)i);
    }

    for (i = 0; i < JOB_QUEUE_CAPACITY; i++) {
        ASSERT_EQ_INT(0, fifo_queue_ops.submit(&queue, &jobs[i]));
    }

    ASSERT_EQ_SIZE(JOB_QUEUE_CAPACITY, fifo_queue_ops.pending_count(&queue));
    ASSERT_EQ_INT(-1, fifo_queue_ops.submit(&queue, &jobs[JOB_QUEUE_CAPACITY]));
    ASSERT_EQ_INT(JOB_IDLE, jobs[JOB_QUEUE_CAPACITY].state);
    return 0;
}

static int test_ops_table_dispatch(void)
{
    struct gpu_queue queue = {0};
    struct gpu_job first;
    struct gpu_job second;
    struct gpu_job *done = NULL;

    gpu_queue_init(&queue, "fifo", &fifo_queue_ops);
    gpu_job_init(&first, 1);
    gpu_job_init(&second, 2);

    ASSERT_PTR_EQ(&fifo_queue_ops, queue.ops);
    ASSERT_EQ_INT(0, queue.ops->submit(&queue, &first));
    ASSERT_EQ_INT(0, queue.ops->submit(&queue, &second));
    ASSERT_EQ_SIZE(2, queue.ops->pending_count(&queue));

    ASSERT_EQ_INT(0, queue.ops->complete_next(&queue, &done));
    ASSERT_PTR_EQ(&first, done);

    ASSERT_EQ_INT(0, queue.ops->complete_next(&queue, &done));
    ASSERT_PTR_EQ(&second, done);
    ASSERT_EQ_SIZE(0, queue.ops->pending_count(&queue));
    ASSERT_EQ_SIZE(2, queue.completed_count);
    return 0;
}

typedef int (*test_fn)(void);

static int run_test(const char *name, test_fn fn)
{
    int rc;

    printf("RUN : %s\n", name);
    fflush(stdout);

    rc = fn();
    if (rc != 0) {
        printf("FAIL: %s\n", name);
        return 1;
    }

    printf("PASS: %s\n", name);
    return 0;
}

int main(void)
{
    int failures = 0;

    failures += run_test("gpu_queue_init stores metadata and clears slots",
                         test_gpu_queue_init);
    failures += run_test("pending_count reports queue->count",
                         test_pending_count);
    failures += run_test("FIFO submit appends jobs at the tail",
                         test_fifo_submit_tail);
    failures += run_test("LIFO submit inserts jobs at the head",
                         test_lifo_submit_head);
    failures += run_test("complete_next removes and completes the head job",
                         test_complete_next);
    failures += run_test("queue capacity rejects overflow",
                         test_queue_capacity);
    failures += run_test("ops table dispatch calls the selected backend",
                         test_ops_table_dispatch);

    if (failures != 0) {
        printf("FAIL: %d Lab 07 test(s) failed\n", failures);
        return 1;
    }

    printf("PASS: all Lab 07 queue ops tests passed\n");
    return 0;
}
