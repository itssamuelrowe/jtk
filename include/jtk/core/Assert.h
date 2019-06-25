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

// Monday, May 21, 2018

#ifndef JTK_CORE_ASSERT_H
#define JTK_CORE_ASSERT_H

#include <jtk/Configuration.h>

/*******************************************************************************
 * Assert                                                                      *
 *******************************************************************************/

/**
 * @class Assert
 * @ingroup jtk_core
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.0
 */

/**
 * @memberof Assert
 */
#define jtk_Assert_assertObject(object, message) assert((object) != NULL)

/**
 * @memberof Assert
 */
#define jtk_Assert_assertTrue(expression, message) assert(expression)

/**
 * @memberof Assert
 */
#define jtk_Assert_assertFalse(expression, message) assert(!(expression))

#endif /* JTK_CORE_ASSERT_H */