// Monday, February 26, 2018

#include <jtk/core/CString.h>
#include <jtk/core/ObjectAdapter.h>
#include <jtk/core/CStringObjectAdapter.h>

/*******************************************************************************
 * CStringObjectAdapter                                                         *
 *******************************************************************************/

static jtk_ObjectAdapter_t s_stringObjectAdapter = {
    NULL, // TODO: compare
    jtk_CStringObjectAdapter_equals,
    jtk_CStringObjectAdapter_hash
};

jtk_ObjectAdapter_t* jtk_CStringObjectAdapter_getInstance() {
    return &s_stringObjectAdapter;
}

bool jtk_CStringObjectAdapter_equals(const uint8_t* string1, const uint8_t* string2) {
    int32_t string1Length = jtk_CString_getSize(string1);
    int32_t string2Length = jtk_CString_getSize(string2);
    return jtk_CString_equals(string1, string1Length, string2, string2Length);
}

int32_t jtk_CStringObjectAdapter_hash(const uint8_t* string) {
    return jtk_CString_hash(string);
}