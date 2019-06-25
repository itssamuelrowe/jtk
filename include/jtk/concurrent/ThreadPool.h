// Tuesday, August 28, 2018

#ifndef JTK_CONCURRENT_THREAD_POOL_H
#define JTK_CONCURRENT_THREAD_POOL_H

/*******************************************************************************
 * ThreadPool                                                                  *
 *******************************************************************************/

/**
 * @class ThreadPool
 * @ingroup jtk_concurrent
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.1
 */
struct jtk_ThreadPool_t {
};

/**
 * @memberof ThreadPool
 */
typedef struct jtk_ThreadPool_t jtk_ThreadPool_t;

/* Constructor */

/**
 * @memberof ThreadPool
 */
jtk_ThreadPool_t* jtk_ThreadPool_new();

/* Destructor */

/**
 * @memberof ThreadPool
 */
void jtk_ThreadPool_delete(jtk_ThreadPool_t* pool);

#endif /* JTK_CONCURRENT_THREAD_POOL_H */