/*
 *                              Jez Toolkit (JTK)
 *     Copyright (C) 2018 OneCube Software Solutions. All rights reserved.
 *
 * This file is part of Jez Toolkit Free Edition, version 1.0.
 *
 * See the file "LICENSE" included in the distribution for the terms and conditions,
 * or visit http://www.onecube.in/jtk/free-license.
 *
 * IMPORTANT NOTE: You may NOT copy the content of this file, either partially
 * or fully, into your source code.
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
 * @author Samuel Rowe
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