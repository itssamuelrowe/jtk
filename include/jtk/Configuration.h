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

// Friday, May 18, 2018

#ifndef JTK_CONFIGURATION_H
#define JTK_CONFIGURATION_H

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>

#define jtk_Memory_allocate(type, units) (type*)jtk_Memory_allocate0(sizeof (type) * (units))
#define jtk_Memory_deallocate(object) jtk_Memory_deallocate0(object)

#define jtk_Assert_assertObject(object, message) assert((object) != NULL)
#define jtk_Assert_assertTrue(expression, message) assert(expression)
#define jtk_Assert_assertFalse(expression, message) assert(!(expression))

void* jtk_Memory_allocate0(int32_t size);
void jtk_Memory_deallocate0(void* object);

#endif /* JTK_CONFIGURATION_H */