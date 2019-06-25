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

// Monday, February 26, 2018

#ifndef JTK_CORE_STRING_OBJECT_ADAPTER_H
#define JTK_CORE_STRING_OBJECT_ADAPTER_H

#include <jtk/core/ObjectAdapter.h>
#include <jtk/core/String.h>

/*******************************************************************************
 * StringObjectAdapter                                                         *
 *******************************************************************************/

/**
 * @class StringObjectAdapter
 * @ingroup jtk_core
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.0
 */
 
/**
 * @memberof jtk_core
 */
jtk_ObjectAdapter_t* jtk_StringObjectAdapter_getInstance();

/**
 * @memberof jtk_core
 */
bool jtk_StringObjectAdapter_equals(jtk_String_t* string1, jtk_String_t* string2);

/**
 * @memberof jtk_core
 */
int32_t jtk_StringObjectAdapter_hash(jtk_String_t* string);

#endif /* JTK_CORE_STRING_OBJECT_ADAPTER_H */