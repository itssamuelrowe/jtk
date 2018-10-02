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

#include <stdlib.h>
#include <jtk/Configuration.h>

/*******************************************************************************
 * Memory                                                                      *
 *******************************************************************************/

void* jtk_Memory_allocate0(int32_t size) {
    void* object = malloc(size);
    return object;
}

void jtk_Memory_deallocate0(void* object) {
    free(object);
}