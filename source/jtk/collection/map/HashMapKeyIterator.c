// Monday, July 23, 2018

#include <jtk/collection/map/HashMapKeyIterator.h>

/*******************************************************************************
 * HashMapKeyIterator                                                          *
 *******************************************************************************/

/* Constructor */

jtk_HashMapKeyIterator_t* jtk_HashMapKeyIterator_new(jtk_HashMap_t* map) {
    jtk_HashMapKeyIterator_t* keyIterator = jtk_Memory_allocate(jtk_HashMapKeyIterator_t, 1);

    jtk_Iterator_t* iterator = jtk_Iterator_new();
    iterator->m_destroy = (jtk_Iterator_DestroyFunction_t)jtk_HashMapKeyIterator_destroy;
    iterator->m_getNext = (jtk_Iterator_GetNextFunction_t)jtk_HashMapKeyIterator_getNext;
    iterator->m_hasNext = (jtk_Iterator_HasNextFunction_t)jtk_HashMapKeyIterator_hasNext;
    iterator->m_bundle = keyIterator;
    
    keyIterator->m_entryIterator = jtk_HashMapEntryIterator_new(map);
    keyIterator->m_iterator = iterator;

    return keyIterator;
}

/* Destructor */

void jtk_HashMapKeyIterator_delete(jtk_HashMapKeyIterator_t* iterator) {
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");
    
    if (iterator->m_iterator != NULL) {
        iterator->m_iterator->m_destroy = NULL;
        jtk_Iterator_delete(iterator->m_iterator);
    }
    jtk_HashMapEntryIterator_delete(iterator->m_entryIterator);
    jtk_Memory_deallocate(iterator);
}

/* Destroy */

void jtk_HashMapKeyIterator_destroy(jtk_HashMapKeyIterator_t* iterator) {
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");
    
    iterator->m_iterator = NULL;
    jtk_HashMapKeyIterator_delete(iterator);
}

/* Iterator */

jtk_Iterator_t* jtk_HashMapKeyIterator_getIterator(jtk_HashMapKeyIterator_t* iterator) {
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");

    return iterator->m_iterator;
}

/* Next */

bool jtk_HashMapKeyIterator_hasNext(jtk_HashMapKeyIterator_t* iterator) {
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");

    return jtk_HashMapEntryIterator_hasNext(iterator->m_entryIterator);
}

void* jtk_HashMapKeyIterator_getNext(jtk_HashMapKeyIterator_t* iterator) {
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");

    jtk_HashMapEntry_t* entry = (jtk_HashMapEntry_t*)jtk_HashMapEntryIterator_getNext(iterator->m_entryIterator);
    return entry->m_key;
}