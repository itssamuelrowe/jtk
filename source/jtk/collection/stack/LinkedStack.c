/*
 * Copyright 2017-2020 Samuel Rowe
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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