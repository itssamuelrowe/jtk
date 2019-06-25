// Tuesday, August 28, 2018

#ifndef JTK_CONCURRENT_THREAD_LOCAL_H
#define JTK_CONCURRENT_THREAD_LOCAL_H

/*******************************************************************************
 * ThreadLocal                                                                 *
 *******************************************************************************/

/**
 * @class ThreadLocal
 * @ingroup jtk_concurrent
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.1
 */
struct jtk_ThreadLocal_t {
};

/**
 * @memberof ThreadLocal
 */
typedef struct jtk_ThreadLocal_t jtk_ThreadLocal_t;

/* Constructor */

/**
 * @memberof ThreadLocal
 */
jtk_ThreadLocal_t* jtk_ThreadLocal_new();

/* Destructor */

/**
 * @memberof ThreadLocal
 */
void jtk_ThreadLocal_delete(jtk_ThreadLocal_t* threadLocal);

#endif /* JTK_CONCURRENT_THREAD_LOCAL_H */