// Thursday, June 07, 2018

#ifndef JTK_COLLECTION_LIST_XOR_LINKED_LIST_ITERATOR_H
#define JTK_COLLECTION_LIST_XOR_LINKED_LIST_ITERATOR_H

/*******************************************************************************
 * XorLinkedListIterator                                                    *
 *******************************************************************************/

struct jtk_XorLinkedListIterator_t {
    jtk_XorLinkedList_t* m_list;
    jtk_XorLinkedNode_t* m_current;
    jtk_XorLinkedNode_t* m_next;
    int32_t m_index;
    jtk_Iterator_t* m_iterator;
};

typedef struct jtk_XorLinkedListIterator_t jtk_XorLinkedListIterator_t;

jtk_XorLinkedListIterator_t* jtk_XorLinkedListIterator_new(jtk_XorLinkedList_t* list);
void jtk_XorLinkedListIterator_delete(jtk_XorLinkedListIterator_t* list);

#endif /* JTK_COLLECTION_LIST_XOR_LINKED_LIST_ITERATOR_H */