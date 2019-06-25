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

// Friday, June 08, 2018

#ifndef JTK_COLLECTION_LIST_ARRAY_LIST_ITERATOR_H
#define JTK_COLLECTION_LIST_ARRAY_LIST_ITERATOR_H

#include <jtk/Configuration.h>
#include <jtk/collection/Iterator.h>

/* Forward Declarations */

typedef struct jtk_ArrayList_t jtk_ArrayList_t;

/*******************************************************************************
 * ArrayListIterator                                                           *
 *******************************************************************************/

/**
 * The ArrayListIterator class represents a source iterator over the elements
 * contained in an array list.
 *
 * Every instance of the ArrayListIterator class is associated with a single
 * instance of the Iterator class. Invoke the `jtk_ArrayListIterator_getIterator()`
 * function to retrieve this iterator. The destruction of the iterator and source
 * iterator pair is mutually exclusuive. In other words, you can either destroy
 * the iterator or the source iterator.
 *
 * The lifecycle of the source iterator is tightly associated with the
 * iterator. The ArrayListIterator class strictly adheres to the iterator
 * and source iterator relationship described in the documentation of the
 * Iterator class. Please refer the documentation of the Iterator class for
 * more information.
 *
 * <codeblock>
 * ...
 * jtk_ArrayListIterator_t* sourceIterator = jtk_ArrayListIterator_new(list);
 * jtk_Iterator_t* iterator = jtk_ArrayListIterator_getIterator(sourceIterator);
 * while (jtk_Iterator_hasNext(iterator)) {
 *     ...
 * }
 * jtk_Iterator_delete(iterator);
 * // jtk_ArrayListIterator_delete(sourceIterator);
 * // Either destroy the iterator or the source iterator. Since they are
 * // associated with each other, JTK takes care of destroying the other.
 * // Destroying both the iterator and the source iterator results in undefined
 * // behaviour.
 * ...
 * </codeblock>
 *
 * Further, it is recommended that the user avoids accessing the fields of
 * this structure directly. They may be subjected to changes without any
 * notifications. Please employ appropriate interfaces with detailed
 * documentation.
 *
 * @class ArrayListIterator
 * @ingroup jtk_collection_list
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.0
 */
struct jtk_ArrayListIterator_t {

    /**
     * The list from which the elements are extracted.
     */
    jtk_ArrayList_t* m_list;

    /**
     * The index at which the next element is located.
     */
    int32_t m_index;

    /**
     * The iterator associated with this source iterator.
     */
    jtk_Iterator_t* m_iterator;
};

typedef struct jtk_ArrayListIterator_t jtk_ArrayListIterator_t;

/* Constructor */

/**
 * Creates a new source iterator over the specified array list.
 *
 * @param  list
 *         This argument specifies the list from which the elements are
 *         extracted.
 * @return A newly created source iterator. The user is responsible for
 *         destroying the iterator.
 * @memberof ArrayListIterator
 */
jtk_ArrayListIterator_t* jtk_ArrayListIterator_new(jtk_ArrayList_t* list);

/* Destructor */

/**
 * Destroys the specified source iterator.
 *
 * @param  iterator
 *         This argument specifies the source iterator to destroy.
 * @memberof ArrayListIterator
 */
void jtk_ArrayListIterator_delete(jtk_ArrayListIterator_t* iterator);

/* Destroy (private) */

/**
 * This is a private function. It acts as the middle man between the iterator
 * and the source iterator with respect to the ArrayListIterator class. It
 * is invoked to control the internal states during destruction.
 *
 * Invoke this function only if you know what you are doing! Further, this
 * function may be subjected to undocumented changes.
 *
 * @param  iterator
 *         This argument specifies the source iterator to destroy.
 * @private
 * @memberof ArrayListIterator
 */
void jtk_ArrayListIterator_destroy(jtk_ArrayListIterator_t* iterator);

/* Iterator */

/**
 * Returns the iterator associated with the specified source iterator.
 *
 * @param  iterator
 *         This argument specifies the source iterator.
 * @return The iterator associated with the specified source iterator.
 * @memberof ArrayListIterator
 */
jtk_Iterator_t* jtk_ArrayListIterator_getIterator(jtk_ArrayListIterator_t* iterator);

/* Next */

/**
 * Determines whether the source has more elements to return, or not.
 *
 * @param  iterator
 *         This argument specifies the source iterator.
 * @return `true` if the source has more elements to return;
 *         `false` otherwise.
 * @memberof ArrayListIterator
 */
bool jtk_ArrayListIterator_hasNext(jtk_ArrayListIterator_t* iterator);

/**
 * Returns the next element from the source. The internal states are updated
 * accordingly.
 *
 * @param  iterator
 *         This argument specifies the source iterator.
 * @return The next element from the source.
 * @memberof ArrayListIterator
 */
void* jtk_ArrayListIterator_getNext(jtk_ArrayListIterator_t* iterator);

#endif /* JTK_COLLECTION_LIST_ARRAY_LIST_ITERATOR_H */