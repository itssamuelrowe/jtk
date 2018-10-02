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
 
// Wednesday, June 06, 2018

#ifndef JTK_COLLECTION_LIST_DOUBLY_LINKED_NODE_H
#define JTK_COLLECTION_LIST_DOUBLY_LINKED_NODE_H

#include <jtk/Configuration.h>

/*******************************************************************************
 * DoublyLinkedNode                                                            *
 *******************************************************************************/
 
typedef struct jtk_DoublyLinkedNode_t jtk_DoublyLinkedNode_t;

/**
 * @class DoublyLinkedNode
 * @ingroup jtk_collection_list
 * @author Samuel Rowe
 * @since JTK 1.0
 */
struct jtk_DoublyLinkedNode_t {
    jtk_DoublyLinkedNode_t* m_previous;
    void* m_element;
    jtk_DoublyLinkedNode_t* m_next;
};

/**
 * @memberof DoublyLinkedNode
 */
jtk_DoublyLinkedNode_t* jtk_DoublyLinkedNode_new(void* element);

/**
 * @memberof DoublyLinkedNode
 */
jtk_DoublyLinkedNode_t* jtk_DoublyLinkedNode_newWithLinks(jtk_DoublyLinkedNode_t* previous, void* element, jtk_DoublyLinkedNode_t* next);

/**
 * @memberof DoublyLinkedNode
 */
void jtk_DoublyLinkedNode_delete(jtk_DoublyLinkedNode_t* element);

#endif /* JTK_COLLECTION_LIST_DOUBLY_LINKED_NODE_H */