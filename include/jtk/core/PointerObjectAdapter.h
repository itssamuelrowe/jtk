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

// Monday, February 26, 2018

#ifndef JTK_CORE_POINTER_OBJECT_ADAPTER_H
#define JTK_CORE_POINTER_OBJECT_ADAPTER_H

#include <jtk/core/ObjectAdapter.h>

/*******************************************************************************
 * PointerObjectAdapter                                                        *
 *******************************************************************************/

/**
 * @class PointerObjectAdapter
 * @ingroup jtk_core
 * @author Samuel Rowe
 * @since JTK 1.0
 */

/**
 * @memberof PointerObjectAdapter
 */
jtk_ObjectAdapter_t* jtk_PointerObjectAdapter_getInstance();

/**
 * @memberof PointerObjectAdapter
 */
int32_t jtk_PointerObjectAdapter_compare(const void* pointer1, const void* pointer2);

/**
 * @memberof PointerObjectAdapter
 */
bool jtk_PointerObjectAdapter_equals(const void* pointer1, const void* pointer2);

/**
 * @memberof PointerObjectAdapter
 */
int32_t jtk_PointerObjectAdapter_hash(const void* pointer);

#endif /* JTK_CORE_POINTER_OBJECT_ADAPTER_H */