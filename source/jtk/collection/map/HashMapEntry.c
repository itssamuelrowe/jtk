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

// Friday, June 08, 2018

#include <jtk/collection/map/HashMapEntry.h>

/*******************************************************************************
 * HashMapEntry                                                                *
 *******************************************************************************/

jtk_HashMapEntry_t* jtk_HashMapEntry_new(void* key, void* value,
    int32_t hashCode, jtk_HashMapEntry_t* next) {
    jtk_HashMapEntry_t* entry = jtk_Memory_allocate(jtk_HashMapEntry_t, 1);
    entry->m_key = key;
    entry->m_value = value;
    entry->m_hashCode = hashCode;
    entry->m_next = next;
    return entry;
}

void jtk_HashMapEntry_delete(jtk_HashMapEntry_t* entry) {
    jtk_Assert_assertObject(entry, "The specified entry is null.");

    jtk_Memory_deallocate(entry);
}