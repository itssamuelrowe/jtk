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