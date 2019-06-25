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
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
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