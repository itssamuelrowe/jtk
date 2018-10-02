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

// Monday, July 30, 2018

#include <jtk/core/PointerObjectAdapter.h>

/*******************************************************************************
 * PointerObjectAdapter                                                        *
 *******************************************************************************/

static jtk_ObjectAdapter_t s_pointerObjectAdapter = {
    jtk_PointerObjectAdapter_compare,
    jtk_PointerObjectAdapter_equals,
    jtk_PointerObjectAdapter_hash
};

jtk_ObjectAdapter_t* jtk_PointerObjectAdapter_getInstance() {
    return &s_pointerObjectAdapter;
}

int32_t jtk_PointerObjectAdapter_compare(const void* pointer1, const void* pointer2) {
    return (pointer1 > pointer2)? -1 : ((pointer1 == pointer2)? 0 : 1);
}

bool jtk_PointerObjectAdapter_equals(const void* pointer1, const void* pointer2) {
    return pointer1 == pointer2;
}

int32_t jtk_PointerObjectAdapter_hash(const void* pointer) {
    // TODO: For 64 bit pointers!
    return (intptr_t)pointer;
}