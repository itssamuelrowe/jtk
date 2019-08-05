// Monday, August 05, 2019

#ifndef JTK_CONCURRENT_THREAD_STATE_H
#define JTK_CONCURRENT_THREAD_STATE_H

/*******************************************************************************
 * ThreadState                                                                 *
 *******************************************************************************/

/**
 * @class ThreadState
 * @ingroup jtk_concurrent
 * @author Samuel Rowe
 * @since JTK 1.1
 */
enum jtk_ThreadState_t {
    
    JTK_THREAD_STATE_NEW = (1 << 0),
    
    JTK_THREAD_STATE_INTERRUPTED = (1 << 1),

    /**
     * Determines whether the thread has begun execution.
     */
    JTK_THREAD_STATE_ALIVE = (1 << 2),
};

/**
 * @memberof ThreadState
 */
typedef enum jtk_ThreadState_t jtk_ThreadState_t;

#endif /* JTK_CONCURRENT_THREAD_STATE_H */