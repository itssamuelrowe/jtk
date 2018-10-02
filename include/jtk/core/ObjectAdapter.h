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

// Saturday, February 24, 2018

#ifndef JTK_CORE_OBJECT_ADAPTER_H
#define JTK_CORE_OBJECT_ADAPTER_H

#include <jtk/Configuration.h>

/*******************************************************************************
 * ObjectAdapter                                                               *
 *******************************************************************************/

/**
 * @memberof ObjectAdapter
 */
typedef int32_t (*jtk_ObjectAdapter_CompareFunction_t)(void* argument1, void* argument2);

/**
 * @memberof ObjectAdapter
 */
typedef bool (*jtk_ObjectAdapter_EqualsFunction_t)(void* argument1, void* argument2);

/**
 * @memberof ObjectAdapter
 */
typedef int32_t (*jtk_ObjectAdapter_HashFunction_t)(void* argument);

/**
 * @class ObjectAdapter
 * @ingroup jtk_core
 * @author Samuel Rowe
 * @since JTK 1.0
 */ 
struct jtk_ObjectAdapter_t {
    jtk_ObjectAdapter_CompareFunction_t compare;
    jtk_ObjectAdapter_EqualsFunction_t equals;
    jtk_ObjectAdapter_HashFunction_t hash;
};

/**
 * @memberof ObjectAdapter
 */
typedef struct jtk_ObjectAdapter_t jtk_ObjectAdapter_t;

#endif /* JTK_CORE_OBJECT_ADAPTER_H */