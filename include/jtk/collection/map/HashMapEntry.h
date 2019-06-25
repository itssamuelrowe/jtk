// Friday, June 08, 2018

#ifndef JTK_COLLECTION_MAP_HASH_MAP_ENTRY_H
#define JTK_COLLECTION_MAP_HASH_MAP_ENTRY_H

#include <jtk/Configuration.h>

/*******************************************************************************
 * HashMapEntry                                                                *
 *******************************************************************************/

typedef struct jtk_HashMapEntry_t jtk_HashMapEntry_t;

/**
 * @class HashMapEntry
 * @ingroup jtk_collection_map
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.0
 */
struct jtk_HashMapEntry_t {
    /**
     * "Open says-ah me!" You got it right. This is the key to the entry.
     */
    void* m_key;

    /**
     * The payload, or user data, or element, or value, whatever you want
     * to call.
     */
    void* m_value;

    /**
     * The hash code corresponding to the key.
     */
    int32_t m_hashCode;

    /**
     * The jtk_HashMap_t implementation stores all the buckets in an array of
     * singly-linked lists, internally. This field points to the next entry
     * in the list of buckets.
     */
    jtk_HashMapEntry_t* m_next;
};

typedef struct jtk_HashMapEntry_t jtk_HashMapEntry_t;

/**
 * @memberof HashMapEntry
 */
jtk_HashMapEntry_t* jtk_HashMapEntry_new(void* key, void* value, int32_t hashCode, jtk_HashMapEntry_t* next);

/**
 * @memberof HashMapEntry
 */
void jtk_HashMapEntry_delete(jtk_HashMapEntry_t* entry);

// Hash Code

/**
 * @since JTK 1.1
 */
int32_t jtk_HashMapEntry_getHashCode(jtk_HashMapEntry_t* entry);

// Key

/**
 * @since JTK 1.1
 */
void* jtk_HashMapEntry_getKey(jtk_HashMapEntry_t* entry);

// Value

/**
 * @since JTK 1.1
 */
void* jtk_HashMapEntry_getValue(jtk_HashMapEntry_t* entry);

#endif /* JTK_COLLECTION_MAP_HASH_MAP_ENTRY_H */