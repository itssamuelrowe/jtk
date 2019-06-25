// Monday, July 23, 2018

#include <jtk/collection/map/HashMapEntryIterator.h>

/*******************************************************************************
 * HashMapEntryIterator                                                        *
 *******************************************************************************/

/* Constructor */

jtk_HashMapEntryIterator_t* jtk_HashMapEntryIterator_new(jtk_HashMap_t* map) {
    jtk_HashMapEntryIterator_t* hashMapEntryIterator = jtk_Memory_allocate(jtk_HashMapEntryIterator_t, 1);
    
    jtk_Iterator_t* iterator = jtk_Iterator_new();
    iterator->m_destroy = (jtk_Iterator_DestroyFunction_t)jtk_HashMapEntryIterator_destroy;
    iterator->m_getNext = (jtk_Iterator_GetNextFunction_t)jtk_HashMapEntryIterator_getNext;
    iterator->m_hasNext = (jtk_Iterator_HasNextFunction_t)jtk_HashMapEntryIterator_hasNext;
    iterator->m_bundle = hashMapEntryIterator;
    
    int32_t index = 0;
    jtk_HashMapEntry_t* next = NULL;
    
    if (map->m_size > 0) {
        do {
            next = map->m_table[index++];
        }
        while ((index < map->m_tableSize) && (next == NULL));
    }
    
    hashMapEntryIterator->m_map = map;
    hashMapEntryIterator->m_iterator = iterator;
    hashMapEntryIterator->m_index = index;
    hashMapEntryIterator->m_next = next;
}

/* Destructor */

void jtk_HashMapEntryIterator_delete(jtk_HashMapEntryIterator_t* iterator) {
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");
    
    if (iterator->m_iterator != NULL) {
        iterator->m_iterator->m_destroy = NULL;
        jtk_Iterator_delete(iterator->m_iterator);
    }
    jtk_Memory_deallocate(iterator);
}

/* Destroy */

void jtk_HashMapEntryIterator_destroy(jtk_HashMapEntryIterator_t* iterator) {
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");
    
    iterator->m_iterator = NULL;
    jtk_HashMapEntryIterator_delete(iterator);
}

/* Iterator */

jtk_Iterator_t* jtk_HashMapEntryIterator_getIterator(jtk_HashMapEntryIterator_t* iterator) {
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");
    
    return iterator->m_iterator;
}

/* Next */

bool jtk_HashMapEntryIterator_hasNext(jtk_HashMapEntryIterator_t* iterator) {
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");
    
    return iterator->m_next != NULL;
}

void* jtk_HashMapEntryIterator_getNext(jtk_HashMapEntryIterator_t* iterator) {
    jtk_Assert_assertObject(iterator, "The specified iterator is null.");
    jtk_Assert_assertTrue(jtk_ArrayListIterator_hasNext(iterator), "The specified iterator is empty.");

    jtk_HashMapEntry_t* entry = iterator->m_next;
    iterator->m_next = entry->m_next;
    if (iterator->m_next == NULL) {
        do {
            iterator->m_next = iterator->m_map->m_table[iterator->m_index++];
        }
        while ((iterator->m_index < iterator->m_map->m_tableSize) &&
            (iterator->m_next == NULL));
    }
    return entry;
}
