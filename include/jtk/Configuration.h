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

// Friday, May 18, 2018

#ifndef JTK_CONFIGURATION_H
#define JTK_CONFIGURATION_H

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#ifndef NULL
    #define NULL 0
#endif

#define jtk_Memory_allocate(type, units) (type*)jtk_Memory_allocate0(sizeof (type) * (units))
#define jtk_Memory_deallocate(object) jtk_Memory_deallocate0(object)

#define jtk_Assert_assertObject(object, message) assert((object) != NULL)
#define jtk_Assert_assertTrue(expression, message) assert(expression)
#define jtk_Assert_assertFalse(expression, message) assert(!(expression))

void* jtk_Memory_allocate0(int32_t size);
void jtk_Memory_deallocate0(void* object);

#endif /* JTK_CONFIGURATION_H */