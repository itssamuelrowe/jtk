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

// Sunday, November 26, 2017

#ifndef JTK_COLLECTION_HASH_MAP_H
#define JTK_COLLECTION_HASH_MAP_H

#include <jtk/core/ObjectAdapter.h>
#include <jtk/collection/map/HashMapEntry.h>
#include <jtk/collection/Iterator.h>

/*******************************************************************************
 * HashMap                                                                     *
 *******************************************************************************/

/**
 * The default capacity of the internal table.
 *
 * @class HashMap
 */
#define JTK_HASH_MAP_DEFAULT_CAPACITY 16

/**
 * The capacity after which the internal table stops growing.
 *
 * @class HashMap
 */
#define JTK_HASH_MAP_MAX_CAPACITY (1 << 30)

/**
 * The default load factor of the internal table.
 *
 * @class HashMap
 */
#define JTK_HASH_MAP_DEFAULT_LOAD_FACTOR 0.75f

/**
 * The HashMap class represents a map backed by an hash table. Internally,
 * all the key-value pairs are stored as entries in an array of buckets. The
 * array grows and shrinks as needed. As of this version, no interface is
 * provided to extract a reference to the internal array. Although, an interface
 * to manipulate the threshold and load factor is provided.
 *
 * As of this version, an object adapter to adapt keys is a requirement. Although,
 * an object adapter to adapt values is optional. Custom implementations of
 * algorithms for converting elements to strings, computing hashes, etc. may
 * be provided. If an object adapter is absent, the implementation fails (to be
 * precise, results are undefined). This behaviour may change in the future
 * releases.
 *
 * Both the adapters should be passed to the constructor. Changing the adapters
 * after emplacing entries may result in inconsistent distribution. Although
 * the entries may be redistributed after changing the adapters, the implementation
 * does not support this. And we do not plan to introduce it in the future. We
 * intend to keep the interface simple and avoid complications. In case of
 * absolute requirement, we recommend employing another map where the elements
 * can be redistributed.
 *
 * The HashMap class is intended to be used by a single thread. It does not
 * implement a thread synchronization policy. In other words, it is not thread
 * safe. Concurrent invocation of a function against an instance without an
 * external synchronization results in undefined behaviour.
 *
 * Further, it is recommended that the user avoids accessing the fields of
 * this structure directly. They may be subjected to changes without any
 * notifications. Please employ appropriate interfaces with detailed
 * documentation.
 *
 * @class HashMap
 * @ingroup jtk_collection_map
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.0
 */
struct jtk_HashMap_t {

    /**
     * The adapter used to adapt keys as objects.
     */
    jtk_ObjectAdapter_t* m_keyAdapter;

    /**
     * The adapter used to adapt values as objects.
     */
    jtk_ObjectAdapter_t* m_valueAdapter;

	/**
	 * The slots, resized when necessary. The size of the table is always a
     * power of two.
	 */
    jtk_HashMapEntry_t** m_table;
    int32_t m_tableSize;

    /**
     * The total number of mappings.
     */
    int32_t m_size;

    /**
     * The threshold size after which the internal table of this map grows.
     */
    int32_t m_threshold;

    /**
     * The load factor of the mappings.
     */
    float m_loadFactor;
};

typedef struct jtk_HashMap_t jtk_HashMap_t;

/* Constructor */

/**
 * Creates an empty HashMap with default initial capacity and load factor.
 *
 * @param  keyAdapter
 *         The adapter used to adapt keys as objects.
 * @param  valueAdapter
 *         The adapter used to adapt values as objects.
 * @return A newly created hash map with default initial capacity and load
 *         factor. The user is responsible for destroying the hash map.
 * @memberof HashMap
 */
jtk_HashMap_t* jtk_HashMap_new(jtk_ObjectAdapter_t* keyAdapter, jtk_ObjectAdapter_t* valueAdapter);

/**
 * Creates an empty HashMap with the specified initial capacity and default load
 * factor.
 *
 * @param  keyAdapter
 *         The adapter used to adapt keys as objects.
 * @param  valueAdapter
 *         The adapter used to adapt values as objects.
 * @param  capacity
 *		   This argument specifies the initial capacity.
 * @return A newly created hash map with the specified initial capacity and
 *         the default load factor. The user is responsible for destroying the
 *         hash map.
 * @memberof HashMap
 */
jtk_HashMap_t* jtk_HashMap_newWithCapacity(jtk_ObjectAdapter_t* keyAdapter, jtk_ObjectAdapter_t* valueAdapter, int32_t capacity);

/**
 * Creates an empty HashMap with the default initial capacity and specified load
 * factor.
 *
 * @param  keyAdapter
 *         The adapter used to adapt keys as objects.
 * @param  valueAdapter
 *         The adapter used to adapt values as objects.
 * @param  loadFactor
 *		   This argument specifies the load factor.
 * @return A newly created hash map with the default initial capacity and
 *         the specified load factor. The user is responsible for destroying the
 *         hash map.
 * @memberof HashMap
 */
jtk_HashMap_t* jtk_HashMap_newWithLoadFactor(jtk_ObjectAdapter_t* keyAdapter, jtk_ObjectAdapter_t* valueAdapter, float loadFactor);

/**
 * Creates an empty HashMap with the specified initial capacity and load
 * factor.
 *
 * @param  keyAdapter
 *         The adapter used to adapt keys as objects.
 * @param  valueAdapter
 *         The adapter used to adapt values as objects.
 * @param  capacity
 *		   This argument specifies the initial capacity.
 * @param  loadFactor
 *		   This argument specifies the load factor.
 * @return A newly created hash map with the specified initial capacity and load
 *         factor. The user is responsible for destroying the hash map.
 * @memberof HashMap
 */
jtk_HashMap_t* jtk_HashMap_newEx(jtk_ObjectAdapter_t* keyAdapter, jtk_ObjectAdapter_t* valueAdapter, int32_t capacity, float loadFactor);

/* Destructor */

/**
 * Destroys the specified hash map.
 *
 * @param  map
 *         The hash map to destroy.
 * @memberof HashMap
 */
void jtk_HashMap_delete(jtk_HashMap_t* map);

/* Clear */

/**
 * The clear() function removes all the key-value pairs from this hash map.
 *
 * @param  map
 *         This argument specifies the hash map to clear.
 * @memberof HashMap
 */
void jtk_HashMap_clear(jtk_HashMap_t* map);

/* Clone */

/**
 * @memberof HashMap
 */
jtk_HashMap_t* jtk_HashMap_clone(jtk_HashMap_t* map);

/* Contains */

/**
 * Determines whether the specified value is mapped to by one or more keys.
 *
 * @param  map
 *         This argument specifies the map.
 * @param  value
 *		   This argument specifies the value to test.
 * @return `true` if this map maps one or more keys to the specified
 *		   value; `false` otherwise.
 * @memberof HashMap
 */
bool jtk_HashMap_containsValue(jtk_HashMap_t* map, void* value);

/**
 * @memberof HashMap
 */
bool jtk_HashMap_containsKey(jtk_HashMap_t* map, void* key);

/* Empty */

/**
 * Determines whether the specified map contains mappings, or not.
 *
 * @param  map
 *         This argument specifies the hash map to test.
 * @return `true` if the specified map contains no mappings; `false`
 *		   otherwise.
 * @memberof HashMap
 */
bool jtk_HashMap_isEmpty(jtk_HashMap_t* map);

/* Iterator */

/**
 * @memberof HashMap
 */
jtk_Iterator_t* jtk_HashMap_getEntryIterator(jtk_HashMap_t* map);

/**
 * @memberof HashMap
 */
jtk_Iterator_t* jtk_HashMap_getKeyIterator(jtk_HashMap_t* map);

/**
 * @memberof HashMap
 */
jtk_Iterator_t* jtk_HashMap_getValueIterator(jtk_HashMap_t* map);

/* Put */

/**
 * Associates the specified value with the speciifed key. If the map
 * previously contained a mapping for the key, the old value is updated.
 *
 * @param  map
 *         This argument specifies the hash map to modify.
 * @param  key
 *		   This argument specifies the key.
 * @param  value
 *		   This argument specifies the value.
 * @return `true` if a new mapping was created; `false`
 *		   otherwise.
 * @memberof HashMap
 */
bool jtk_HashMap_put(jtk_HashMap_t* map, void* key, void* value);

/**
 * Associates the specified value with the speciifed key. If the map
 * previously contained a mapping for the key, the function terminates.
 *
 * @param  map
 *         This argument specifies the hash map to modify.
 * @param  key
 *         The key to map.
 * @param  value
 *         The value to map.
 * @return `true` if the mapping was successfully created;
 *         `false` otherwise.
 * @memberof HashMap
 */
bool jtk_HashMap_putStrictly(jtk_HashMap_t* map, void* key, void* value);

/* Remove */

/**
 * Removes the mapping for the specified key from this map if it exists.
 *
 * @param  map
 *         This argument specifies the hash map to modify.
 * @param  key
 *		   This argument specifies the key to remove.
 * @return `true` if the specified key was successfully removed;
 *         `false` otherwise.
 * @memberof HashMap
 */
bool jtk_HashMap_removeKey(jtk_HashMap_t* map, void* key);

/* Size */

/**
 * Returns the number of mappings in the specified map.
 *
 * @param  map
 *         This argument specifies the hash map to test.
 * @return The number of mappings in this map.
 * @memberof HashMap
 */
int32_t jtk_HashMap_getSize(jtk_HashMap_t* map);

/* Value */

/**
 * Returns the value to which the specified key is mapped, if any; otherwise,
 * null.
 *
 * @param  map
 *         This argument specifies the hash map.
 * @param  key
 *         The key that maps to the value.
 * @return The value to which the specified key is mapped, if any; `null`
 *         otherwise.
 * @memberof HashMap
 */
void* jtk_HashMap_getValue(jtk_HashMap_t* map, void* key);

void* jtk_HashMap_getValueFast(jtk_HashMap_t* map, void* key, int32_t* hashCode);

/**
 * Returns the value to which the specified key is mapped, if any. Otherwise,
 * this function returns the specified default value.
 *
 * @param  map
 *         This argument specifies the hash map.
 * @param  key
 *         The key that maps to the value.
 * @param  contains
 *         A pointer to an integer. It is set to `true`, if a mapping
 *         was found; `false` otherwise.
 * @param  defaultValue
 *         The value which is returned if no mapping exists.
 * @return The value to which the specified key is mapped, if any; otherwise
 *         the specified default value is returned.
 * @memberof HashMap
 */
void* jtk_HashMap_getValueEx(jtk_HashMap_t* map, void* key, bool* contains, void* defaultValue);

/**
 * Updates the value associated with the specified key.
 *
 * @param  map
 *         This argument specifies the hash map.
 * @param  key
 *         This argument specifies the key.
 * @param  value
 *         This argument specifies the new value.
 * @return `true` if a mapping was updated; `false` otherwise.
 * @memberof HashMap
 */
bool jtk_HashMap_setValue(jtk_HashMap_t* map, void* key, void* value);

/**
 * Updates the value associated with the specified key. Further, it retrieves
 * the previous was associated with the key.
 *
 * @param  map
 *         This argument specifies the hash map.
 * @param  key
 *         This argument specifies the key.
 * @param  value
 *         This argument specifies the new value.
 * @param  previousValue
 *         This argument is set to the previous value, if any; `null`
 *         otherwise.
 * @return `true` if a mapping was updated; `false` otherwise.
 * @memberof HashMap
 */
bool jtk_HashMap_setValueEx(jtk_HashMap_t* map, void* key, void* value, void** previousValue);

#endif /* JTK_COLLECTION_HASH_MAP_H */