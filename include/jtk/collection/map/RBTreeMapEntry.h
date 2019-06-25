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