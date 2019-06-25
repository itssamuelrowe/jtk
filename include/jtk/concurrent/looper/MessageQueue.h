/*
 * Copyright 2018-2019 OneCube
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// Tuesday, August 28, 2018

#ifndef JTK_CONCURRENT_LOOPER_MESSAGE_QUEUE_H
#define JTK_CONCURRENT_LOOPER_MESSAGE_QUEUE_H

#include <jtk/Configuration.h>
#include <jtk/collection/list/ArrayList.h>
#include <jtk/collection/list/SinglyLinkedList.h>
#include <jtk/concurrent/lock/Mutex.h>
#include <jtk/concurrent/looper/Message.h>

/*******************************************************************************
 * MessageQueue                                                                *
 *******************************************************************************/

/**
 * @class MessageQueue
 * @ingroup jtk_concurrent
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since  JTK 1.1
 */
struct jtk_MessageQueue_t {

    /**
     * The mutual exclusive object used to synchronize this message
     * queue.
     */
    jtk_Mutex_t* m_mutex;

    /**
     * A list of registered idle listeners; notified when the message
     * queue is idle.
     */
    jtk_ArrayList_t* m_idleListeners;

    /**
     * A list of messages.
     */
    jtk_SinglyLinkedList_t* m_messages;

    /**
     * The message queue flushes out messages before permanently
     * quitting. This field determines whether the message queue is
     * quitting, or not. Once this flag is set to {@code true},
     * inserting a message into the queue always results in an
     * error.
     */
    bool m_quitting;

    /**
     * Determines whether the message queue is waiting for the next
     * message.
     */
    bool m_blocked;
};

/**
 * @memberof MessageQueue
 */
typedef struct jtk_MessageQueue_t jtk_MessageQueue_t;

/* Constructor */

/**
 * @memberof MessageQueue
 */
jtk_MessageQueue_t* jtk_MessageQueue_new();

/* Destructor */

/**
 * @memberof MessageQueue
 */
void jtk_MessageQueue_delete(jtk_MessageQueue_t* messageQueue);

/* Enqueue */

void jtk_MessageQueue_enqueue(jtk_MessageQueue_t* messageQueue, jtk_Message_t* message);

/* Idle Listener */

void jtk_MessageQueue_addIdleListener(jtk_MessageQueue_t* messageQueue, jtk_IdleListenerFunction_t listener);
void jtk_MessageQueue_removeIdleListener(jtk_MessageQueue_t* messageQueue, jtk_IdleListenerFunction_t listener);

/* Next */

jtk_Message_t* jtk_MessageQueue_getNext(jtk_MessageQueue_t* messageQueue);

#endif /* JTK_CONCURRENT_LOOPER_MESSAGE_QUEUE_H */