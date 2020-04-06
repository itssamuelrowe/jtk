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

// Sunday, June 03, 2018

#ifndef JTK_FUNCTION_COMPARATOR_FUNCTION_H
#define JTK_FUNCTION_COMPARATOR_FUNCTION_H

#include <jtk/Configuration.h>

/*******************************************************************************
 * ComparatorFunction                                                          *
 *******************************************************************************/

/**
 * @ingroup jtk_function
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.0
 */
typedef int32_t (*jtk_ComparatorFunction_t)(void* argument1, void* argument2);

#endif /* JTK_FUNCTION_COMPARATOR_FUNCTION_H */