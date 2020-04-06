/*
 * Copyright 2017-2020 Samuel Rowe
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