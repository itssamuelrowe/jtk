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

#include <jtk/collection/stack/ArrayStack.h>

jtk_ArrayStack_t* jtk_ArrayStack_new() {
    jtk_ArrayStack_t* stack = jtk_Memory_allocate(jtk_ArrayStack_t, 1);
    stack->m_list = jtk_ArrayList_new();
    return stack;
}

void jtk_ArrayStack_delete(jtk_ArrayStack_t* stack) {
    jtk_Assert_assertObject(stack, "The specified stack is null.");
    jtk_ArrayList_delete(stack->m_list);
    jtk_Memory_deallocate(stack);
}

void jtk_ArrayStack_push(jtk_ArrayStack_t* stack, void* element) {
    jtk_Assert_assertObject(stack, "The specified stack is null.");
    jtk_ArrayList_addFirst(stack->m_list, element);
}

void jtk_ArrayStack_pop(jtk_ArrayStack_t* stack) {
    jtk_Assert_assertObject(stack, "The specified stack is null.");
    jtk_Assert_assertFalse(jtk_ArrayList_isEmpty(stack->m_list), "The specified stack is empty.");
    jtk_ArrayList_removeIndex(stack->m_list, 0);
}

void* jtk_ArrayStack_peek(jtk_ArrayStack_t* stack) {
    jtk_Assert_assertObject(stack, "The specified stack is null.");
    jtk_Assert_assertTrue(jtk_ArrayList_getSize(stack->m_list) > 0, "The specified stack is empty.");
    
    return jtk_ArrayList_getValue(stack->m_list, 0);
}

bool jtk_ArrayStack_isEmpty(jtk_ArrayStack_t* stack) {
    jtk_Assert_assertObject(stack, "The specified stack is null.");
    return jtk_ArrayList_isEmpty(stack->m_list);
}

int32_t jtk_ArrayStack_getSize(jtk_ArrayStack_t* stack) {
    jtk_Assert_assertObject(stack, "The specified stack is null.");
    return jtk_ArrayList_getSize(stack->m_list);
}

void jtk_ArrayStack_addAll(jtk_ArrayStack_t* stack, jtk_CollectionType_t type,
    void* collection) {
    jtk_Assert_assertObject(stack, "The specified stack is null.");
    return jtk_ArrayList_addAll(stack->m_list, type, collection);
}