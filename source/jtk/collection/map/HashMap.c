/*
 * Copyright 2017-2020 Samuel Rowe
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// Saturday, February 24, 2018

#include <jtk/collection/array/Arrays.h>
#include <jtk/collection/map/HashMap.h>
#include <jtk/collection/map/HashMapEntryIterator.h>
#include <jtk/collection/map/HashMapKeyIterator.h>
#include <jtk/collection/map/HashMapValueIterator.h>
#include <jtk/core/Integer.h>
#include <jtk/core/Float.h>
#include <jtk/math/Math.h>

/*******************************************************************************
 * HashMap                                                                     *
 *******************************************************************************/

/* Hash */

static int32_t jtk_HashMap_hash(int32_t hashCode);

/* Index */

static int32_t jtk_HashMap_getIndex(int32_t hashCode, int32_t size);

/* Entry */

static void jtk_HashMap_addEntry(jtk_HashMap_t* map, int32_t index, void* key, void* value, int32_t hashCode);
static jtk_HashMapEntry_t* jtk_HashMap_getEntry(jtk_HashMap_t* map, void* key);

/* Resize */

static void jtk_HashMap_resize(jtk_HashMap_t* map, int32_t newCapacity);

/* Entry (private) */

void jtk_HashMap_addEntry(jtk_HashMap_t* map, int32_t index, void* key,
    void* value, int32_t hashCode) {
    jtk_HashMapEntry_t* oldEntry = map->m_table[index];
    jtk_HashMapEntry_t* newEntry = jtk_HashMapEntry_new(key, value, hashCode, oldEntry);
    map->m_table[index] = newEntry;
    map->m_size++;
    if (map->m_size >= map->m_threshold) {
        jtk_HashMap_resize(map, 2 * map->m_tableSize);
    }
}

jtk_HashMapEntry_t* jtk_HashMap_getEntry(jtk_HashMap_t* map, void* key) {
    int32_t objectHashCode = map->m_keyAdapter->hash(key);
    int32_t hashCode = jtk_HashMap_hash(objectHashCode);
    int32_t index = jtk_HashMap_getIndex(hashCode, map->m_tableSize);

    jtk_HashMapEntry_t* result = NULL;
    jtk_HashMapEntry_t* entry = map->m_table[index];
    while (entry != NULL) {
        void* key0 = entry->m_key;
        if ((entry->m_hashCode == hashCode) && map->m_keyAdapter->equals(key0, key)) {
            result = entry;
            break;
        }
        entry = entry->m_next;
    }
    return result;
}

/* Hash (private) */

int32_t jtk_HashMap_hash(int32_t hashCode) {
    hashCode ^= ((uint32_t)hashCode >> 20) ^ ((uint32_t)hashCode >> 12);
    return hashCode ^ ((uint32_t)hashCode >> 7) ^ ((uint32_t)hashCode >> 4);
}

/* Index (private)  */

int32_t jtk_HashMap_getIndex(int32_t code, int32_t size) {
    return code & (size - 1);
}

/* Resize (private) */

void jtk_HashMap_resize(jtk_HashMap_t* map, int32_t newCapacity) {
	jtk_HashMapEntry_t** oldTable = map->m_table;
	int32_t oldCapacity = map->m_tableSize;
	if (oldCapacity == JTK_HASH_MAP_MAX_CAPACITY) {
		map->m_threshold = JTK_INTEGER_MAX_VALUE;
	}
	else {
		jtk_HashMapEntry_t** newTable = jtk_Memory_allocate(jtk_HashMapEntry_t*, newCapacity);
        jtk_Arrays_fill_v((void**)newTable, newCapacity, NULL);

        int32_t i;
		for (i = 0; i < oldCapacity; i++) {
			jtk_HashMapEntry_t* entry = oldTable[i];
			if (entry != NULL) {
				do {
					jtk_HashMapEntry_t* next = entry->m_next;
					int32_t index = jtk_HashMap_getIndex(entry->m_hashCode, newCapacity);
					entry->m_next = newTable[index];
					newTable[index] = entry;
					entry = next;
				}
				while (entry != NULL);
			}
		}
		map->m_table = newTable;

        // fprintf(stderr, "[resize] HashMap: oldCapacity=%d, newCapacity=%d, size=%d\n", oldCapacity, newCapacity, map->m_size);

        map->m_tableSize = newCapacity;
		map->m_threshold = (int32_t)(newCapacity * map->m_loadFactor);
		jtk_Memory_deallocate(oldTable);
	}
}

/* Constructor */

jtk_HashMap_t* jtk_HashMap_new(jtk_ObjectAdapter_t* keyAdapter,
    jtk_ObjectAdapter_t* valueAdapter) {
    return jtk_HashMap_newEx(keyAdapter, valueAdapter, JTK_HASH_MAP_DEFAULT_CAPACITY, JTK_HASH_MAP_DEFAULT_LOAD_FACTOR);
}

jtk_HashMap_t* jtk_HashMap_newWithCapacity(jtk_ObjectAdapter_t* keyAdapter,
    jtk_ObjectAdapter_t* valueAdapter, int32_t capacity) {
    return jtk_HashMap_newEx(keyAdapter, valueAdapter, JTK_HASH_MAP_DEFAULT_CAPACITY, JTK_HASH_MAP_DEFAULT_LOAD_FACTOR);
}

jtk_HashMap_t* jtk_HashMap_newWithLoadFactor(jtk_ObjectAdapter_t* keyAdapter,
    jtk_ObjectAdapter_t* valueAdapter, float loadFactor) {
    return jtk_HashMap_newEx(keyAdapter, valueAdapter, JTK_HASH_MAP_DEFAULT_CAPACITY, loadFactor);
}

jtk_HashMap_t* jtk_HashMap_newEx(jtk_ObjectAdapter_t* keyAdapter,
    jtk_ObjectAdapter_t* valueAdapter, int32_t capacity, float loadFactor) {
    jtk_Assert_assertFalse(capacity < 0, "The specified capacity is invalid.");
    jtk_Assert_assertFalse(((loadFactor < 0.0f) || jtk_Float_isNaN(loadFactor)), "The specified load factor is invalid.");

	if (capacity > JTK_HASH_MAP_MAX_CAPACITY) {
		capacity = JTK_HASH_MAP_MAX_CAPACITY;
	}

    /* The specified capacity is always converted to the nearest power of
     * two.
     */
	int32_t capacity0 = jtk_Math_findPowerOfTwo(capacity);

    jtk_HashMap_t* map = jtk_Memory_allocate(jtk_HashMap_t, 1);
    map->m_keyAdapter = keyAdapter;
    map->m_valueAdapter = valueAdapter;
	map->m_loadFactor = loadFactor;
	map->m_threshold = (int32_t)(capacity0 * loadFactor);
	map->m_table = jtk_Memory_allocate(jtk_HashMapEntry_t*, capacity0);
    map->m_tableSize = capacity0;
    map->m_size = 0;

    /* Due to the inherent nature of C, the newly allocated array may contain
     * garbage value. The constructor explicitly sets each element to null.
     */
    jtk_Arrays_fill_v((void**)map->m_table, capacity0, NULL);

    return map;
}

/* Destructor */

void jtk_HashMap_delete(jtk_HashMap_t* map) {
    jtk_Assert_assertObject(map, "The specified map is null.");

    int32_t capacity = map->m_tableSize;
	for (int32_t i = 0; i < capacity; i++) {
		jtk_HashMapEntry_t* next;
        jtk_HashMapEntry_t* entry = map->m_table[i];
		while (entry != NULL) {
			next = entry->m_next;
			jtk_HashMapEntry_delete(entry);
            entry = next;
		}
	}
	jtk_Memory_deallocate(map->m_table);
    jtk_Memory_deallocate(map);
}

/* Clear */

void jtk_HashMap_clear(jtk_HashMap_t* map) {
    jtk_Assert_assertObject(map, "The specified map is null.");

    int32_t capacity = map->m_tableSize;
    int32_t i;
	for (i = 0; i < capacity; i++) {
		jtk_HashMapEntry_t* next;
        jtk_HashMapEntry_t* entry = map->m_table[i];
		while (entry != NULL) {
			next = entry->m_next;
			jtk_HashMapEntry_delete(entry);
            entry = next;
		}
		map->m_table[i] = NULL;
	}
	map->m_size = 0;
}

/* Clone */

jtk_HashMap_t* jtk_HashMap_clone(jtk_HashMap_t* map) {
    jtk_HashMap_t* result = jtk_HashMap_newEx(map->m_keyAdapter,
        map->m_valueAdapter, map->m_tableSize, map->m_loadFactor);

    int32_t capacity = map->m_tableSize;
    int32_t i;
    for (i = 0; i < capacity; i++) {
        jtk_HashMapEntry_t* entry = map->m_table[i];
        while (entry != NULL) {
            /* Theoretically, the specified map should always contain unique
             * values. Therefore, jtk_HashMap_put() and jtk_HashMap_putStrictly()
             * should result in the same behaviour.
             */
            jtk_HashMap_putStrictly(map, entry->m_key, entry->m_value);
            entry = entry->m_next;
        }
    }

    return result;
}

/* Contains */

bool jtk_HashMap_containsKey(jtk_HashMap_t* map, void* key) {
    jtk_Assert_assertObject(map, "The specified map is null.");

    return jtk_HashMap_getEntry(map, key) != NULL;
}

bool jtk_HashMap_containsValue(jtk_HashMap_t* map, void* value) {
    jtk_Assert_assertObject(map, "The specified map is null.");

	int32_t capacity = map->m_tableSize;
    int32_t i;
	for (i = 0; i < capacity; i++) {
        jtk_HashMapEntry_t* entry = map->m_table[i];
		while (entry != NULL) {
            /* If a value adapter is attached to the hash map, apply it.
             * Otherwise, fallback to the equality operator.
             */
			if (((map->m_valueAdapter != NULL) && map->m_valueAdapter->equals(value, entry->m_value)) ||
                (entry->m_value == value)) {
				return true;
			}
            entry = entry->m_next;
		}
	}
	return false;
}

/* Empty */

bool jtk_HashMap_isEmpty(jtk_HashMap_t* map) {
    jtk_Assert_assertObject(map, "The specified map is null.");

    return map->m_size == 0;
}

/* Iterator */

jtk_Iterator_t* jtk_HashMap_getEntryIterator(jtk_HashMap_t* map) {
    jtk_Assert_assertObject(map, "The specified map is null.");

    jtk_HashMapEntryIterator_t* iterator = jtk_HashMapEntryIterator_new(map);
    return jtk_HashMapEntryIterator_getIterator(iterator);
}

jtk_Iterator_t* jtk_HashMap_getKeyIterator(jtk_HashMap_t* map) {
    jtk_Assert_assertObject(map, "The specified map is null.");

    jtk_HashMapKeyIterator_t* iterator = jtk_HashMapKeyIterator_new(map);
    return jtk_HashMapKeyIterator_getIterator(iterator);
}

jtk_Iterator_t* jtk_HashMap_getValueIterator(jtk_HashMap_t* map) {
    jtk_Assert_assertObject(map, "The specified map is null.");

    jtk_HashMapValueIterator_t* iterator = jtk_HashMapValueIterator_new(map);
    return jtk_HashMapValueIterator_getIterator(iterator);
}

/* Put */

bool jtk_HashMap_put(jtk_HashMap_t* map, void* key, void* value) {
    jtk_Assert_assertObject(map, "The specified map is null.");

    int32_t objectHashCode = map->m_keyAdapter->hash(key);
	int32_t hashCode = jtk_HashMap_hash(objectHashCode);
	int32_t index = jtk_HashMap_getIndex(hashCode, map->m_tableSize);

	jtk_HashMapEntry_t* entry = map->m_table[index];
	while (entry != NULL) {
		void* key0 = entry->m_key;
		if ((entry->m_hashCode == hashCode) && map->m_keyAdapter->equals(key0, key)) {
			break;
		}
        entry = entry->m_next;
	}

    bool result = entry != NULL;
	if (result) {
		entry->m_value = value;
	}
    else {
        jtk_HashMap_addEntry(map, index, key, value, hashCode);
    }

    return !result;
}

bool jtk_HashMap_putStrictly(jtk_HashMap_t* map, void* key, void* value) {
    jtk_Assert_assertObject(map, "The specified map is null.");

    int32_t objectHashCode = map->m_keyAdapter->hash(key);
    int32_t hashCode = jtk_HashMap_hash(objectHashCode);
    int32_t index = jtk_HashMap_getIndex(hashCode, map->m_tableSize);

    jtk_HashMapEntry_t* entry = map->m_table[index];
    while (entry != NULL) {
        void* key0 = entry->m_key;
        if ((entry->m_hashCode == hashCode) && map->m_keyAdapter->equals(key0, key)) {
            break;
        }
        entry = entry->m_next;
    }

    bool result = false;
    if (entry == NULL) {
        jtk_HashMap_addEntry(map, index, key, value, hashCode);
        result = true;
    }
    return result;
}

/* Remove */

bool jtk_HashMap_removeKey(jtk_HashMap_t* map, void* key) {
    jtk_Assert_assertObject(map, "The specified map is null.");

    bool result = false;
    int32_t objectHashCode = map->m_keyAdapter->hash(key);
    int32_t hashCode = jtk_HashMap_hash(objectHashCode);
	int32_t index = jtk_HashMap_getIndex(hashCode, map->m_tableSize);

	jtk_HashMapEntry_t* previous = map->m_table[index];
    jtk_HashMapEntry_t* entry = map->m_table[index];
	while (entry != NULL) {
        jtk_HashMapEntry_t* next = entry->m_next;
		void* key0 = entry->m_key;
		if ((entry->m_hashCode == hashCode) && map->m_keyAdapter->equals(key, key0)) {
			/* We have discovered the target node. */
			if (previous == entry) {
				/* If entry is the first node, make the next node as the
				 * head.
				 */
				map->m_table[index] = next;
			}
			else {
				/* Entry is not the first node, make the previous node skip
				 * this node.
				 */
				previous->m_next = next;
			}
			map->m_size--;

			result = true;
            break;
		}
        previous = entry;
        entry = next;
	}
	return result;
}

/* Size */

int32_t jtk_HashMap_getSize(jtk_HashMap_t* map) {
    jtk_Assert_assertObject(map, "The specified map is null.");

    return map->m_size;
}

void* jtk_HashMap_getValue(jtk_HashMap_t* map, void* key) {
    jtk_Assert_assertObject(map, "The specified map is null.");

	jtk_HashMapEntry_t* entry = jtk_HashMap_getEntry(map, key);
    return (entry == NULL)? NULL : entry->m_value;
}

void* jtk_HashMap_getValueEx(jtk_HashMap_t* map, void* key, bool* contains,
    void* defaultValue) {
    jtk_Assert_assertObject(map, "The specified map is null.");


    /* In the jtk_HashMap_getValue() function, the default value is assumed
     * as NULL. Here, the library assumes whatever default value the user
     * specified.
     */
    void* result = defaultValue;

    /* Retreive the entry from the internal array of buckets. Check if a
     * corresponding entry was found in the buckets.
     */
    jtk_HashMapEntry_t* entry = jtk_HashMap_getEntry(map, key);
    *contains = (entry != NULL);
	if (*contains) {
		result = entry->m_value;
	}

    /* Return the value, if any. */
    return result;
}

bool jtk_HashMap_setValue(jtk_HashMap_t* map, void* key, void* value) {
    jtk_Assert_assertObject(map, "The specified map is null.");

	jtk_HashMapEntry_t* entry = jtk_HashMap_getEntry(map, key);
	bool result = false;
    if (entry != NULL) {
		entry->m_value = value;
		result = true;
	}
    return result;
}

bool jtk_HashMap_setValueEx(jtk_HashMap_t* map, void* key, void* value,
    void** previous) {
    jtk_Assert_assertObject(map, "The specified map is null.");

	jtk_HashMapEntry_t* entry = jtk_HashMap_getEntry(map, key);
	bool result = false;
    if (entry != NULL) {
        *previous = entry->m_value;
		entry->m_value = value;
		result = true;
	}
    return result;
}