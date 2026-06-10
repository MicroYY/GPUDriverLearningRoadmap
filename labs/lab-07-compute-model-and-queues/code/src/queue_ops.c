#include "queue_ops.h"

static int submit_tail(struct gpu_queue *queue, struct gpu_job *job)
{
    /*
     * TODO(student):
     * Append job to the tail of queue->pending.
     * Return -1 when the queue is full.
     * On success, mark the job as JOB_PENDING and return 0.
     */
    (void)queue;
    (void)job;
    return -1;
}

static int submit_head(struct gpu_queue *queue, struct gpu_job *job)
{
    /*
     * TODO(student):
     * Insert job at the head of queue->pending.
     * Existing pending jobs should move one slot toward the tail.
     * Return -1 when the queue is full.
     * On success, mark the job as JOB_PENDING and return 0.
     */
    (void)queue;
    (void)job;
    return -1;
}

static int complete_next(struct gpu_queue *queue, struct gpu_job **out_job)
{
    /*
     * TODO(student):
     * Complete the first pending job.
     * Return -1 when no pending job exists.
     * On success:
     *   - remove the first pending job
     *   - shift remaining jobs toward the head
     *   - mark the job as JOB_COMPLETED
     *   - store it in *out_job when out_job is not NULL
     *   - increment queue->completed_count
     *   - return 0
     */
    (void)queue;
    (void)out_job;
    return -1;
}

static size_t pending_count(const struct gpu_queue *queue)
{
    /* TODO(student): return the number of pending jobs. */
    (void)queue;
    return 0;
}

const struct gpu_queue_ops fifo_queue_ops = {
    submit_tail,
    complete_next,
    pending_count,
};

const struct gpu_queue_ops lifo_queue_ops = {
    submit_head,
    complete_next,
    pending_count,
};

void gpu_job_init(struct gpu_job *job, int id)
{
    job->id = id;
    job->state = JOB_IDLE;
}

void gpu_queue_init(struct gpu_queue *queue, const char *name,
                    const struct gpu_queue_ops *ops)
{
    /*
     * TODO(student):
     * Initialize queue metadata and clear the pending array.
     */
    (void)queue;
    (void)name;
    (void)ops;
}
