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

// Tuesday, January 22, 2019

#ifndef JTK_SYSTEM_MEMORY_ALLOCATOR_H
#define JTK_SYSTEM_MEMORY_ALLOCATOR_H

/*******************************************************************************
 * Allocator                                                                   *
 *******************************************************************************/

typedef void* (*jtk_Allocator_AllocateFunction_t)(void* userData, int32_t size, int32_t count);
typedef void (*jtk_Allocator_DeallocateFunction_t)(void* userData, void* object);

/**
 * @class Allocator
 * @ingroup jtk_system_memory
 * @author Samuel Rowe
 * @since JTK 1.1
 */
struct jtk_Allocator_t {
    jtk_Allocator_AllocateFunction_t m_allocate;
    jtk_Allocator_DeallocateFunction_t m_deallocate;
    void* m_userData;
};

/**
 * @memberof Allocator
 */
typedef struct jtk_Allocator_t jtk_Allocator_t;

/* Allocate */

/**
 * @memberof Allocator
 */
void* jtk_Allocator_allocate(jtk_Allocator_t* allocator, int32_t size, int32_t count);

/**
 * @memberof Allocator
 */
void jtk_Allocator_deallocate(jtk_Allocator_t* allocator, void* object);

#endif /* JTK_SYSTEM_MEMORY_ALLOCATOR_H */