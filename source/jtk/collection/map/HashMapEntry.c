// Friday, June 08, 2018

#include <jtk/collection/map/HashMapEntry.h>

/*******************************************************************************
 * HashMapEntry                                                                *
 *******************************************************************************/

// Constructor

jtk_HashMapEntry_t* jtk_HashMapEntry_new(void* key, void* value,
    int32_t hashCode, jtk_HashMapEntry_t* next) {
    jtk_HashMapEntry_t* entry = jtk_Memory_allocate(jtk_HashMapEntry_t, 1);
    entry->m_key = key;
    entry->m_value = value;
    entry->m_hashCode = hashCode;
    entry->m_next = next;
    return entry;
}

// Destructor

void jtk_HashMapEntry_delete(jtk_HashMapEntry_t* entry) {
    jtk_Assert_assertObject(entry, "The specified entry is null.");

    jtk_Memory_deallocate(entry);
}

// Hash Code

int32_t jtk_HashMapEntry_getHashCode(jtk_HashMapEntry_t* entry) {
    jtk_Assert_assertObject(entry, "The specified entry is null.");
    
    return entry->m_hashCode;
}

// Key

void* jtk_HashMapEntry_getKey(jtk_HashMapEntry_t* entry) {
    jtk_Assert_assertObject(entry, "The specified entry is null.");
    
    return entry->m_key;
}

// Value

void* jtk_HashMapEntry_getValue(jtk_HashMapEntry_t* entry) {
    jtk_Assert_assertObject(entry, "The specified entry is null.");
    
    return entry->m_value;
}