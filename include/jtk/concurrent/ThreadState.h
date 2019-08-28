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

    JTK_THREAD_STATE_WRAPPER = (1 << 0),

    JTK_THREAD_STATE_INTERRUPTIBLE = (1 << 1),

    JTK_THREAD_STATE_INTERRUPTED = (1 << 2),

    /**
     * Determines whether the thread has begun execution.
     */
    JTK_THREAD_STATE_ALIVE = (1 << 3),
};

/**
 * @memberof ThreadState
 */
typedef enum jtk_ThreadState_t jtk_ThreadState_t;

#endif /* JTK_CONCURRENT_THREAD_STATE_H */