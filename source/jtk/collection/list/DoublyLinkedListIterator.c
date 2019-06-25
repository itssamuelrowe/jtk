#include <jtk/collection/list/DoublyLinkedList.h>
#include <jtk/collection/list/DoublyLinkedListIterator.h>
#include <jtk/collection/list/DoublyLinkedNode.h>

/*******************************************************************************
 * DoublyLinkedListIterator                                                    *
 *******************************************************************************/

/* Constructor */

jtk_DoublyLinkedListIterator_t* jtk_DoublyLinkedListIterator_new(
    jtk_DoublyLinkedList_t* list) {
    jtk_DoublyLinkedListIterator_t* doublyLinkedListIterator = jtk_Memory_allocate(jtk_DoublyLinkedListIterator_t, 1);

    jtk_Iterator_t* iterator = jtk_Iterator_new();
    iterator->m_destroy = (jtk_Iterator_DestroyFunction_t)jtk_DoublyLinkedListIterator_destroy;
    iterator->m_getNext = (jtk_Iterator_GetNextFunction_t)jtk_DoublyLinkedListIterator_getNext;
    iterator->m_hasNext = (jtk_Iterator_HasNextFunction_t)jtk_DoublyLinkedListIterator_hasNext;
    iterator->m_bundle = doublyLinkedListIterator;

    doublyLinkedListIterator->m_list = list;
    doublyLinkedListIterator->m_current = NULL;
    doublyLinkedListIterator->m_next = list->m_first;
    doublyLinkedListIterator->m_index = 0;
    doublyLinkedListIterator->m_iterator = iterator;

    return doublyLinkedListIterator;
}

/* Destructor */

void jtk_DoublyLinkedListIterator_delete(jtk_DoublyLinkedListIterator_t* iterator) {
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");

    if (iterator->m_iterator != NULL) {
        iterator->m_iterator->m_destroy = NULL;
        jtk_Iterator_delete(iterator->m_iterator);
    }
    jtk_Memory_deallocate(iterator);
}

/* Destroy */

void jtk_DoublyLinkedListIterator_destroy(jtk_DoublyLinkedListIterator_t* iterator) {
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");

    iterator->m_iterator = NULL;
    jtk_DoublyLinkedListIterator_delete(iterator);
}

/* Iterator */

jtk_Iterator_t* jtk_DoublyLinkedListIterator_getIterator(jtk_DoublyLinkedListIterator_t* iterator) {
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");

    return iterator->m_iterator;
}

/* Next */

bool jtk_DoublyLinkedListIterator_hasNext(jtk_DoublyLinkedListIterator_t* iterator) {
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");

    return iterator->m_index < iterator->m_list->m_size;
}

void* jtk_DoublyLinkedListIterator_getNext(jtk_DoublyLinkedListIterator_t* iterator) {
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");
    jtk_Assert_assertTrue(jtk_DoublyLinkedListIterator_hasNext(iterator), "The specified iterator is empty.");

    jtk_DoublyLinkedNode_t* current = iterator->m_next;
    
    iterator->m_current = current;
    iterator->m_next = current->m_next;
    iterator->m_index++;

    return current->m_element;
}