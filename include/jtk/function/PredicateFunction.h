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

// Tuesday, May 15, 2018

#ifndef JTK_FUNCTION_PREDICATE_FUNCTION_H
#define JTK_FUNCTION_PREDICATE_FUNCTION_H

#include <jtk/Configuration.h>

/*******************************************************************************
 * PredicateFunction                                                           *
 *******************************************************************************/

/**
 * @ingroup jtk_function
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.1
 */
typedef bool (*jtk_MixedPredicateFunction_t)(const void* argument);

/**
 * @ingroup jtk_function
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.1
 */
typedef bool (*jtk_IntegerPredicateFunction_t)(int32_t argument);

/**
 * @ingroup jtk_function
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.1
 */
typedef bool (*jtk_LongPredicateFunction_t)(int64_t argument);

/**
 * @ingroup jtk_function
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.1
 */
typedef bool (*jtk_FloatPredicateFunction_t)(float argument);

/**
 * @ingroup jtk_function
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.1
 */
typedef bool (*jtk_DoublePredicateFunction_t)(double argument);

#endif /* JTK_FUNCTION_PREDICATE_FUNCTION_H */