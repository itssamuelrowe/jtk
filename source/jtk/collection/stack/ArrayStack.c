/*
 * Copyright 2018-2019 OneCube
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