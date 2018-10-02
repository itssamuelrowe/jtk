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

#include <jtk/collection/stack/LinkedStack.h>

/*******************************************************************************
 * LinkedStack                                                                 *
 *******************************************************************************/

jtk_LinkedStack_t* jtk_LinkedStack_new() {
    jtk_LinkedStack_t* stack = jtk_Memory_allocate(jtk_LinkedStack_t, 1);
    stack->m_list = jtk_DoublyLinkedList_new();
    return stack;
}

void jtk_LinkedStack_delete(jtk_LinkedStack_t* stack) {
    jtk_Assert_assertObject(stack, "The specified stack is null.");

    jtk_DoublyLinkedList_delete(stack->m_list);
    jtk_Memory_deallocate(stack);
}

void jtk_LinkedStack_push(jtk_LinkedStack_t* stack, void* element) {
    jtk_Assert_assertObject(stack, "The specified stack is null.");

    jtk_DoublyLinkedList_addFirst(stack->m_list, element);
}

void* jtk_LinkedStack_pop(jtk_LinkedStack_t* stack) {
    jtk_Assert_assertObject(stack, "The specified stack is null.");
    jtk_Assert_assertTrue(!jtk_DoublyLinkedList_isEmpty(stack->m_list), "The specified stack is empty.");

    void* result = jtk_DoublyLinkedList_getFirst(stack->m_list);
    jtk_DoublyLinkedList_removeFirst(stack->m_list);

    return result;
}

void* jtk_LinkedStack_peek(jtk_LinkedStack_t* stack) {
    jtk_Assert_assertObject(stack, "The specified stack is null.");
    jtk_Assert_assertTrue(!jtk_DoublyLinkedList_isEmpty(stack->m_list), "The specified stack is empty.");

    return jtk_DoublyLinkedList_getFirst(stack->m_list);
}

bool jtk_LinkedStack_isEmpty(jtk_LinkedStack_t* stack) {
    jtk_Assert_assertObject(stack, "The specified stack is null.");

    return jtk_DoublyLinkedList_isEmpty(stack->m_list);
}

int32_t jtk_LinkedStack_getSize(jtk_LinkedStack_t* stack) {
    jtk_Assert_assertObject(stack, "The specified stack is null.");

    return jtk_DoublyLinkedList_getSize(stack->m_list);
}

void jtk_LinkedStack_addAll(jtk_LinkedStack_t* stack, jtk_CollectionType_t type,
    void* collection) {
    jtk_Assert_assertObject(stack, "The specified stack is null.");

    jtk_DoublyLinkedList_addAll(stack->m_list, type, collection);
}