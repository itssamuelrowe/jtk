/*
 * Copyright 2017-2020 Samuel Rowe
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

// Friday, July 06, 2018

#include <jtk/Configuration.h>

/*******************************************************************************
 * RBTreeMapEntry                                                              *
 *******************************************************************************/

typedef struct jtk_RBTreeMapEntry_t jtk_RBTreeMapEntry_t;

struct jtk_RBTreeMapEntry_t {
    void* m_key;
    void* m_value;
    bool m_color;
    jtk_RBTreeMapEntry_t* m_left;
    jtk_RBTreeMapEntry_t* m_right;
    jtk_RBTreeMapEntry_t* m_parent;
};

/* Constructor */

jtk_RBTreeMapEntry_t* jtk_RBTreeMapEntry_new(jtk_RBTreeMapEntry_t* parent, void* key, void* value);

/* Destructor */

void jtk_RBTreeMapEntry_delete(jtk_RBTreeMapEntry_t* entry);

/* Key */

void* jtk_RBTreeMapEntry_getKey(jtk_RBTreeMapEntry_t* entry);
void jtk_RBTreeMapEntry_setKey(jtk_RBTreeMapEntry_t* entry, void* value);

/* Value */

void jtk_RBTreeMapEntry_setValue(jtk_RBTreeMapEntry_t* entry, void* value);
void* jtk_RBTreeMapEntry_getValue(jtk_RBTreeMapEntry_t* entry);