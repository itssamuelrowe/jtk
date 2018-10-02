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

// Monday, July 02, 2018

#include <jtk/collection/list/DoublyLinkedNode.h>

/*******************************************************************************
 * DoublyLinkedNode                                                        *
 *******************************************************************************/

/* Constructor */
 
jtk_DoublyLinkedNode_t* jtk_DoublyLinkedNode_new(void* element) {
    jtk_DoublyLinkedNode_t* node = jtk_Memory_allocate(jtk_DoublyLinkedNode_t, 1);
    node->m_previous = NULL;
    node->m_element = element;
    node->m_next = NULL;
    return node;
}

jtk_DoublyLinkedNode_t* jtk_DoublyLinkedNode_newWithLinks(
    jtk_DoublyLinkedNode_t* previous, void* element,
    jtk_DoublyLinkedNode_t* next) {
    jtk_DoublyLinkedNode_t* node = jtk_Memory_allocate(jtk_DoublyLinkedNode_t, 1);
    node->m_previous = previous;
    node->m_element = element;
    node->m_next = next;

    return node;
}

/* Destructor */

void jtk_DoublyLinkedNode_delete(jtk_DoublyLinkedNode_t* node) {
    jtk_Assert_assertObject(node, "The specified doubly-linked node is null.");

    jtk_Memory_deallocate(node);
}