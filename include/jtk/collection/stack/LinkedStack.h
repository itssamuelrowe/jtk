// Monday, January 08, 2018

#ifndef JTK_COLLECTION_LINKED_STACK_H
#define JTK_COLLECTION_LINKED_STACK_H

#include <jtk/collection/list/DoublyLinkedList.h>
#include <jtk/collection/CollectionType.h>

/*******************************************************************************
 * LinkedStack                                                                 *
 *******************************************************************************/

/**
 * @class LinkedStack
 * @ingroup jtk_collection_stack
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.0
 */
struct jtk_LinkedStack_t {
    jtk_DoublyLinkedList_t* m_list;
};

/**
 * @memberof LinkedStack
 */
typedef struct jtk_LinkedStack_t jtk_LinkedStack_t;

/**
 * @memberof LinkedStack
 */
jtk_LinkedStack_t* jtk_LinkedStack_new();

/**
 * @memberof LinkedStack
 */
void jtk_LinkedStack_delete(jtk_LinkedStack_t* stack);

/**
 * @memberof LinkedStack
 */
void jtk_LinkedStack_push(jtk_LinkedStack_t* stack, void* element);

/**
 * @memberof LinkedStack
 */
void* jtk_LinkedStack_pop(jtk_LinkedStack_t* stack);

/**
 * @memberof LinkedStack
 */
void* jtk_LinkedStack_peek(jtk_LinkedStack_t* stack);

/**
 * @memberof LinkedStack
 */
bool jtk_LinkedStack_isEmpty(jtk_LinkedStack_t* stack);

/**
 * @memberof LinkedStack
 */
int32_t jtk_LinkedStack_getSize(jtk_LinkedStack_t* stack);

/**
 * @memberof LinkedStack
 */
void jtk_LinkedStack_addAll(jtk_LinkedStack_t* stack, jtk_CollectionType_t type, void* collection);

#endif /* JTK_COLLECTION_LINKED_STACK_H */