// Friday, June 08, 2018

#ifndef JTK_COLLECTION_BAG_HASH_BAG_H
#define JTK_COLLECTION_BAG_HASH_BAG_H

/*******************************************************************************
 * HashBag                                                                     *
 *******************************************************************************/

/**
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.0
 */
struct jtk_HashBag_t {

    /**
     * The internal map that associates the elements with their corresponding
     * counts.
     */
    jtk_HashMap_t* m_map;

    /**
     * The total number of elements contained in this bag, including copies.
     */
    int32_t m_size;
};

typedef struct jtk_HashBag_t jtk_HashBag_t;

/* Constructor */

jtk_HashBag_t* jtk_HashBag_new(jtk_ObjectAdapter_t* elementAdapter);

/* Destructor */

void jtk_HashBag_delete(jtk_HashBag_t* bag);

/* Add */

void jtk_HashBag_add(jtk_HashBag_t* bag, void* element);
void jtk_HashBag_addAll(jtk_HashBag_t* bag, jtk_CollectionType_t type, void* collection);
void jtk_HashBag_addAllFromIterator(jtk_HashBag_t* bag, jtk_Iterator_t* iterator);
void jtk_HashBag_addCopies(jtk_HashBag_t* bag, void* element, int32_t copies);

/* Add Predicatively */

void jtk_HashBag_addPredicatively(jtk_HashBag_t* bag, void* element, jtk_PredicateFunction_t predicate);
void jtk_HashBag_addAllPredicatively(jtk_HashBag_t* bag, jtk_CollectionType_t type, void* collection, jtk_PredicateFunction_t predicate);
void jtk_HashBag_addAllFromIteratorPredicatively(jtk_HashBag_t* bag, jtk_Iterator_t* iterator, jtk_PredicateFunction_t predicate);
void jtk_HashBag_addCopiesPredicatively(jtk_HashBag_t* bag, void* element, int32_t copies, jtk_PredicateFunction_t predicate);

/* Copy to Array */

void jtk_HashBag_copyToArray(jtk_HashBag_t* bag, jtk_Array_t* array);

/* Copy to Array Extended */

jtk_HashBag_copyToArrayEx(jtk_HashBag_t* bag, jtk_Array_t* array, int32_t index);

/* Contains */

bool jtk_HashBag_contains(jtk_HashBag_t* bag, void* element);
bool jtk_HashBag_containsAll(jtk_HashBag_t* bag, jtk_CollectionType_t type, void* collection);
bool jtk_HashBag_containsAllFromIterator(jtk_HashBag_t* bag, jtk_Iterator_t* iterator);

/* Count */

int32_t jtk_HashBag_getCount(jtk_HashBag_t* bag, void* element);

/* Empty */

bool jtk_HashBag_isEmpty(jtk_HashBag_t* bag);

/* Equals */

bool jtk_HashBag_equals(jtk_HashBag_t* bag, jtk_HashBag_t* other);

/* HashBag-to-Array */

jtk_Array_t* jtk_HashBag_toArray(jtk_HashBag_t* bag);

/* HashBag-to-Map */

jtk_HashMap_t* jtk_HashBag_toMap(jtk_HashBag_t* bag);

/* HashBag-To-String */

uint8_t* jtk_HashBag_toString(jtk_HashBag_t* bag);

void jtk_HashBag_toStringEx(jtk_HashBag_t* bag, uint8_t* string, int32_t capacity);

/* HashBag-To-StringBuilder */

void jtk_HashBag_toStringBuilder(jtk_HashBag_t* bag, jtk_StringBuilder_t* builder);

/* Iterator */

jtk_Iterator_t* jtk_HashBag_getIterator(jtk_HashBag_t* bag);

/* Remove */

bool jtk_HashBag_remove(jtk_HashBag_t* bag, void* element);
bool jtk_HashBag_removeCopies(jtk_HashBag_t* bag, void* element, int32_t copies);
bool jtk_HashBag_removeAll(jtk_HashBag_t* bag, void* element);
int32_t jtk_HashBag_removeFromCollection(jtk_HashBag_t* bag, jtk_CollectionType_t type, void* collection);
int32_t jtk_HashBag_removeCopiesFromCollection(jtk_HashBag_t* bag, jtk_CollectionType_t type, void* collection, int32_t copies);
int32_t jtk_HashBag_removeAllFromCollection(jtk_HashBag_t* bag, jtk_CollectionType_t type, void* collection);
int32_t jtk_HashBag_removeFromIterator(jtk_HashBag_t* bag, jtk_Iterator_t* iterator);
int32_t jtk_HashBag_removeCopiesFromIterator(jtk_HashBag_t* bag, jtk_Iterator_t* iterator, int32_t copies);
int32_t jtk_HashBag_removeAllFromIterator(jtk_HashBag_t* bag, jtk_Iterator_t* iterator);

/* Size */

int32_t jtk_HashBag_getSize(jtk_HashBag_t* bag);

#endif /* JTK_COLLECTION_BAG_HASH_BAG_H */