// Monday, February 26, 2018

#include <jtk/core/ObjectAdapter.h>
#include <jtk/core/StringObjectAdapter.h>

/*******************************************************************************
 * StringObjectAdapter                                                         *
 *******************************************************************************/

static jtk_ObjectAdapter_t s_stringObjectAdapter = {
    NULL, // TODO: compare
    jtk_StringObjectAdapter_equals,
    jtk_StringObjectAdapter_hash
};

jtk_ObjectAdapter_t* jtk_StringObjectAdapter_getInstance() {
    return &s_stringObjectAdapter;
}

bool jtk_StringObjectAdapter_equals(jtk_String_t* string1, jtk_String_t* string2) {
    int32_t string1Length = jtk_String_getSize(string1);
    int32_t string2Length = jtk_String_getSize(string2);
    return jtk_String_equals(string1, string2);
}

int32_t jtk_StringObjectAdapter_hash(jtk_String_t* string) {
    return jtk_String_hash(string);
}