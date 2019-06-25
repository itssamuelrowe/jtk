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

// Saturday, February 24, 2018

#ifndef JTK_CORE_OBJECT_ADAPTER_H
#define JTK_CORE_OBJECT_ADAPTER_H

#include <jtk/Configuration.h>

/*******************************************************************************
 * ObjectAdapter                                                               *
 *******************************************************************************/

/**
 * @memberof ObjectAdapter
 */
typedef int32_t (*jtk_ObjectAdapter_CompareFunction_t)(void* argument1, void* argument2);

/**
 * @memberof ObjectAdapter
 */
typedef bool (*jtk_ObjectAdapter_EqualsFunction_t)(void* argument1, void* argument2);

/**
 * @memberof ObjectAdapter
 */
typedef int32_t (*jtk_ObjectAdapter_HashFunction_t)(void* argument);

/**
 * @class ObjectAdapter
 * @ingroup jtk_core
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.0
 */ 
struct jtk_ObjectAdapter_t {
    jtk_ObjectAdapter_CompareFunction_t compare;
    jtk_ObjectAdapter_EqualsFunction_t equals;
    jtk_ObjectAdapter_HashFunction_t hash;
};

/**
 * @memberof ObjectAdapter
 */
typedef struct jtk_ObjectAdapter_t jtk_ObjectAdapter_t;

#endif /* JTK_CORE_OBJECT_ADAPTER_H */