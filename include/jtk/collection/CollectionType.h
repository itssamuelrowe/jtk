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

// Saturday, February 24, 2018

#ifndef JTK_COLLECTION_COLLECTION_TYPE_H
#define JTK_COLLECTION_COLLECTION_TYPE_H

/**
 * @enum CollectionType
 * @ingroup jtk_collection
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
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