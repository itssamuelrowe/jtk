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

// Friday, July 27, 2018

#ifndef JTK_COLLECTION_ARRAY_ARRAY_ITERATOR
#define JTK_COLLECTION_ARRAY_ARRAY_ITERATOR

#include <jtk/Configuration.h>
#include <jtk/collection/Iterator.h>

/*******************************************************************************
 * ArrayIterator                                                               *
 *******************************************************************************/

/**
 * The ArrayIterator class represents a source iterator over the elements
 * contained in an array.
 *
 * Every instance of the ArrayIterator class is associated with a single
 * instance of the Iterator class. Invoke the `jtk_ArrayIterator_getIterator()`
 * function to retrieve this iterator. The destruction of the iterator and source
 * iterator pair is mutually exclusuive. In other words, you can either destroy
 * the iterator or the source iterator. You cannot destroy both.
 *
 * The lifecycle of the source iterator is tightly associated with the
 * iterator. The ArrayIterator class strictly adheres to the iterator
 * and source iterator relationship described in the documentation of the
 * Iterator class. Please refer the documentation of the Iterator class for
 * more information.
 *
 * <codeblock>
 * ...
 * jtk_ArrayIterator_t* sourceIterator = jtk_ArrayIterator_new(array);
 * jtk_Iterator_t* iterator = jtk_ArrayIterator_getIterator(sourceIterator);
 * while (jtk_Iterator_hasNext(iterator)) {
 *     ...
 * }
 * jtk_Iterator_delete(iterator);
 * // jtk_ArrayIterator_delete(sourceIterator);
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
 * @class   ArrayIterator
 * @ingroup JtkCollectionModule
 * @author  Samuel Rowe
 * @since   JTK 1.0
 */
struct jtk_ArrayIterator_t {

    /**
     * The array from which the elements are extracted.
     */
    void** m_array;
    
    /**
     * The size of the array.
     */
    int32_t m_size;

    /**
     * The index at which the next element is located.
     */
    int32_t m_index;

    /**
     * The iterator associated with this source iterator.
     */
    jtk_Iterator_t* m_iterator;
};

typedef struct jtk_ArrayIterator_t jtk_ArrayIterator_t;

/* Constructor */

/**
 * Creates a new source iterator over the specified array list.
 *
 * @param  array
 *         This argument specifies the array from which the elements are
 *         extracted.
 * @param  size
 *         This argument specifies the size of the array.
 * @return A newly created source iterator. The user is responsible for
 *         destroying the iterator.
 * @memberof ArrayIterator
 */
jtk_ArrayIterator_t* jtk_ArrayIterator_new(void** array, int32_t size);

/* Destructor */

/**
 * Destroys the specified source iterator.
 *
 * @param  iterator
 *         This argument specifies the source iterator to destroy.
 * @memberof ArrayIterator
 */
void jtk_ArrayIterator_delete(jtk_ArrayIterator_t* iterator);

/* Destroy (private) */

/**
 * This is a private function. It acts as the middle man between the iterator
 * and the source iterator with respect to the ArrayIterator class. It
 * is invoked to control the internal states during destruction.
 *
 * Invoke this function only if you know what you are doing! Further, this
 * function may be subjected to undocumented changes.
 *
 * @param  iterator
 *         This argument specifies the source iterator to destroy.
 * @private
 * @memberof ArrayIterator
 */
void jtk_ArrayIterator_destroy(jtk_ArrayIterator_t* iterator);

/* Iterator */

/**
 * Returns the iterator associated with the specified source iterator.
 *
 * @param  iterator
 *         This argument specifies the source iterator.
 * @return The iterator associated with the specified source iterator.
 * @memberof ArrayIterator
 */
jtk_Iterator_t* jtk_ArrayIterator_getIterator(jtk_ArrayIterator_t* iterator);

/* Next */

/**
 * Determines whether the source has more elements to return, or not.
 *
 * @param  iterator
 *         This argument specifies the source iterator.
 * @return `true` if the source has more elements to return;
 *         `false` otherwise.
 * @memberof ArrayIterator
 */
bool jtk_ArrayIterator_hasNext(jtk_ArrayIterator_t* iterator);

/**
 * Returns the next element from the source. The internal states are updated
 * accordingly.
 *
 * @param  iterator
 *         This argument specifies the source iterator.
 * @return The next element from the source.
 * @memberof ArrayIterator
 */
void* jtk_ArrayIterator_getNext(jtk_ArrayIterator_t* iterator);

#endif /* JTK_COLLECTION_ARRAY_ARRAY_ITERATOR */