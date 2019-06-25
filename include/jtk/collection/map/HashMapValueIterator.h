/*
 * Copyright 2018-2019 OneCube
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

// Thursday, ‎July ‎12, ‎2018

#ifndef JTK_COLLECTION_HASH_MAP_VALUE_ITERATOR_H
#define JTK_COLLECTION_HASH_MAP_VALUE_ITERATOR_H

#include <jtk/Configuration.h>
#include <jtk/collection/map/HashMapEntryIterator.h>

/*******************************************************************************
 * HashMapValueIterator                                                          *
 *******************************************************************************/

/**
 * @class HashMapValueIterator
 * @ingroup jtk_collection_map
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.0
 */
struct jtk_HashMapValueIterator_t {
    jtk_HashMapEntryIterator_t* m_entryIterator;
    jtk_Iterator_t* m_iterator;
};

/**
 * @memberof HashMapValueIterator
 */
typedef struct jtk_HashMapValueIterator_t jtk_HashMapValueIterator_t;

/* Constructor */

/**
 * @memberof HashMapValueIterator
 */
jtk_HashMapValueIterator_t* jtk_HashMapValueIterator_new(jtk_HashMap_t* map);

/* Destructor */

/**
 * @memberof HashMapValueIterator
 */
void jtk_HashMapValueIterator_delete(jtk_HashMapValueIterator_t* iterator);

/* Destroy */

/**
 * @private
 * @memberof HashMapValueIterator
 */
void jtk_HashMapValueIterator_destroy(jtk_HashMapValueIterator_t* iterator);

/* Iterator */

/**
 * @memberof HashMapValueIterator
 */
jtk_Iterator_t* jtk_HashMapValueIterator_getIterator(jtk_HashMapValueIterator_t* iterator);

/* Next */

/**
 * @memberof HashMapValueIterator
 */
bool jtk_HashMapValueIterator_hasNext(jtk_HashMapValueIterator_t* iterator);

/**
 * @memberof HashMapValueIterator
 */
void* jtk_HashMapValueIterator_getNext(jtk_HashMapValueIterator_t* iterator);

#endif /* JTK_COLLECTION_HASH_MAP_VALUE_ITERATOR_H */