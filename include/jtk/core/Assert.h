/*
 *                              Jez Toolkit (JTK)
 *     Copyright (C) 2018 OneCube Software Solutions. All rights reserved.
 *
 * This file is part of Jez Toolkit Free Edition, version 1.0.
 *
 * See the file "LICENSE" included in the distribution for the terms and conditions,
 * or visit http://www.onecube.in/jtk/free-license.
 *
 * IMPORTANT NOTE: You may NOT copy the content of this file, either partially
 * or fully, into your source code.
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
 * @author Samuel Rowe
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