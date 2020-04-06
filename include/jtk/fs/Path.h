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

// Tuesday, July 31, 2018

#ifndef JTK_FS_PATH_H
#define JTK_FS_PATH_H

#include <jtk/Configuration.h>
#include <jtk/fs/PathHandle.h>

/**
 * @memberof Path
 */
typedef struct jtk_Path_t jtk_Path_t;

typedef bool (*jtk_Path_FilterFunction_t)(jtk_Path_t* path);

/*******************************************************************************
 * Path                                                                        *
 *******************************************************************************/

#define JTK_PATH_ELEMENT_SEPARATOR '/'

/**
 * @class Path
 * @ingroup jtk_fs
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since  JTK 1.1
 */
struct jtk_Path_t {
    uint8_t* m_value;
    int32_t m_valueSize;
};

/* Constructor */

/**
 * @memberof Path
 */
jtk_Path_t* jtk_Path_newFromString(const uint8_t* path);

/**
 * @memberof Path
 */
jtk_Path_t* jtk_Path_newFromStringEx(const uint8_t* path, int32_t size);

/**
 * @memberof Path
 */
jtk_Path_t* jtk_Path_newWithParentAndChild_zz(const uint8_t* parent, const uint8_t* child);

/**
 * @memberof Path
 */
jtk_Path_t* jtk_Path_newWithParentAndChild_oo(jtk_Path_t* parent, jtk_Path_t* child);

/**
 * @memberof Path
 */
jtk_Path_t* jtk_Path_newWithParentAndChild_oz(jtk_Path_t* parent, const uint8_t* child);

/**
 * @memberof Path
 */
jtk_Path_t* jtk_Path_newWithParentAndChild_zo(const uint8_t* parent, jtk_Path_t* child);

/* Destructor */

/**
 * @memberof Path
 */
void jtk_Path_delete(jtk_Path_t* path);

/* Absolute */

/**
 * @memberof Path
 */
bool jtk_Path_isAbsolute(jtk_Path_t* path);

jtk_Path_t* jtk_Path_getAbsolutePath(jtk_Path_t* path);

/* Canonical Path */

/**
 * @memberof Path
 */
jtk_Path_t* jtk_Path_getCanonicalPath(jtk_Path_t* path);

/* Create Directory */

bool jtk_Path_createDirectory(jtk_Path_t* path);
jtk_PathHandle_t* jtk_Path_createDirectoryEx(jtk_Path_t* path, int32_t flags);

/* Create File */

bool jtk_Path_createFile(jtk_Path_t* path);
jtk_PathHandle_t* jtk_Path_createFileEx(jtk_Path_t* path, int32_t flags);

/* Compare */

int32_t jtk_Path_compare(jtk_Path_t* path1, jtk_Path_t* path2);

/* Element */

/**
 * @memberof Path
 */
jtk_Path_t* jtk_Path_getElement(jtk_Path_t* path, int32_t index);

/**
 * @memberof Path
 */
int32_t jtk_Path_countElements(jtk_Path_t* path);

/* Empty */

/**
 * @memberof Path
 */
bool jtk_Path_isEmpty(jtk_Path_t* path);

/* Ends With */

/**
 * @memberof Path
 */
bool jtk_Path_endsWith(jtk_Path_t* path, jtk_Path_t* suffix);

/**
 * @memberof Path
 */
bool jtk_Path_endsWithEx(jtk_Path_t* path, jtk_Path_t* suffix, int32_t startIndex);

/* Extract */

/**
 * @memberof Path
 */
jtk_Path_t* jtk_Path_extract(jtk_Path_t* path, int32_t startIndex, int32_t stopIndex);

/* Name */

/**
 * @memberof Path
 */
// void jtk_Path_getName(jtk_Path_t* path, jtk_StringBuffer_t* buffer);
// void jtk_Path_getNameEx(jtk_Path_t* path, jtk_StringBuffer_t* buffer, int32_t index);

/* Normalize */

/**
 * @memberof Path
 */
jtk_Path_t* jtk_Path_normalize(jtk_Path_t* path);

/* Parent */

/**
 * @memberof Path
 */
jtk_Path_t* jtk_Path_getParent(jtk_Path_t* path);

/* Rename */

/**
 * @memberof Path
 */
bool jtk_Path_rename(jtk_Path_t* path, jtk_Path_t* destination);

/* Root */

/**
 * @memberof Path
 */
jtk_Path_t* jtk_Path_getRoot(jtk_Path_t* path);

/* Starts With */

/**
 * @memberof Path
 */
bool jtk_Path_startsWith(jtk_Path_t* path, jtk_Path_t* prefix);

/**
 * @memberof Path
 */
bool jtk_Path_startsWithEx(jtk_Path_t* path, jtk_Path_t* prefix, int32_t startIndex);

#endif /* JTK_FS_PATH_H */