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

// Sunday, June 03, 2018

#ifndef JTK_FUNCTION_COMPARATOR_FUNCTION_H
#define JTK_FUNCTION_COMPARATOR_FUNCTION_H

#include <jtk/Configuration.h>

/*******************************************************************************
 * ComparatorFunction                                                          *
 *******************************************************************************/

/**
 * @ingroup jtk_function
 * @author Samuel Rowe
 * @since JTK 1.0
 */
typedef int32_t (*jtk_ComparatorFunction_t)(void* argument1, void* argument2);

#endif /* JTK_FUNCTION_COMPARATOR_FUNCTION_H */