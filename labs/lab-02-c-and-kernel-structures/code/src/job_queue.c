#include "job_queue.h"

static size_t count_list(const struct list_head *head)
{
    /* TODO(student): walk the circular list and count entries. */
    (void)head;
    return 0;
}

void job_init(struct job *job, int id, int priority)
{
    job->id = id;
    job->priority = priority;
    job->state = JOB_IDLE;
    list_init(&job->link);
}

void job_queue_init(struct job_queue *queue, const char *name)
{
    /*
     * TODO(student):
     * Initialize queue metadata and both intrusive list heads.
     *
     * Suggested initial values:
     *   name: provided name
     *   refcount: 1
     *   flags: 0
     */
    (void)queue;
    (void)name;
}

int job_queue_submit(struct job_queue *queue, struct job *job)
{
    /*
     * TODO(student):
     * Mark job as pending and append it to queue->pending.
     */
    (void)queue;
    (void)job;
    return -1;
}

int job_queue_complete_next(struct job_queue *queue, struct job **out_job)
{
    /*
     * TODO(student):
     * If queue->pending is empty, return -1.
     * Otherwise, move the first pending job to queue->done, mark it done,
     * write it to *out_job when out_job is not NULL, and return 0.
     */
    (void)queue;
    (void)out_job;
    return -1;
}

size_t job_queue_pending_count(const struct job_queue *queue)
{
    /* TODO(student): return number of jobs in queue->pending. */
    (void)queue;
    return 0;
}

size_t job_queue_done_count(const struct job_queue *queue)
{
    /* TODO(student): return number of jobs in queue->done. */
    (void)queue;
    return 0;
}
