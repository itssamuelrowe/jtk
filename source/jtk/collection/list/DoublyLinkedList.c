// Wednesday, January 10, 2018

#include <stdio.h>
#include <jtk/collection/CollectionHelper.h>
#include <jtk/collection/list/ArrayList.h>
#include <jtk/collection/list/DoublyLinkedList.h>
#include <jtk/collection/list/DoublyLinkedListIterator.h>

/*******************************************************************************
 * DoublyLinkedList                                                            *
 *******************************************************************************/

/* Constructor */

jtk_DoublyLinkedList_t* jtk_DoublyLinkedList_new() {
    return jtk_DoublyLinkedList_newEx(NULL, NULL);
}

jtk_DoublyLinkedList_t* jtk_DoublyLinkedList_newFromCollection(
    jtk_CollectionType_t type, void* collection) {
    jtk_Assert_assertObject(collection, "The specified collection is null.");

    /* An iterator is obtained from the collection. Later, the elements are
     * added to the list in the order in which the iterator returns them.
     */
    jtk_Iterator_t* iterator = jtk_CollectionHelper_getIterator(type, collection);

    /* Delegate the creation of the doubly-linked list to
     * jtk_DoublyLinkedList_newEx().
     */
    jtk_DoublyLinkedList_t* list = jtk_DoublyLinkedList_newEx(NULL, iterator);

    /* Destroy the iterator. */
    jtk_Iterator_delete(iterator);

    return list;
}

jtk_DoublyLinkedList_t* jtk_DoublyLinkedList_newFromIterator(
    jtk_Iterator_t* iterator) {
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");

    return jtk_DoublyLinkedList_newEx(NULL, iterator);
}

jtk_DoublyLinkedList_t* jtk_DoublyLinkedList_newFromAdaptor(
    jtk_ObjectAdapter_t* adapter) {
    jtk_Assert_assertObject(adapter, "The specified object adapter is null.");

    return jtk_DoublyLinkedList_newEx(adapter, NULL);
}

jtk_DoublyLinkedList_t* jtk_DoublyLinkedList_newEx(jtk_ObjectAdapter_t* adapter,
    jtk_Iterator_t* iterator) {
    jtk_DoublyLinkedList_t* list = jtk_Memory_allocate(jtk_DoublyLinkedList_t, 1);
    list->m_first = NULL;
    list->m_last = NULL;
    list->m_size = 0;
    list->m_adapter = adapter;

    if (iterator != NULL) {
        jtk_DoublyLinkedList_addAllFromIterator(list, iterator);
    }

    return list;
}

/* Destructor */

void jtk_DoublyLinkedList_delete(jtk_DoublyLinkedList_t* list) {
    jtk_Assert_assertObject(list, "The specified doubly-linked list is null.");

    jtk_DoublyLinkedNode_t* node = list->m_first;
    jtk_DoublyLinkedNode_t* temporary = NULL;
    while (node != NULL) {
        temporary = node;
        node = node->m_next;
        jtk_DoublyLinkedNode_delete(temporary);
    }
    jtk_Memory_deallocate(list);
}

/* Link (Private) */

void jtk_DoublyLinkedList_linkBefore(jtk_DoublyLinkedList_t* list,
    void* value, jtk_DoublyLinkedNode_t* node) {
    jtk_Assert_assertObject(list, "The specified doubly-linked list is null.");
    jtk_Assert_assertObject(node, "The specified doubly-linked list node is null.");

    jtk_DoublyLinkedNode_t* previous = node->m_previous;
    jtk_DoublyLinkedNode_t* next = node;
    jtk_DoublyLinkedNode_t* newNode = jtk_DoublyLinkedNode_newWithLinks(previous, value, next);
    if (previous == NULL) {
         list->m_first = newNode;
    }
    else {
        previous->m_next = newNode;
    }
    list->m_size++;
}

void  jtk_DoublyLinkedList_linkFirst(jtk_DoublyLinkedList_t* list,
    void* value) {
    jtk_Assert_assertObject(list, "The specified doubly-linked list is null.");

    jtk_DoublyLinkedNode_t* firstNode = list->m_first;
    jtk_DoublyLinkedNode_t* newNode = jtk_DoublyLinkedNode_newWithLinks(NULL, value, firstNode);
    list->m_first = newNode;
    if (firstNode == NULL) {
        list->m_last = newNode;
    }
    else {
        firstNode->m_previous = newNode;
    }
    list->m_size++;
}

void jtk_DoublyLinkedList_linkLast(jtk_DoublyLinkedList_t* list, void* value) {
    jtk_Assert_assertObject(list, "The specified doubly-linked list is null.");

    jtk_DoublyLinkedNode_t* lastNode = list->m_last;
    jtk_DoublyLinkedNode_t* newNode = jtk_DoublyLinkedNode_newWithLinks(lastNode, value, NULL);
    list->m_last = newNode;
    if (lastNode == NULL) {
        list->m_first = newNode;
    }
    else {
        lastNode->m_next = newNode;
    }
    list->m_size++;
}

/* Node (Private) */

jtk_DoublyLinkedNode_t* jtk_DoublyLinkedList_getNode(jtk_DoublyLinkedList_t* list,
    int32_t index) {
    jtk_Assert_assertObject(list, "The specified doubly-linked list is null.");
    jtk_Assert_assertTrue((index >= 0) && (index < list->m_size), "The specified index is invalid.");

    /* The linked list is divided into two halves, the lower half and the
     * upper half. The lower half begins at index 0 and extends to the middle
     * of the list. Whereas, the upper half begins at the middle and ends
     * at the last index. Depending on the index, the search begins in the
     * appropriate region. Thus, the look up algorithm is optimized.
     */
    jtk_DoublyLinkedNode_t* node = NULL;
    if (index < (list->m_size >> 1)) {
        node = list->m_first;
        int32_t i;
        for (i = 0; i < index; i++) {
            node = node->m_next;
        }
    }
    else {
        node = list->m_last;
        int32_t i;
        for (i = list->m_size - 1; i > index; i--) {
            node = node->m_previous;
        }
    }
    return node;
}

/* Unlink (Private) */

void jtk_DoublyLinkedList_unlink(jtk_DoublyLinkedList_t* list, jtk_DoublyLinkedNode_t* node) {
    jtk_Assert_assertObject(list, "The specified doubly-linked list is null.");
    jtk_Assert_assertObject(node, "The specified doubly-linked list node is null.");

    if (node->m_previous == NULL) {
        list->m_first = node->m_next;
    }
    else {
        node->m_previous->m_next = node->m_next;
    }

    if (node->m_next == NULL) {
        list->m_last = node->m_previous;
    }
    else {
        node->m_next->m_previous = node->m_previous;
    }

    jtk_DoublyLinkedNode_delete(node);
    list->m_size--;
}

void jtk_DoublyLinkedList_unlinkFirst(jtk_DoublyLinkedList_t* list) {
    jtk_Assert_assertObject(list, "The specified doubly-linked list is null.");
    jtk_Assert_assertObject(list->m_first, "The specified doubly-linked list is empty.");

    jtk_DoublyLinkedNode_t* temporary = list->m_first;
    if (list->m_first->m_next == NULL) {
        list->m_last = NULL;
        list->m_first = NULL;
    }
    else {
        list->m_first->m_next->m_previous = NULL;
        list->m_first = list->m_first->m_next;
    }
    jtk_DoublyLinkedNode_delete(temporary);
    list->m_size--;
}

void jtk_DoublyLinkedList_unlinkLast(jtk_DoublyLinkedList_t* list) {
    jtk_Assert_assertObject(list, "The specified doubly-linked list is null.");
    jtk_Assert_assertObject(list->m_last, "The specified doubly-linked list is empty.");

    jtk_DoublyLinkedNode_t* temporary = list->m_last;
    if (list->m_last->m_previous == NULL) {
        list->m_last = NULL;
        list->m_first = NULL;
    }
    else {
        list->m_last->m_previous->m_next = NULL;
        list->m_last = list->m_last->m_previous;
    }
    jtk_DoublyLinkedNode_delete(temporary);
    list->m_size--;
}

/* Add */

void jtk_DoublyLinkedList_add(jtk_DoublyLinkedList_t* list, void* value) {
    jtk_Assert_assertObject(list, "The specified doubly-linked list is null.");

    jtk_DoublyLinkedList_linkLast(list, value);
}

void jtk_DoublyLinkedList_addIndex(jtk_DoublyLinkedList_t* list, int32_t index,
    void* value) {
    jtk_Assert_assertObject(list, "The specified doubly-linked list is null.");
    jtk_Assert_assertTrue((index >= 0) && (index<= list->m_size), "The specified index is invalid.");

    if (index == list->m_size) {
        jtk_DoublyLinkedList_linkLast(list, value);
    }
    else {
        jtk_DoublyLinkedNode_t* node = jtk_DoublyLinkedList_getNode(list, index);
        jtk_DoublyLinkedList_linkBefore(list, value, node);
    }
}

void jtk_DoublyLinkedList_addAll(jtk_DoublyLinkedList_t* list,
    jtk_CollectionType_t type, void* collection) {
    jtk_Assert_assertObject(list, "The specified doubly-linked list is null.");
    jtk_Assert_assertObject(collection, "The specified collection is null.");

    /* An iterator is obtained from the collection. Later, the elements are
     * added to the list in the order in which the iterator returns them.
     */
    jtk_Iterator_t* iterator = jtk_CollectionHelper_getIterator(type, collection);

    /* Delegate the addition of the elements from the iterator to
     * jtk_DoublyLinkedList_addFromIterator() function.
     */
    jtk_DoublyLinkedList_addAllFromIterator(list, iterator);

    /* Destroy the iterator. */
    jtk_Iterator_delete(iterator);
}

void jtk_DoublyLinkedList_addAllAt(jtk_DoublyLinkedList_t* list,
    jtk_CollectionType_t type, void* collection, int32_t index) {
    jtk_Assert_assertObject(list, "The specified doubly-linked list is null.");
    jtk_Assert_assertObject(collection, "The specified iterator is null.");
    jtk_Assert_assertTrue((index >= 0) && (index<= list->m_size), "The specified index is invalid.");

    /* An iterator is obtained from the collection. Later, the elements are
     * added to the list in the order in which the iterator returns them.
     */
    jtk_Iterator_t* iterator = jtk_CollectionHelper_getIterator(type, collection);

    /* Delegate the addition of the elements from the iterator to
     * jtk_DoublyLinkedList_addFromIteratorAt() function.
     */
    jtk_DoublyLinkedList_addAllFromIteratorAt(list, iterator, index);
}

void jtk_DoublyLinkedList_addAllFromIterator(jtk_DoublyLinkedList_t* list,
    jtk_Iterator_t* iterator) {
    jtk_Assert_assertObject(list, "The specified doubly-linked list is null.");
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");

    while (jtk_Iterator_hasNext(iterator)) {
        void* value = jtk_Iterator_getNext(iterator);
        jtk_DoublyLinkedList_linkLast(list, value);
    }
}

void jtk_DoublyLinkedList_addAllFromIteratorAt(jtk_DoublyLinkedList_t* list,
    jtk_Iterator_t* iterator, int32_t index) {
    jtk_Assert_assertObject(list, "The specified doubly-linked list is null.");
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");
    jtk_Assert_assertTrue((index >= 0) && (index<= list->m_size), "The specified index is invalid.");

    jtk_ArrayList_t* temporary = jtk_ArrayList_newFromIterator(iterator);
    int32_t temporarySize = jtk_ArrayList_getSize(temporary);

    /* Alternatively, a chain of nodes representing the elements obtained from
     * the iterator is created first, called the subchain. Later, the first node
     * of the subchain is linked to the node before the index. The last node of
     * the subchain is linked to the node after the index.
     *
     * Special cases include:
     *     -- When the insertion is at the beginning of the list. In such cases,
     *        the first node of the subchain is made the head of the list.
     *     -- When the insertion is at the end of the list. In such cases,
     *        the last node of the subchain is made the tail of the list.
     */

    /* For the purpose of inserting the elements from the iterator, two pointers
     * are employed. The backward pointer refers to the element before the cursor.
     * On the other hand, the forward pointer refers to the element after the
     * cursor. The cursor is an imaginary position existing between two successive
     * indexes.
     */
    jtk_DoublyLinkedNode_t* backward = NULL;
    jtk_DoublyLinkedNode_t* forward = NULL;

    /* If the elements are required to be added at the end of the list,
     * there are no elements ahead. Therefore, the forward reference is null.
     * The backward reference points to the last element.
     */
    if (index == list->m_size) {
        forward = NULL;
        backward = list->m_last;
    }
    else {
        /* The forward reference points to the element after the index.
         * The backward reference points to the element before the index;
         * for the first index, it is always null.
         */
        forward = jtk_DoublyLinkedList_getNode(list, index);
        backward = forward->m_previous;
    }

    /* Iterate over all the elements from the iterator. Add each element to
     * the list.
     */
    int32_t i;
    for (i = 0; i < temporarySize; i++) {
        void* value = jtk_ArrayList_getValue(temporary, i);

        /* Create a new node to represent an element. The next link is updated
         * later on.
         */
        jtk_DoublyLinkedNode_t* node = jtk_DoublyLinkedNode_newWithLinks(backward, value, NULL);

        /* If the insertion is at the beginning of the list, update the pointer
         * to the first node.
         */
        if (backward == NULL) {
            list->m_first = node;
        }
        else {
            /* Otherwise, update the link in the node before the index. */
            backward->m_next = node;
        }
        /* The backward pointer is updated for the next iteration in advance. */
        backward = node;
    }

    /* If the insertion is at the end of the list, make the last node of
     * the subchain the tail.
     */
    if (forward == NULL) {
        list->m_last = backward;
    }
    else {
        /* Bind the newly added nodes with the previously existing nodes. */
        backward->m_next = forward;
        forward->m_previous = backward;
    }

    /* Update the size of the list. */
    list->m_size += temporarySize;

    /* Destroy the temporary array list. */
    jtk_ArrayList_delete(temporary);
}

void jtk_DoublyLinkedList_addFirst(jtk_DoublyLinkedList_t* list, void* value) {
    jtk_Assert_assertObject(list, "The specified doubly-linked list is null.");

    jtk_DoublyLinkedList_linkFirst(list, value);
}

void jtk_DoublyLinkedList_addLast(jtk_DoublyLinkedList_t* list, void* value) {
    jtk_Assert_assertObject(list, "The specified doubly-linked list is null.");

    jtk_DoublyLinkedList_linkLast(list, value);
}

/* Add Predicatively */

void jtk_DoublyLinkedList_addPredicatively(jtk_DoublyLinkedList_t* list,
    void* value, jtk_PredicateFunction_t predicate) {
    jtk_Assert_assertObject(list, "The specified doubly-linked list is null.");
    jtk_Assert_assertObject((void*)predicate, "The specified predicate function is null.");

    if (predicate(value)) {
        jtk_DoublyLinkedList_linkLast(list, value);
    }
}

void jtk_DoublyLinkedList_addFirstPredicatively(jtk_DoublyLinkedList_t* list,
    void* value, jtk_PredicateFunction_t predicate) {
    jtk_Assert_assertObject(list, "The specified doubly-linked list is null.");
    jtk_Assert_assertObject((void*)predicate, "The specified predicate function is null.");

    if (predicate(value)) {
        jtk_DoublyLinkedList_linkFirst(list, value);
    }
}

void jtk_DoublyLinkedList_addLastPredicatively(jtk_DoublyLinkedList_t* list,
    void* value, jtk_PredicateFunction_t predicate) {
    jtk_Assert_assertObject(list, "The specified doubly-linked list is null.");
    jtk_Assert_assertObject((void*)predicate, "The specified predicate function is null.");

    if (predicate(value)) {
        jtk_DoublyLinkedList_linkLast(list, value);
    }
}

/* DoublyLinkedList-to-Array */

jtk_Array_t* jtk_DoublyLinkedList_toArray(jtk_DoublyLinkedList_t* list) {
    jtk_Assert_assertObject(list, "The specified doubly-linked list is null.");

    jtk_Array_t* result = jtk_Array_new(list->m_size);
    int32_t i = 0;
    jtk_DoublyLinkedNode_t* node = list->m_first;
    while (node != NULL) {
        jtk_Array_setValue(result, i++, node->m_element);
        node = node->m_next;
    }
    return result;
}

void** jtk_DoublyLinkedList_toRawArray(jtk_DoublyLinkedList_t* list) {
    jtk_Assert_assertObject(list, "The specified doubly-linked list is null.");

    void** result = jtk_Memory_allocate(void*, list->m_size);
    int32_t i = 0;
    jtk_DoublyLinkedNode_t* node = list->m_first;
    while (node != NULL) {
        result[i++] = node->m_element;
        node = node->m_next;
    }
    return result;
}

/* Clear */

void jtk_DoublyLinkedList_clear(jtk_DoublyLinkedList_t* list) {
    jtk_Assert_assertObject(list, "The specified doubly-linked list is null.");

    jtk_DoublyLinkedNode_t* node = list->m_first;
    jtk_DoublyLinkedNode_t* temporary = NULL;
    while (node != NULL) {
        temporary = node;
        node = node->m_next;
        jtk_DoublyLinkedNode_delete(temporary);
    }
    list->m_first = NULL;
    list->m_last = NULL;
    list->m_size = 0;
}

/* Copy */

int32_t jtk_DoublyLinkedList_copy(jtk_DoublyLinkedList_t* list, jtk_Array_t* array) {
    jtk_Assert_assertObject(list, "The specified doubly-linked list is null.");

    jtk_DoublyLinkedNode_t* node = list->m_first;
    int32_t i = 0;
    int32_t arraySize = jtk_Array_getSize(array);
    while ((node != NULL) && (i < arraySize)) {
        jtk_Array_setValue(array, i++, node->m_element);
        node = node->m_next;
    }

    return i;
}

int32_t jtk_DoublyLinkedList_copyEx(jtk_DoublyLinkedList_t* list, jtk_Array_t* array,
    int32_t index) {
    jtk_Assert_assertObject(list, "The specified doubly-linked list is null.");

    int32_t arraySize = jtk_Array_getSize(array);
    jtk_Assert_assertTrue((index >= 0) && (index < arraySize), "The specified index is invalid.");

    jtk_DoublyLinkedNode_t* node = list->m_first;
    int32_t i = index;
    while ((node != NULL) && (i < arraySize)) {
        jtk_Array_setValue(array, i++, node->m_element);
        node = node->m_next;
    }

    return i;
}

/* Contains */

// TODO: Protect all the adapter accessing functions from null adapters.

/* The documentation for the jtk_ObjectAdapter_t class states that an adapter
 * must define all the functions, employing empty functions wherever the
 * programmer finds a callback is unnecessary.
 */
bool jtk_DoublyLinkedList_contains(jtk_DoublyLinkedList_t* list, void* value) {
    jtk_Assert_assertObject(list, "The specified doubly-linked list is null.");

    jtk_DoublyLinkedNode_t* node = list->m_first;
    while (node != NULL) {
        if (((list->m_adapter != NULL) && list->m_adapter->equals(node->m_element, value)) ||
            (node->m_element == value)) {
            return true;
        }
        node = node->m_next;
    }
    return false;
}

// TODO: Update all functions using jtk_CollectionHelper_getIterator() to check for null values.
bool jtk_DoublyLinkedList_containsAll(jtk_DoublyLinkedList_t* list,
    jtk_CollectionType_t type, void* collection) {
    jtk_Assert_assertObject(list, "The specified doubly-linked list is null.");
    jtk_Assert_assertObject(collection, "The specified collection list is null.");

    bool result = false;

    /* Obtain an iterator for the specified collection type and collection. */
    jtk_Iterator_t* iterator = jtk_CollectionHelper_getIterator(type, collection);

    /* If an unknown collection type is specified, the functions returns false. */
    if (iterator != NULL) {
        /* Delegate the search to jtk_DoublyLinkedList_containsAllFromIterator()
         * function which applies a specialized linear search over the elements
         * in the list.
         */
        result = jtk_DoublyLinkedList_containsAllFromIterator(list, iterator);

        /* Destroy the iterator. */
        jtk_Iterator_delete(iterator);
    }

    /* Return the result. */
    return result;
}

bool jtk_DoublyLinkedList_containsAllFromIterator(jtk_DoublyLinkedList_t* list,
    jtk_Iterator_t* iterator) {
    jtk_Assert_assertObject(list, "The specified doubly-linked list is null.");
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");

    bool result = true;
    while (jtk_Iterator_hasNext(iterator)) {
        void* value = jtk_Iterator_getNext(iterator);
        if (!jtk_DoublyLinkedList_contains(list, value)) {
            result = false;
            break;
        }
    }
    return result;
}

/* Empty */

bool jtk_DoublyLinkedList_isEmpty(jtk_DoublyLinkedList_t* list) {
    jtk_Assert_assertObject(list, "The specified doubly-linked list is null.");

    return list->m_size == 0;
}

/* Find */

int32_t jtk_DoublyLinkedList_find(jtk_DoublyLinkedList_t* list, void* value) {
    jtk_Assert_assertObject(list, "The specified doubly-linked list is null.");

    return (list->m_size != 0)? jtk_DoublyLinkedList_findInRange(list, value, 0, list->m_size) : -1;
}

int32_t jtk_DoublyLinkedList_findAfter(jtk_DoublyLinkedList_t* list, void* value,
    int32_t index) {
    jtk_Assert_assertObject(list, "The specified doubly-linked list is null.");
    jtk_Assert_assertTrue((index >= 0) && (index < list->m_size), "The specified index is invalid.");

    /* jtk_ArrayList_findInRange() states that the start index is inclusive
     * in the linear search algorithm it implements. Therefore, increment
     * the index by one before delegating the search.
     */
    return (list->m_size != 0)? jtk_DoublyLinkedList_findInRange(list, value, index + 1, list->m_size) : -1;

}

int32_t jtk_DoublyLinkedList_findBefore(jtk_DoublyLinkedList_t* list,
    void* value, int32_t index) {
    jtk_Assert_assertObject(list, "The specified doubly-linked list is null.");
    jtk_Assert_assertTrue((index >= 0) && (index <= list->m_size), "The specified index is invalid.");

    return (list->m_size != 0)? jtk_DoublyLinkedList_findInRange(list, value, 0, index) : -1;
}

int32_t jtk_DoublyLinkedList_findInRange(jtk_DoublyLinkedList_t* list,
    void* value, int32_t startIndex, int32_t stopIndex) {
    jtk_Assert_assertObject(list, "The specified doubly-linked list is null.");
    jtk_Assert_assertTrue((startIndex >= 0) && (startIndex <= stopIndex) &&
        (stopIndex <= list->m_size), "The specified range is invalid.");

    /* Retrieve the first node within the search range. */
    jtk_DoublyLinkedNode_t* node = jtk_DoublyLinkedList_getNode(list, startIndex);

    int32_t result = -1;
    for (int32_t i = startIndex; i < stopIndex; i++) {
        /* The documentation for the comparator function states that an
         * implementation of a comparator is required to provide comparison
         * of two objects for equivality, at least. Further, the equals()
         * and compare() function should return consistent values for equal
         * values. Thus, they are interchangeable.
         */
        if (list->m_adapter->equals(node->m_element, value)) {
            result = i;
            break;
        }

        /* Move to the next node. */
        node = node->m_next;
    }
    return result;
}

/* Find Last */

int32_t jtk_DoublyLinkedList_findLast(jtk_DoublyLinkedList_t* list, void* value) {
    jtk_Assert_assertObject(list, "The specified array list is null.");

    return (list->m_size != 0)? jtk_DoublyLinkedList_findLastInRange(list, value, 0, list->m_size) : -1;
}

int32_t jtk_DoublyLinkedList_findLastAfter(jtk_DoublyLinkedList_t* list, void* value,
    int32_t index) {
    jtk_Assert_assertObject(list, "The specified array list is null.");
    jtk_Assert_assertTrue((index >= 0) && (index < list->m_size), "The specified index is invalid.");

    /* jtk_DoublyLinkedList_findLastInRange() states that the start index is inclusive
     * in the linear search algorithm it implements. Therefore, increment
     * the index by one before delegating the search.
     */
    return (list->m_size != 0)? jtk_DoublyLinkedList_findLastInRange(list, value, index + 1, list->m_size) : -1;
}

int32_t jtk_DoublyLinkedList_findLastBefore(jtk_DoublyLinkedList_t* list, void* value,
    int32_t index) {
    jtk_Assert_assertObject(list, "The specified array list is null.");
    jtk_Assert_assertTrue((index >= 0) && (index <= list->m_size), "The specified index is invalid.");

    return (list->m_size != 0)? jtk_DoublyLinkedList_findLastInRange(list, value, 0, index) : -1;
}

int32_t jtk_DoublyLinkedList_findLastInRange(jtk_DoublyLinkedList_t* list, void* value,
    int32_t startIndex, int32_t stopIndex) {
    jtk_Assert_assertObject(list, "The specified array list is null.");
    jtk_Assert_assertTrue((startIndex >= 0) && (startIndex <= stopIndex) &&
        (stopIndex <= list->m_size), "The specified range is invalid.");

    /* Retrieve the last node within the search range. */
    int32_t lastIndex = stopIndex - 1;
    jtk_DoublyLinkedNode_t* node = jtk_DoublyLinkedList_getNode(list, lastIndex);

    int32_t result = -1;
    for (int32_t i = lastIndex; i >= startIndex; i--) {
        /* The documentation for the comparator function states that an
         * implementation of a comparator is required to provide comparison
         * of two objects for equivality, at least. Further, the equals()
         * and compare() function should return consistent values for equal
         * values. Thus, they are interchangeable.
         */
        if (list->m_adapter->equals(node->m_element, value)) {
            result = i;
            break;
        }

        /* Move to the next node. */
        node = node->m_previous;
    }
    return result;
}

/* Iterator */

jtk_Iterator_t* jtk_DoublyLinkedList_getIterator(jtk_DoublyLinkedList_t* list) {
    jtk_Assert_assertObject(list, "The specified doubly-linked list is null.");

    jtk_DoublyLinkedListIterator_t* iterator = jtk_DoublyLinkedListIterator_new(list);
    return jtk_DoublyLinkedListIterator_getIterator(iterator);
}

/* Remove */

bool jtk_DoublyLinkedList_remove(jtk_DoublyLinkedList_t* list, void* value) {
    jtk_Assert_assertObject(list, "The specified doubly-linked list is null.");

    bool result = false;
    jtk_DoublyLinkedNode_t* node = list->m_first;
    while (node != NULL) {
        if (((list->m_adapter != NULL) && list->m_adapter->equals(node->m_element, value)) ||
            (node->m_element == value)) {
            jtk_DoublyLinkedList_unlink(list, node);
            result = true;
            break;
        }
        node = node->m_next;
    }
    return result;
}

int32_t jtk_DoublyLinkedList_removeAll(jtk_DoublyLinkedList_t* list,
    jtk_CollectionType_t type, void* collection) {
    jtk_Assert_assertObject(list, "The specified doubly-linked list is null.");
    jtk_Assert_assertObject(collection, "The specified collection list is null.");

    int32_t result = 0;

    /* Obtain an iterator for the specified collection type and collection. */
    jtk_Iterator_t* iterator = jtk_CollectionHelper_getIterator(type, collection);

    /* If an unknown collection type is specified, the functions returns false. */
    if (iterator != NULL) {
        /* Delegate the deletion to jtk_DoublyLinkedList_removeAllFromIterator()
         * function which applies a specialized linear search over the elements
         * in the list.
         */
        result = jtk_DoublyLinkedList_removeAllFromIterator(list, iterator);

        /* Destroy the iterator. */
        jtk_Iterator_delete(iterator);
    }

    /* Return the result. */
    return result;
}

int32_t jtk_DoublyLinkedList_removeAllFromIterator(jtk_DoublyLinkedList_t* list,
    jtk_Iterator_t* iterator) {
    jtk_Assert_assertObject(list, "The specified doubly-linked list is null.");
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");

    int32_t result = 0;
    jtk_ArrayList_t* temporary = jtk_ArrayList_newFromIterator(iterator);
    jtk_DoublyLinkedNode_t* node = list->m_first;
    while (node != NULL) {
        if (jtk_ArrayList_contains(temporary, node->m_element)) {
            result++;
            jtk_DoublyLinkedList_unlink(list, node);
        }
        node = node->m_next;
    }
    jtk_ArrayList_delete(temporary);
    
    return result;
}

void jtk_DoublyLinkedList_removeIndex(jtk_DoublyLinkedList_t* list,
    int32_t index) {
    jtk_Assert_assertObject(list, "The specified doubly-linked list is null.");
    jtk_Assert_assertTrue((index >= 0) && (index < list->m_size), "The specified index is invalid.");

    jtk_DoublyLinkedNode_t* node = jtk_DoublyLinkedList_getNode(list, index);
    jtk_DoublyLinkedList_unlink(list, node);
}

void jtk_DoublyLinkedList_removeRange(jtk_DoublyLinkedList_t* list,
    int32_t startIndex, int32_t stopIndex) {
    jtk_Assert_assertObject(list, "The specified doubly-linked list is null.");
    jtk_Assert_assertTrue((startIndex >= 0) && (startIndex <= stopIndex) &&
        (stopIndex <= list->m_size), "The specified range is invalid.");

    jtk_DoublyLinkedNode_t* node = jtk_DoublyLinkedList_getNode(list, startIndex);
    int32_t i;
    for (i = startIndex; i < stopIndex; i++) {
        jtk_DoublyLinkedNode_t* next = node->m_next;
        jtk_DoublyLinkedList_unlink(list, node);
        node = next;
    }
}

void jtk_DoublyLinkedList_removeFirst(jtk_DoublyLinkedList_t* list) {
    jtk_DoublyLinkedList_unlinkFirst(list);
}

void jtk_DoublyLinkedList_removeLast(jtk_DoublyLinkedList_t* list) {
    jtk_DoublyLinkedList_unlinkLast(list);
}

/* Size */

int32_t jtk_DoublyLinkedList_getSize(jtk_DoublyLinkedList_t* list) {
    return list->m_size;
}

/* Value */

void* jtk_DoublyLinkedList_getValue(jtk_DoublyLinkedList_t* list, int32_t index) {
    jtk_Assert_assertTrue((index >= 0) && (index < list->m_size), "The specified index is invalid.");
    jtk_DoublyLinkedNode_t* node = jtk_DoublyLinkedList_getNode(list, index);
    return node->m_element;
}

void jtk_DoublyLinkedList_setValue(jtk_DoublyLinkedList_t* list, int32_t index,
    void* value) {
    jtk_Assert_assertTrue((index >= 0) && (index < list->m_size), "The specified index is invalid.");

    jtk_DoublyLinkedNode_t* node = jtk_DoublyLinkedList_getNode(list, index);
    node->m_element = value;
}

void* jtk_DoublyLinkedList_getFirst(jtk_DoublyLinkedList_t* list) {
    return list->m_first->m_element;
}

void jtk_DoublyLinkedList_setFirst(jtk_DoublyLinkedList_t* list, int32_t index,
    void* value) {
    jtk_Assert_assertTrue((index >= 0) && (index < list->m_size), "The specified index is invalid.");

    list->m_first->m_element = value;
}

void* jtk_DoublyLinkedList_getLast(jtk_DoublyLinkedList_t* list) {
    return list->m_last->m_element;
}

void jtk_DoublyLinkedList_setLast(jtk_DoublyLinkedList_t* list, int32_t index,
    void* value) {
    jtk_Assert_assertTrue((index >= 0) && (index < list->m_size), "The specified index is invalid.");

    list->m_last->m_element = value;
}