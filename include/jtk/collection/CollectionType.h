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

// Saturday, February 24, 2018

#ifndef JTK_COLLECTION_COLLECTION_TYPE_H
#define JTK_COLLECTION_COLLECTION_TYPE_H

/**
 * @enum CollectionType
 * @ingroup jtk_collection
 * @author Samuel Rowe
 * @since JTK 1.0
 */
enum jtk_CollectionType_t {
    JTK_COLLECTION_ARRAY_LIST,
    JTK_COLLECTION_DOUBLY_LINKED_LIST,
    JTK_COLLECTION_LINKED_STACK,
    JTK_COLLECTION_ARRAY_STACK,
    JTK_COLLECTION_LINKED_QUEUE,
    JTK_COLLECTION_ARRAY_QUEUE,
    JTK_COLLECTION_HASH_MAP,
    JTK_COLLECTION_HASH_SET,
    JTK_COLLECTION_HASH_BAG
};

/**
 * @memberof CollectionType
 */
typedef enum jtk_CollectionType_t jtk_CollectionType_t;

#endif /* JTK_COLLECTION_COLLECTION_TYPE_H */