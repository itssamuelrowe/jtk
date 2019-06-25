// Thursday, June 07, 2018

#ifndef JTK_COLLECTION_LIST_XOR_LINKED_NODE_H
#define JTK_COLLECTION_LIST_XOR_LINKED_NODE_H

/*******************************************************************************
 * XorLinkedNode                                                               *
 *******************************************************************************/

struct jtk_XorLinkedNode_t {
    void* m_element;
    intptr_t m_links;
};

typedef struct jtk_XorLinkedNode_t jtk_XorLinkedNode_t;

/* Constructor */

jtk_XorLinkedNode_t* jtk_XorLinkedNode_new(void* element);
jtk_XorLinkedNode_t* jtk_XorLinkedNode_newWithLinks(jtk_XorLinkedNode_t* previous, void* element, jtk_XorLinkedNode_t* next);

/* Destructor */

void jtk_XorLinkedNode_delete(jtk_XorLinkedNode_t* element);

#endif /* JTK_COLLECTION_LIST_XOR_LINKED_NODE_H */