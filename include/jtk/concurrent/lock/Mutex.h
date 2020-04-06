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