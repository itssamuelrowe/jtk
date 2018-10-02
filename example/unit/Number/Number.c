/*
 *                              Jez Toolkit (JTK)
 *     Copyright (C) 2018 OneCube Software Solutions. All rights reserved.
 *
 * This file is part of Jez Toolkit Example Suite, version 1.0. The contents of
 * this file, either partially or fully, may be used, distributed and modified
 * without any limitation.
 */

// Wednesday, June 27, 2018

#include "Number.h"

/*******************************************************************************
 * Number                                                                      *
 *******************************************************************************/

#include "Number.h"

/*
 * Determines whether the specified number is odd, or not.
 */
bool example_Number_isOdd(int32_t number) {
    return (number % 2) == 1;
}

/*
 * Determines whether the specified number is odd, or not.
 */
bool example_Number_isEven(int32_t number) {
    return (number % 2) == 0;
}