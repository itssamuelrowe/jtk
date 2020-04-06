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