#ifndef QUEUE_OPS_H
#define QUEUE_OPS_H

#include <stddef.h>

#define JOB_QUEUE_CAPACITY 8

enum job_state {
    JOB_IDLE = 0,
    JOB_PENDING,
    JOB_COMPLETED,
};

struct gpu_job {
    int id;
    enum job_state state;
};

struct gpu_queue;

struct gpu_queue_ops {
    int (*submit)(struct gpu_queue *queue, struct gpu_job *job);
    int (*complete_next)(struct gpu_queue *queue, struct gpu_job **out_job);
    size_t (*pending_count)(const struct gpu_queue *queue);
};

struct gpu_queue {
    const char *name;
    const struct gpu_queue_ops *ops;
    struct gpu_job *pending[JOB_QUEUE_CAPACITY];
    size_t count;
    size_t completed_count;
};

extern const struct gpu_queue_ops fifo_queue_ops;
extern const struct gpu_queue_ops lifo_queue_ops;

void gpu_job_init(struct gpu_job *job, int id);
void gpu_queue_init(struct gpu_queue *queue, const char *name,
                    const struct gpu_queue_ops *ops);

#endif
