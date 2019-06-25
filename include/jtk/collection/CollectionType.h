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