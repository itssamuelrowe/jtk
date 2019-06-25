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

// Friday, July 06, 2018

#include <jtk/collection/map/RBTreeMap.h>
#include <jtk/collection/stack/LinkedStack.h>

/*******************************************************************************
 * RBTreeMap                                                                   *
 *******************************************************************************/

/* Color (private) */

bool jtk_RBTreeMap_getColor(jtk_RBTreeMapEntry_t* entry) {
    return (entry == NULL)? JTK_RBT_COLOR_BLACK : entry->m_color;
}

void jtk_RBTreeMap_setColor(jtk_RBTreeMapEntry_t* entry, bool color) {
    if (entry != NULL) {
        entry->m_color = color;
    }
}

/* Entries (private) */

void jtk_RBTreeMap_destroyEntries(jtk_RBTreeMapEntry_t* entry) {
    jtk_LinkedStack_t* stack = jtk_LinkedStack_new();
    jtk_LinkedStack_push(stack, entry);
    while (!jtk_LinkedStack_isEmpty(stack)) {
        jtk_RBTreeMapEntry_t* entry = (jtk_RBTreeMapEntry_t*)jtk_LinkedStack_pop(stack);

        jtk_LinkedStack_push(stack, entry->m_left);
        jtk_LinkedStack_push(stack, entry->m_right);

        jtk_RBTreeMapEntry_delete(entry);
    }
    jtk_LinkedStack_delete(stack);
}

/* Entry (private) */

jtk_RBTreeMapEntry_t* jtk_RBTreeMap_getEntry(jtk_RBTreeMap_t* map, void* key) {
    jtk_Assert_assertObject(map, "The specified red-black tree map is null.");

    jtk_RBTreeMapEntry_t* entry = map->m_root;
    while (entry != NULL) {
        int32_t comparison = map->m_keyAdapter->compare(entry->m_key, key);
        if (comparison < 0) {
            entry = entry->m_left;
        }
        else if (comparison > 0) {
            entry = entry->m_right;
        }
        else {
            return entry;
        }
    }
    return NULL;
}

void jtk_RBTreeMap_removeEntry(jtk_RBTreeMap_t* map, jtk_RBTreeMapEntry_t* entry) {
    jtk_RBTreeMapEntry_t* temporary = entry;

    if ((entry->m_left != NULL) && (entry->m_right != NULL)) {
        jtk_RBTreeMapEntry_t* successor = jtk_RBTreeMap_getSuccessor(entry);
        entry->m_key = successor->m_key;
        entry->m_value = successor->m_value;
        entry = successor;
    }

    jtk_RBTreeMapEntry_t* replacement = (entry->m_left != NULL)? entry->m_left : entry->m_right;
    if (replacement != NULL) {
        replacement->m_parent = entry->m_parent;
        if (entry->m_parent == NULL) {
            map->m_root = replacement;
        }
        else if (entry == entry->m_parent->m_left) {
            entry->m_parent->m_left  = replacement;
        }
        else {
            entry->m_parent->m_right = replacement;
        }
        entry->m_left = entry->m_right = entry->m_parent = NULL;

        if (entry->m_color == JTK_RBT_COLOR_BLACK) {
            jtk_RBTreeMap_normalizeRemoval(map, replacement);
        }
    }
    else if (entry->m_parent == NULL) {
        map->m_root = NULL;
    }
    else {
        if (entry->m_color == JTK_RBT_COLOR_BLACK)
            jtk_RBTreeMap_normalizeRemoval(map, entry);

        if (entry->m_parent != NULL) {
            if (entry == entry->m_parent->m_left) {
                entry->m_parent->m_left = NULL;
            }
            else if (entry == entry->m_parent->m_right) {
                entry->m_parent->m_right = NULL;
            }
            entry->m_parent = NULL;
        }
    }

    jtk_RBTreeMapEntry_delete(temporary);
    map->m_size--;
}

jtk_RBTreeMapEntry_t* jtk_RBTreeMap_getFirstEntry(jtk_RBTreeMap_t* map) {
    jtk_RBTreeMapEntry_t* entry = map->m_root;
    if (entry != NULL) {
        while (entry->m_left != NULL) {
            entry = entry->m_left;
        }
    }
    return entry;
}

jtk_RBTreeMapEntry_t* jtk_RBTreeMap_getLastEntry(jtk_RBTreeMap_t* map) {
    jtk_RBTreeMapEntry_t* entry = map->m_root;
    if (entry != NULL) {
        while (entry->m_right != NULL) {
            entry = entry->m_right;
        }
    }
    return entry;
}

/* Rotate (private) */

void jtk_RBTreeMap_rotateLeft(jtk_RBTreeMap_t* map, jtk_RBTreeMapEntry_t* entry) {
    if (entry != NULL) {
        jtk_RBTreeMapEntry_t* right = entry->m_right;
        entry->m_right = right->m_left;
        if (right->m_left != NULL) {
            right->m_left->m_parent = entry;
        }
        right->m_parent = entry->m_parent;
        if (entry->m_parent == NULL) {
            map->m_root = right;
        }
        else if (entry->m_parent->m_left == entry) {
            entry->m_parent->m_left = right;
        }
        else {
            entry->m_parent->m_right = right;
        }
        right->m_left = entry;
        entry->m_parent = right;
    }
}

void jtk_RBTreeMap_rotateRight(jtk_RBTreeMap_t* map, jtk_RBTreeMapEntry_t* entry) {
    if (entry != NULL) {
        jtk_RBTreeMapEntry_t* left = entry->m_left;
        entry->m_left = left->m_right;
        if (left->m_right != NULL) {
            left->m_right->m_parent = entry;
        }
        left->m_parent = entry->m_parent;
        if (entry->m_parent == NULL) {
            map->m_root = left;
        }
        else if (entry->m_parent->m_right == entry) {
            entry->m_parent->m_right = left;
        }
        else {
            entry->m_parent->m_left = left;
        }
        left->m_right = entry;
        entry->m_parent = left;
    }
}

/* Normalize */

void jtk_RBTreeMap_normalizeInsertion(jtk_RBTreeMap_t* map, jtk_RBTreeMapEntry_t* entry1) {
    jtk_RBTreeMapEntry_t* entry2 = NULL;

    entry1->m_color = JTK_RBT_COLOR_RED;
    while ((entry1 != NULL) && (entry1 != map->m_root) &&
           (entry1->m_parent->m_color == JTK_RBT_COLOR_RED)) {
        if (jtk_RBTreeMap_getParent(entry1) == jtk_RBTreeMap_getLeft(jtk_RBTreeMap_getParent(jtk_RBTreeMap_getParent(entry1)))) {
            entry2 = jtk_RBTreeMap_getRight(jtk_RBTreeMap_getParent(jtk_RBTreeMap_getParent(entry1)));
            if (jtk_RBTreeMap_getColor(entry2) == JTK_RBT_COLOR_RED) {
                jtk_RBTreeMap_setColor(jtk_RBTreeMap_getParent(entry1), JTK_RBT_COLOR_BLACK);
                jtk_RBTreeMap_setColor(entry2, JTK_RBT_COLOR_BLACK);
                jtk_RBTreeMap_setColor(jtk_RBTreeMap_getParent(jtk_RBTreeMap_getParent(entry1)), JTK_RBT_COLOR_RED);
                entry1 = jtk_RBTreeMap_getParent(jtk_RBTreeMap_getParent(entry1));
            }
            else {
                if (entry1 == jtk_RBTreeMap_getRight(jtk_RBTreeMap_getParent(entry1))) {
                    entry1 = jtk_RBTreeMap_getParent(entry1);
                    jtk_RBTreeMap_rotateLeft(map, entry1);
                }
                jtk_RBTreeMap_setColor(jtk_RBTreeMap_getParent(entry1), JTK_RBT_COLOR_BLACK);
                jtk_RBTreeMap_setColor(jtk_RBTreeMap_getParent(jtk_RBTreeMap_getParent(entry1)), JTK_RBT_COLOR_RED);
                jtk_RBTreeMap_rotateRight(map, jtk_RBTreeMap_getParent(jtk_RBTreeMap_getParent(entry1)));
            }
        }
        else {
            entry2 = jtk_RBTreeMap_getLeft(jtk_RBTreeMap_getParent(jtk_RBTreeMap_getParent(entry1)));
            if (jtk_RBTreeMap_getColor(entry2) == JTK_RBT_COLOR_RED) {
                jtk_RBTreeMap_setColor(jtk_RBTreeMap_getParent(entry1), JTK_RBT_COLOR_BLACK);
                jtk_RBTreeMap_setColor(entry2, JTK_RBT_COLOR_BLACK);
                jtk_RBTreeMap_setColor(jtk_RBTreeMap_getParent(jtk_RBTreeMap_getParent(entry1)), JTK_RBT_COLOR_RED);
                entry1 = jtk_RBTreeMap_getParent(jtk_RBTreeMap_getParent(entry1));
            }
            else {
                if (entry1 == jtk_RBTreeMap_getLeft(jtk_RBTreeMap_getParent(entry1))) {
                    entry1 = jtk_RBTreeMap_getParent(entry1);
                    jtk_RBTreeMap_rotateRight(map, entry1);
                }
                jtk_RBTreeMap_setColor(jtk_RBTreeMap_getParent(entry1), JTK_RBT_COLOR_BLACK);
                jtk_RBTreeMap_setColor(jtk_RBTreeMap_getParent(jtk_RBTreeMap_getParent(entry1)), JTK_RBT_COLOR_RED);
                jtk_RBTreeMap_rotateLeft(map, jtk_RBTreeMap_getParent(jtk_RBTreeMap_getParent(entry1)));
            }
        }
    }
    map->m_root->m_color = JTK_RBT_COLOR_BLACK;
}

void jtk_RBTreeMap_normalizeRemoval(jtk_RBTreeMap_t* map, jtk_RBTreeMapEntry_t* entry) {
    while ((entry != map->m_root) && (jtk_RBTreeMap_getColor(entry) == JTK_RBT_COLOR_BLACK)) {
        if (entry == jtk_RBTreeMap_getLeft(jtk_RBTreeMap_getParent(entry))) {
            jtk_RBTreeMapEntry_t* sibling = jtk_RBTreeMap_getRight(jtk_RBTreeMap_getParent(entry));

            if (jtk_RBTreeMap_getColor(sibling) == JTK_RBT_COLOR_RED) {
                jtk_RBTreeMap_setColor(sibling, JTK_RBT_COLOR_BLACK);
                jtk_RBTreeMap_setColor(jtk_RBTreeMap_getParent(entry), JTK_RBT_COLOR_RED);
                jtk_RBTreeMap_rotateLeft(map, jtk_RBTreeMap_getParent(entry));
                sibling = jtk_RBTreeMap_getRight(jtk_RBTreeMap_getParent(entry));
            }

            if ((jtk_RBTreeMap_getColor(jtk_RBTreeMap_getLeft(sibling)) == JTK_RBT_COLOR_BLACK) &&
                (jtk_RBTreeMap_getColor(jtk_RBTreeMap_getRight(sibling)) == JTK_RBT_COLOR_BLACK)) {
                jtk_RBTreeMap_setColor(sibling, JTK_RBT_COLOR_RED);
                entry = jtk_RBTreeMap_getParent(entry);
            }
            else {
                if (jtk_RBTreeMap_getColor(jtk_RBTreeMap_getRight(sibling)) == JTK_RBT_COLOR_BLACK) {
                    jtk_RBTreeMap_setColor(jtk_RBTreeMap_getLeft(sibling), JTK_RBT_COLOR_BLACK);
                    jtk_RBTreeMap_setColor(sibling, JTK_RBT_COLOR_RED);
                    jtk_RBTreeMap_rotateRight(map, sibling);
                    sibling = jtk_RBTreeMap_getRight(jtk_RBTreeMap_getParent(entry));
                }
                jtk_RBTreeMap_setColor(sibling, jtk_RBTreeMap_getColor(jtk_RBTreeMap_getParent(entry)));
                jtk_RBTreeMap_setColor(jtk_RBTreeMap_getParent(entry), JTK_RBT_COLOR_BLACK);
                jtk_RBTreeMap_setColor(jtk_RBTreeMap_getRight(sibling), JTK_RBT_COLOR_BLACK);
                jtk_RBTreeMap_rotateLeft(map, jtk_RBTreeMap_getParent(entry));
                entry = map->m_root;
            }
        }
        else {
            jtk_RBTreeMapEntry_t* sibling = jtk_RBTreeMap_getLeft(jtk_RBTreeMap_getParent(entry));

            if (jtk_RBTreeMap_getColor(sibling) == JTK_RBT_COLOR_RED) {
                jtk_RBTreeMap_setColor(sibling, JTK_RBT_COLOR_BLACK);
                jtk_RBTreeMap_setColor(jtk_RBTreeMap_getParent(entry), JTK_RBT_COLOR_RED);
                jtk_RBTreeMap_rotateRight(map, jtk_RBTreeMap_getParent(entry));
                sibling = jtk_RBTreeMap_getLeft(jtk_RBTreeMap_getParent(entry));
            }

            if (jtk_RBTreeMap_getColor(jtk_RBTreeMap_getRight(sibling)) == JTK_RBT_COLOR_BLACK &&
                jtk_RBTreeMap_getColor(jtk_RBTreeMap_getLeft(sibling)) == JTK_RBT_COLOR_BLACK) {
                jtk_RBTreeMap_setColor(sibling, JTK_RBT_COLOR_RED);
                entry = jtk_RBTreeMap_getParent(entry);
            }
            else {
                if (jtk_RBTreeMap_getColor(jtk_RBTreeMap_getLeft(sibling)) == JTK_RBT_COLOR_BLACK) {
                    jtk_RBTreeMap_setColor(jtk_RBTreeMap_getRight(sibling), JTK_RBT_COLOR_BLACK);
                    jtk_RBTreeMap_setColor(sibling, JTK_RBT_COLOR_RED);
                    jtk_RBTreeMap_rotateLeft(map, sibling);
                    sibling = jtk_RBTreeMap_getLeft(jtk_RBTreeMap_getParent(entry));
                }
                jtk_RBTreeMap_setColor(sibling, jtk_RBTreeMap_getColor(jtk_RBTreeMap_getParent(entry)));
                jtk_RBTreeMap_setColor(jtk_RBTreeMap_getParent(entry), JTK_RBT_COLOR_BLACK);
                jtk_RBTreeMap_setColor(jtk_RBTreeMap_getLeft(sibling), JTK_RBT_COLOR_BLACK);
                jtk_RBTreeMap_rotateRight(map, jtk_RBTreeMap_getParent(entry));
                entry = map->m_root;
            }
        }
    }
    jtk_RBTreeMap_setColor(entry, JTK_RBT_COLOR_BLACK);
}

/* Relative (private) */

jtk_RBTreeMapEntry_t* jtk_RBTreeMap_getParent(jtk_RBTreeMapEntry_t* entry) {
    return (entry == NULL)? NULL : entry->m_parent;
}

jtk_RBTreeMapEntry_t* jtk_RBTreeMap_getLeft(jtk_RBTreeMapEntry_t* entry) {
    return (entry == NULL)? NULL : entry->m_left;
}

jtk_RBTreeMapEntry_t* jtk_RBTreeMap_getRight(jtk_RBTreeMapEntry_t* entry) {
    return (entry == NULL)? NULL : entry->m_right;
}

jtk_RBTreeMapEntry_t* jtk_RBTreeMap_getSuccessor(jtk_RBTreeMapEntry_t* node) {
    jtk_RBTreeMapEntry_t* parent = NULL;
    if (node != NULL) {
        if (node->m_right != NULL) {
            parent = node->m_right;
            while (parent->m_left != NULL) {
                parent = parent->m_left;
            }
        }
        else {
            parent = node->m_parent;
            jtk_RBTreeMapEntry_t* entry = node;
            while ((parent != NULL) && (entry == parent->m_right)) {
                entry = parent;
                parent = parent->m_parent;
            }
        }
    }
    return parent;
}

/* Constructor */

jtk_RBTreeMap_t* jtk_RBTreeMap_new(jtk_ObjectAdapter_t* keyAdapter,
    jtk_ObjectAdapter_t* valueAdapter) {
    return jtk_RBTreeMap_newEx(keyAdapter, valueAdapter);
}

jtk_RBTreeMap_t* jtk_RBTreeMap_newEx(jtk_ObjectAdapter_t* keyAdapter,
    jtk_ObjectAdapter_t* valueAdapter) {
    jtk_Assert_assertObject(keyAdapter, "The specified key adapter is null.");
    jtk_Assert_assertObject(valueAdapter, "The specified value adapter is null.");

    jtk_RBTreeMap_t* tree = jtk_Memory_allocate(jtk_RBTreeMap_t, 1);
    tree->m_keyAdapter = keyAdapter;
    tree->m_valueAdapter = valueAdapter;
    tree->m_size = 0;
    tree->m_root = NULL;

    return tree;
}

/* Destructor */

void jtk_RBTreeMap_delete(jtk_RBTreeMap_t* map) {
    jtk_Assert_assertObject(map, "The specified red-black tree map is null.");

    jtk_RBTreeMap_destroyEntries(map->m_root);
    jtk_Memory_deallocate(map);
}

/* Clear */

void jtk_RBTreeMap_clear(jtk_RBTreeMap_t* map) {
    jtk_Assert_assertObject(map, "The specified red-black tree map is null.");

    jtk_RBTreeMap_destroyEntries(map->m_root);
    map->m_root = NULL;
    map->m_size = 0;
}

/* Contains */

bool jtk_RBTreeMap_containsKey(jtk_RBTreeMap_t* map, void* key) {
    jtk_Assert_assertObject(map, "The specified red-black tree map is null.");

    return jtk_RBTreeMap_getEntry(map, key) != NULL;
}

bool jtk_RBTreeMap_containsValue(jtk_RBTreeMap_t* map, void* value) {
    jtk_Assert_assertObject(map, "The specified red-black tree map is null.");

    bool result = false;
    jtk_RBTreeMapEntry_t* entry = jtk_RBTreeMap_getFirstEntry(map);
    while (entry != NULL) {
        if (map->m_valueAdapter->equals(entry->m_value, value)) {
            result = true;
            break;
        }
        entry = jtk_RBTreeMap_getSuccessor(entry);
    }
    return result;
}

/* Key */

void* jtk_RBTreeMap_getFirstKey(jtk_RBTreeMap_t* map) {
    jtk_Assert_assertObject(map, "The specified red-black tree map is null.");

    jtk_RBTreeMapEntry_t* entry = jtk_RBTreeMap_getFirstEntry(map);
    return (entry == NULL)? NULL : entry->m_key;
}

void* jtk_RBTreeMap_getLastKey(jtk_RBTreeMap_t* map) {
    jtk_Assert_assertObject(map, "The specified red-black tree map is null.");

    jtk_RBTreeMapEntry_t* entry = jtk_RBTreeMap_getLastEntry(map);
    return (entry == NULL)? NULL : entry->m_key;
}

/* Put */

bool jtk_RBTreeMap_put(jtk_RBTreeMap_t* map, void* key, void* value) {
    jtk_Assert_assertObject(map, "The specified red-black tree map is null.");

    bool result = false;
    jtk_RBTreeMapEntry_t* entry = map->m_root;
    if (entry == NULL) {
        map->m_root = jtk_RBTreeMapEntry_new(NULL, key, value);
        map->m_size = 1;
        result = true;
    }
    else {
        jtk_RBTreeMapEntry_t* parent = NULL;
        int32_t comparison;
        do {
            parent = entry;
            comparison = map->m_keyAdapter->compare(entry->m_key, key);
            if (comparison < 0) {
                entry = entry->m_left;
            }
            else if (comparison > 0) {
                entry = entry->m_right;
            }
            else {
                entry->m_value = value;
                result = false;
                break;
            }
        }
        while (entry != NULL);

        if (!result) {
            jtk_RBTreeMapEntry_t* newEntry = jtk_RBTreeMapEntry_new(parent, key, value);
            if (comparison < 0) {
                parent->m_left = newEntry;
            }
            else {
                parent->m_right = newEntry;
            }
            jtk_RBTreeMap_normalizeInsertion(map, newEntry);

            result = true;
            /* Since a new entry was added, increment the size of the map. */
            map->m_size++;
        }

    }
    return result;
}

/* Remove */

bool jtk_RBTreeMap_remove(jtk_RBTreeMap_t* map, void* key) {
    jtk_Assert_assertObject(map, "The specified red-black tree map is null.");

    bool result = false;
    jtk_RBTreeMapEntry_t* entry = jtk_RBTreeMap_getEntry(map, key);
    if (entry != NULL) {
        jtk_RBTreeMap_removeEntry(map, entry);
        result = true;
    }
    return result;
}

/* Size */

int32_t jtk_RBTreeMap_getSize(jtk_RBTreeMap_t* map) {
    jtk_Assert_assertObject(map, "The specified red-black tree map is null.");

    return map->m_size;
}

/* Value */

void* jtk_RBTreeMap_getValue(jtk_RBTreeMap_t* map, void* key) {
    jtk_Assert_assertObject(map, "The specified red-black tree map is null.");

    jtk_RBTreeMapEntry_t* entry = jtk_RBTreeMap_getEntry(map, key);
    return (entry == NULL)? NULL : entry->m_value;
}