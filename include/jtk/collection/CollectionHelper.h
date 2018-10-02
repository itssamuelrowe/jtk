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

// Thursday, July 12, 2018

#ifndef JTK_COLLECTION_COLLECTION_HELPER_H
#define JTK_COLLECTION_COLLECTION_HELPER_H

#include <jtk/collection/CollectionType.h>
#include <jtk/collection/Iterator.h>

/**
 * @class CollectionHelper
 * @ingroup jtk_collection
 * @author Samuel Rowe
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