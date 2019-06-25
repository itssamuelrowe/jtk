// Thursday, August 30, 2018

#ifndef JTK_CONCURRENT_LOCK_MUTEX_H
#define JTK_CONCURRENT_LOCK_MUTEX_H

/*******************************************************************************
 * Mutex                                                                       *
 *******************************************************************************/

/**
 * @ingroup jtk_concurrent_lock
 * @class Mutex
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.0
 */
struct jtk_Mutex_t {
    void* m_handle;
    int32_t m_recursionCount;
    jtk_Thread_t* m_ownerThread;
};

/**
 * @memberof Mutex
 */
typedef struct jtk_Mutex_t jtk_Mutex_t;

/* Constructor */

/**
 * @memberof Mutex
 */
jtk_Mutex_t* jtk_Mutex_new();

/* Destructor */

/**
 * @memberof Mutex
 */
void jtk_Mutex_delete(jtk_Mutex_t* mutex);

/* Lock */

/**
 * @memberof Mutex
 */
bool jtk_Mutex_tryLock(jtk_Mutex_t* mutex);

/**
 * @memberof Mutex
 */
void jtk_Mutex_lock(jtk_Mutex_t* mutex);

/**
 * @memberof Mutex
 */
void jtk_Mutex_unlock(jtk_Mutex_t* mutex);

#endif /* JTK_CONCURRENT_LOCK_MUTEX_H */