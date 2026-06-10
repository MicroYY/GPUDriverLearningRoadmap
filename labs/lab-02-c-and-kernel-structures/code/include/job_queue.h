#ifndef JOB_QUEUE_H
#define JOB_QUEUE_H

#include <stddef.h>

#include "lab02_list.h"

enum job_state {
    JOB_IDLE = 0,
    JOB_PENDING,
    JOB_DONE,
};

struct job {
    int id;
    int priority;
    enum job_state state;
    struct list_head link;
};

struct job_queue;

struct job_queue {
    const char *name;
    struct list_head pending;
    struct list_head done;
    unsigned int refcount;
    unsigned long flags;
};

void job_init(struct job *job, int id, int priority);
void job_queue_init(struct job_queue *queue, const char *name);
int job_queue_submit(struct job_queue *queue, struct job *job);
int job_queue_complete_next(struct job_queue *queue, struct job **out_job);
size_t job_queue_pending_count(const struct job_queue *queue);
size_t job_queue_done_count(const struct job_queue *queue);

#endif
