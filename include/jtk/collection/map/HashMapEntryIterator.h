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

// Monday, July 23, 2018

#ifndef JTK_COLLECTION_MAP_HASH_MAP_ENTRY_ITERATOR_H
#define JTK_COLLECTION_MAP_HASH_MAP_ENTRY_ITERATOR_H

#include <jtk/Configuration.h>
#include <jtk/collection/map/HashMap.h>

/*******************************************************************************
 * HashMapEntryIterator                                                        *
 *******************************************************************************/

/**
 * @class HashMapEntryIterator
 * @ingroup jtk_collection_map
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.0
 */
struct jtk_HashMapEntryIterator_t {

    /**
     * The hash map from which the entries are extracted.
     */
    jtk_HashMap_t* m_map;

    /**
     * The iterator associated with this source iterator.
     */
    jtk_Iterator_t* m_iterator;

    int32_t m_index;
    jtk_HashMapEntry_t* m_next;
};

/**
 * @memberof HashMapEntryIterator
 */
typedef struct jtk_HashMapEntryIterator_t jtk_HashMapEntryIterator_t;

/* Constructor */

/**
 * @memberof HashMapEntryIterator
 */
jtk_HashMapEntryIterator_t* jtk_HashMapEntryIterator_new(jtk_HashMap_t* map);

/* Destructor */

/**
 * @memberof HashMapEntryIterator
 */
void jtk_HashMapEntryIterator_delete(jtk_HashMapEntryIterator_t* iterator);

/* Destroy */

/**
 * @private
 * @memberof HashMapEntryIterator
 */
void jtk_HashMapEntryIterator_destroy(jtk_HashMapEntryIterator_t* iterator);

/* Iterator */

/**
 * @memberof HashMapEntryIterator
 */
jtk_Iterator_t* jtk_HashMapEntryIterator_getIterator(jtk_HashMapEntryIterator_t* iterator);

/* Next */

/**
 * @memberof HashMapEntryIterator
 */
bool jtk_HashMapEntryIterator_hasNext(jtk_HashMapEntryIterator_t* iterator);

/**
 * @memberof HashMapEntryIterator
 */
void* jtk_HashMapEntryIterator_getNext(jtk_HashMapEntryIterator_t* iterator);

#endif /* JTK_COLLECTION_MAP_HASH_MAP_ENTRY_ITERATOR_H */