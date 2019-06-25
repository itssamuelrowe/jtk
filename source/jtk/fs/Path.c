// Friday, May 03, 2019

#include <jtk/core/StringBuilder.h>
#include <jtk/fs/Path.h>
#include <jtk/fs/PathComparisonFlag.h>

/*******************************************************************************
 * Path                                                                        *
 *******************************************************************************/

/* Constructor */

jtk_Path_t* jtk_Path_newFromString(const uint8_t* path) {
    jtk_Path_t* result = jtk_Memory_allocate(jtk_Path_t, 1);
    result->m_value = jtk_String_new(path); // jtk_PathHelper_normalize(path);

    return result;
}

jtk_Path_t* jtk_Path_newFromStringEx(const uint8_t* path, int32_t size) {
    jtk_Path_t* result = jtk_Memory_allocate(jtk_Path_t, 1);
    result->m_value = jtk_String_newEx(path, size); // jtk_PathHelper_normalize(path);

    return result;
}

jtk_Path_t* jtk_Path_newFromString_s(jtk_String_t* path) {
    jtk_Path_t* result = jtk_Memory_allocate(jtk_Path_t, 1);
    result->m_value = jtk_String_clone(path); // jtk_PathHelper_normalize(path);

    return result;
}

jtk_Path_t* jtk_Path_newFromPath(jtk_Path_t* path) {
    jtk_Assert_assertObject(path, "The specified path is null.");

    jtk_Path_t* result = jtk_Memory_allocate(jtk_Path_t, 1);
    result->m_value = jtk_String_new(path->m_value); // jtk_PathHelper_normalize(path);

    return result;
}

jtk_Path_t* jtk_Path_newWithParentAndChild_zz(const uint8_t* parent, const uint8_t* child);

jtk_Path_t* jtk_Path_newWithParentAndChild_oo(jtk_Path_t* parent, jtk_Path_t* child) {
    jtk_Assert_assertObject(parent, "The specified parent path is null.");
    jtk_Assert_assertObject(child, "The specified child path is null.");
    
    jtk_StringBuilder_t* builder = jtk_StringBuilder_new();
    jtk_StringBuilder_appendString(builder, parent->m_value);
    jtk_StringBuilder_append_c(builder, JTK_PATH_ELEMENT_SEPARATOR);
    jtk_StringBuilder_appendString(builder, child->m_value);
    
    jtk_Path_t* result = jtk_Memory_allocate(jtk_Path_t, 1);
    result->m_value = jtk_StringBuilder_toString(builder);
    
    jtk_StringBuilder_delete(builder);
    
    return result;
}


jtk_Path_t* jtk_Path_newWithParentAndChild_oz(jtk_Path_t* parent, const uint8_t* child);


jtk_Path_t* jtk_Path_newWithParentAndChild_zo(const uint8_t* parent, jtk_Path_t* child);

/* Destructor */

void jtk_Path_delete(jtk_Path_t* path) {
    jtk_Assert_assertObject(path, "The specified path is null.");

    jtk_String_delete(path->m_value);
    jtk_Memory_deallocate(path);
}

/* Absolute */

bool jtk_Path_isAbsolute(jtk_Path_t* path);


jtk_Path_t* jtk_Path_getAbsolutePath(jtk_Path_t* path);

/* Canonical Path */

jtk_Path_t* jtk_Path_getCanonicalPath(jtk_Path_t* path);

/* Create Directory */

bool jtk_Path_createDirectory(jtk_Path_t* path);
jtk_PathHandle_t* jtk_Path_createDirectoryEx(jtk_Path_t* path, int32_t flags);

/* Create File */

bool jtk_Path_createFile(jtk_Path_t* path);
jtk_PathHandle_t* jtk_Path_createFileEx(jtk_Path_t* path, int32_t flags);

/* Compare */

int32_t jtk_Path_compare(jtk_Path_t* path1, jtk_Path_t* path2);
/*
int32_t jtk_Path_compareEx(jtk_Path_t* path1, jtk_Path_t* path2,
    jtk_PathComparisonFlag_t flag) {
    jtk_Assert_assertObject(path1, "The specified first path is null.");
    jtk_Assert_assertObject(path2, "The specified second path is null.");

    int32_t result = 0;
    switch (flag) {
        case JTK_PATH_COMPARISON_FLAG_SIMPLE: {
            result = jtk_String_compare(path1->m_value, path1->m_valueSize,
                path2->m_value, path2->m_valueSize);

            break;
        }

        case JTK_PATH_COMPARISON_FLAG_ABSOLUTE: {
            /* Force the paths to cache in case the absolute paths have not been
             * evaluated yet.
             *
            jtk_Path_getAbsolutePathAsString(path1);
            jtk_Path_getAbsolutePathAsString(path2);
            result = jtk_String_compare(path1->m_absolutePath, path1->m_absolutePathSize,
                path2->m_absolutePath, path2->m_absolutePathSize);

            break;
        }

        case JTK_PATH_COMPARISON_FLAG_CANONICAL: {
            /* Force the paths to cache in case the canonical paths have not been
             * evaluated yet.
             *
            jtk_Path_getCanonicalPathAsString(path1);
            jtk_Path_getCanonicalPathAsString(path2);
            result = jtk_String_compare(path1->m_canonicalPath, path1->m_canonicalPathSize,
                path2->m_canonicalPath, path2->m_canonicalPathSize);

            break;
        }
    }
    return result;
}

*/

/* Element */

jtk_Path_t* jtk_Path_getElement(jtk_Path_t* path, int32_t index);

int32_t jtk_Path_countElements(jtk_Path_t* path);

/* Empty */

bool jtk_Path_isEmpty(jtk_Path_t* path);

/* Ends With */

bool jtk_Path_endsWith(jtk_Path_t* path, jtk_Path_t* suffix);

bool jtk_Path_endsWithEx(jtk_Path_t* path, jtk_Path_t* suffix, int32_t startIndex);

/* Extract */

jtk_Path_t* jtk_Path_extract(jtk_Path_t* path, int32_t startIndex, int32_t stopIndex);

/* Name */

uint8_t* jtk_Path_getName(jtk_Path_t* path) {
    jtk_Assert_assertObject(path, "The specified path is null.");
    /*
    int32_t index = jtk_String_findLast_c(path->m_value, JTK_PATH_ELEMENT_SEPARATOR);
    return (index < 0)?
        jtk_String_new(path->m_value) :
        jtk_String_substring(path->m_value, index + 1);
    */
}
/*
void jtk_Path_getNameEx(jtk_Path_t* path, jtk_StringBuilder_t* builder,
    int32_t index) {
    jtk_Assert_assertObject(path, "The specified path is null.");
    jtk_Assert_assertObject(builder, "The specified string builder is null.");
    /*
    int32_t separatorIndex = jtk_String_findLast_c(path->m_value, JTK_PATH_ELEMENT_SEPARATOR);
    if (index < 0) {
        jtk_StringBuilder_appendEx_z(builder, index, path->m_value);
    }
    else {
        jtk_StringBuilder_appendEx_z(builder, index, path->m_value + separatorIndex + 1);
    }
}
    */

/* Normalize */

jtk_Path_t* jtk_Path_normalize(jtk_Path_t* path);

/* Parent */

jtk_Path_t* jtk_Path_getParent(jtk_Path_t* path);

/* Rename */

bool jtk_Path_rename(jtk_Path_t* path, jtk_Path_t* destination);

/* Root */

jtk_Path_t* jtk_Path_getRoot(jtk_Path_t* path);

/* Starts With */

bool jtk_Path_startsWith(jtk_Path_t* path, jtk_Path_t* prefix);

bool jtk_Path_startsWithEx(jtk_Path_t* path, jtk_Path_t* prefix, int32_t startIndex);