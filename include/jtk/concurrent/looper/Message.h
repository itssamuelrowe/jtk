// Tuesday, August 28, 2018

#ifndef JTK_CONCURRENT_LOOPER_MESSAGE_H
#define JTK_CONCURRENT_LOOPER_MESSAGE_H

#include <jtk/concurrent/looper/MessageHandler.h>
#include <jtk/concurrent/looper/MessagePool.h>

/*******************************************************************************
 * Message                                                                     *
 *******************************************************************************/

/**
 * @class Message
 * @ingroup jtk_concurrent_looper
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.0
 */
struct jtk_Message_t {
    int32_t m_code;
    int64_t m_argument1;
    int64_t m_argument2;
    void* m_argument3;
    int64_t m_when;
    jtk_MessageHandler_t* m_handler;
    jtk_MessagePool_t* m_pool;
    bool m_available;
};

/**
 * @memberof Message
 */
typedef struct jtk_Message_t jtk_Message_t;

/* Constructor */

/**
 * @memberof Message
 */
jtk_Message_t* jtk_Message_new();

/* Destructor */

/**
 * @memberof Message
 */
void jtk_Message_delete(jtk_Message_t* message);

#endif /* JTK_CONCURRENT_LOOPER_MESSAGE_H */