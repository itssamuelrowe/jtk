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

// Tuesday, May 15, 2018

#ifndef JTK_CORE_OBJECT_H
#define JTK_CORE_OBJECT_H

#include <jtk/Configuration.h>

/*******************************************************************************
 * Object                                                                      *
 *******************************************************************************/

// Null

/**
 * @since JTK 2.0
 */
bool jtk_Object_isNull(void* object);

/**
 * @since JTK 2.0
 */
bool jtk_Object_isNotNull(void* object);

#endif /* JTK_CORE_OBJECT_H */