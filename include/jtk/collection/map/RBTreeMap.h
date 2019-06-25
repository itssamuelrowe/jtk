// Thursday, July 05, 2018

#ifndef JTK_COLLECTION_MAP_RB_TREE_MAP_H
#define JTK_COLLECTION_MAP_RB_TREE_MAP_H

#include <jtk/Configuration.h>
#include <jtk/collection/Iterator.h>
#include <jtk/collection/map/RBTreeMapEntry.h>
#include <jtk/core/ObjectAdapter.h>

/*******************************************************************************
 * RBTreeColor                                                                 *
 *******************************************************************************/

#define JTK_RBT_COLOR_BLACK false
#define JTK_RBT_COLOR_RED true

/*******************************************************************************
 * RBTreeMap                                                                   *
 *******************************************************************************/

/**
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.0
 */
struct jtk_RBTreeMap_t {
    jtk_ObjectAdapter_t* m_keyAdapter;
    jtk_ObjectAdapter_t* m_valueAdapter;
    int32_t m_size;
    jtk_RBTreeMapEntry_t* m_root;
};

typedef struct jtk_RBTreeMap_t jtk_RBTreeMap_t;

/* Color (private) */

bool jtk_RBTreeMap_getColor(jtk_RBTreeMapEntry_t* entry);
void jtk_RBTreeMap_setColor(jtk_RBTreeMapEntry_t* entry, bool color);

/* Entries (private) */

void jtk_RBTreeMap_destroyEntries(jtk_RBTreeMapEntry_t* entry);

/* Entry (private) */

jtk_RBTreeMapEntry_t* jtk_RBTreeMap_getEntry(jtk_RBTreeMap_t* map, void* key);
void jtk_RBTreeMap_removeEntry(jtk_RBTreeMap_t* map, jtk_RBTreeMapEntry_t* entry);
jtk_RBTreeMapEntry_t* jtk_RBTreeMap_getFirstEntry(jtk_RBTreeMap_t* map);
jtk_RBTreeMapEntry_t* jtk_RBTreeMap_getLastEntry(jtk_RBTreeMap_t* map);

/* Rotate (private) */

void jtk_RBTreeMap_rotateLeft(jtk_RBTreeMap_t* map, jtk_RBTreeMapEntry_t* entry);
void jtk_RBTreeMap_rotateRight(jtk_RBTreeMap_t* map, jtk_RBTreeMapEntry_t* entry);

/* Normalize (private) */

void jtk_RBTreeMap_normalizeInsertion(jtk_RBTreeMap_t* map, jtk_RBTreeMapEntry_t* entry1);
void jtk_RBTreeMap_normalizeRemoval(jtk_RBTreeMap_t* map, jtk_RBTreeMapEntry_t* entry);

/* Relative (private) */

jtk_RBTreeMapEntry_t* jtk_RBTreeMap_getParent(jtk_RBTreeMapEntry_t* entry);
jtk_RBTreeMapEntry_t* jtk_RBTreeMap_getLeft(jtk_RBTreeMapEntry_t* entry);
jtk_RBTreeMapEntry_t* jtk_RBTreeMap_getRight(jtk_RBTreeMapEntry_t* entry);
jtk_RBTreeMapEntry_t* jtk_RBTreeMap_getSuccessor(jtk_RBTreeMapEntry_t* entry);

/* Constructor */

jtk_RBTreeMap_t* jtk_RBTreeMap_new(jtk_ObjectAdapter_t* keyAdapter, jtk_ObjectAdapter_t* valueAdapter);
jtk_RBTreeMap_t* jtk_RBTreeMap_newEx(jtk_ObjectAdapter_t* keyAdapter, jtk_ObjectAdapter_t* valueAdapter);

/* Destructor */

void jtk_RBTreeMap_delete(jtk_RBTreeMap_t* tree);

/* Clear */

void jtk_RBTreeMap_clear(jtk_RBTreeMap_t* tree);

/* Clone */

jtk_RBTreeMap_t* jtk_RBTreeMap_clone(jtk_RBTreeMap_t* tree);

/* Contain */

bool jtk_RBTreeMap_containKey(jtk_RBTreeMap_t* tree, void* key);
bool jtk_RBTreeMap_containValue(jtk_RBTreeMap_t* tree, void* value);

/* Iterator */

jtk_Iterator_t* jtk_RBTreeMap_getKeyIterator(jtk_RBTreeMap_t* tree);
jtk_Iterator_t* jtk_RBTreeMap_getValueIterator(jtk_RBTreeMap_t* tree);

/* Key */

void* jtk_RBTreeMap_getFirstKey(jtk_RBTreeMap_t* tree);
void* jtk_RBTreeMap_getLastKey(jtk_RBTreeMap_t* tree);

/* Put */

bool jtk_RBTreeMap_put(jtk_RBTreeMap_t* map, void* key, void* value);
bool jtk_RBTreeMap_putStrictly(jtk_RBTreeMap_t* map, void* key, void* value);

/* Remove */

bool jtk_RBTreeMap_remove(jtk_RBTreeMap_t* map, void* key);

/* Size */

int32_t jtk_RBTreeMap_getSize(jtk_RBTreeMap_t* tree);

/* Value */

void* jtk_RBTreeMap_getValue(jtk_RBTreeMap_t* tree, void* key);
bool jtk_RBTreeMap_setValue(jtk_RBTreeMap_t* tree, void* key, void* value);
bool jtk_RBTreeMap_setValueEx(jtk_RBTreeMap_t* tree, void* key, void* value, void** previousValue);

#endif /* JTK_COLLECTION_MAP_RB_TREE_MAP_H */