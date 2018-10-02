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

// Saturday, December 02, 2017

#ifndef JTK_COLLECTION_ARRAY_STACK_H
#define JTK_COLLECTION_ARRAY_STACK_H

#include <jtk/collection/list/ArrayList.h>
#include <jtk/collection/CollectionType.h>

/*******************************************************************************
 * ArrayStack                                                                  *
 *******************************************************************************/

/**
 * @class ArrayStack
 * @ingroup jtk_collection_stack
 * @author Samuel Rowe
 * @since JTK 1.0
 */
struct jtk_ArrayStack_t {
    jtk_ArrayList_t* m_list;
};

/**
 * @memberof ArrayStack
 */
typedef struct jtk_ArrayStack_t jtk_ArrayStack_t;

/**
 * @memberof ArrayStack
 */
jtk_ArrayStack_t* jtk_ArrayStack_new();

/**
 * @memberof ArrayStack
 */
void jtk_ArrayStack_delete(jtk_ArrayStack_t* stack);

/**
 * @memberof ArrayStack
 */
void jtk_ArrayStack_push(jtk_ArrayStack_t* stack, void* element);

/**
 * @memberof ArrayStack
 */
void jtk_ArrayStack_pop(jtk_ArrayStack_t* stack);

/**
 * @memberof ArrayStack
 */
void* jtk_ArrayStack_peek(jtk_ArrayStack_t* stack);

/**
 * @memberof ArrayStack
 */
bool jtk_ArrayStack_isEmpty(jtk_ArrayStack_t* stack);

/**
 * @memberof ArrayStack
 */
int32_t jtk_ArrayStack_getSize(jtk_ArrayStack_t* stack);

/**
 * @memberof ArrayStack
 */
void jtk_ArrayStack_addAll(jtk_ArrayStack_t* stack, jtk_CollectionType_t type, void* collection);

#endif /* JTK_COLLECTION_ARRAY_STACK_H */