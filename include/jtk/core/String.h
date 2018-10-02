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

// Saturday, November 04, 2017

#ifndef JTK_CORE_STRING_H
#define JTK_CORE_STRING_H

#include <jtk/Configuration.h>

/*******************************************************************************
 * String                                                                      *
 *******************************************************************************/

/**
 * @class String
 * @ingroup jtk_core
 * @author Samuel Rowe
 * @since JTK 1.0
 */

/**
 * @memberof String
 */
uint8_t* jtk_String_new(const uint8_t* string);

/**
 * @memberof String
 */
uint8_t* jtk_String_newWithSize(const uint8_t* string, int32_t size);

/**
 * @memberof String
 */
void jtk_String_delete(uint8_t* string);

/**
 * @memberof String
 */
bool jtk_String_equals(const uint8_t* string1, int32_t size1, const uint8_t* string2, int32_t size2);

/**
 * @memberof String
 */
int32_t jtk_String_getLength(const uint8_t* string);

/**
 * @memberof String
 */
int32_t jtk_String_hash(const uint8_t* string);

#endif /* JTK_CORE_STRING_H */