// Thursday, July 12, 2018

#ifndef JTK_COLLECTION_COLLECTION_HELPER_H
#define JTK_COLLECTION_COLLECTION_HELPER_H

#include <jtk/collection/CollectionType.h>
#include <jtk/collection/Iterator.h>

/**
 * @class CollectionHelper
 * @ingroup jtk_collection
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.0
 */

/*******************************************************************************
 * CollectionHelper                                                            *
 *******************************************************************************/

/**
 * @memberof CollectionHelper
 */
jtk_Iterator_t* jtk_CollectionHelper_getIterator(jtk_CollectionType_t type, void* collection);

#endif /* JTK_COLLECTION_COLLECTION_HELPER_H */