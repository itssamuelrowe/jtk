// Friday, May 03, 2019

#ifndef JTK_FS_PATH_HANDLE_H
#define JTK_FS_PATH_HANDLE_H

#include <jtk/Configuration.h>
#include <jtk/collection/array/Array.h>

typedef struct jtk_Path_t jtk_Path_t;
 
typedef bool (*jtk_Path_FilterFunction_t)(jtk_Path_t* path);

/*******************************************************************************
 * PathHandle                                                                  *
 *******************************************************************************/

/**
 * @class PathHandle
 * @author Samuel Rowe
 * @since JTK 1.1
 * @ingroup jtk_fs
 */
struct jtk_PathHandle_t {
    jtk_Path_t* m_path;
    void* m_descriptor;
};

typedef struct jtk_PathHandle_t jtk_PathHandle_t;

// Constructor

// Has some bug!!!
jtk_PathHandle_t* jtk_PathHandle_newFromPath(jtk_Path_t* path);

jtk_PathHandle_t* jtk_PathHandle_newFromString(const uint8_t* path);

// Destructor

void jtk_PathHandle_delete(jtk_PathHandle_t* handle);

/* Directory */

/**
 * @memberof PathHandle
 */
bool jtk_PathHandle_isDirectory(jtk_PathHandle_t* handle);

/* Exists */

/**
 * @memberof PathHandle
 */
bool jtk_PathHandle_exists(jtk_PathHandle_t* handle);

/* Regular File */

/**
 * @memberof PathHandle
 */
bool jtk_PathHandle_isRegularFile(jtk_PathHandle_t* handle);

/* Hidden */

/**
 * @memberof PathHandle
 */
bool jtk_PathHandle_isHidden(jtk_PathHandle_t* handle);

/* Last Modified Time */

/**
 * @memberof PathHandle
 */
int64_t jtk_PathHandle_getLastModifiedTime(jtk_PathHandle_t* handle);

/**
 * @memberof PathHandle
 */
void jtk_PathHandle_setLastModifiedTime(jtk_PathHandle_t* handle,
    int64_t lastModifiedTime);

/* List */

jtk_Array_t* jtk_PathHandle_list(jtk_PathHandle_t* handle);

jtk_Array_t* jtk_PathHandle_listEx(jtk_PathHandle_t* handle, jtk_Path_FilterFunction_t filter);

/* Readable */

/**
 * @memberof PathHandle
 */
bool jtk_PathHandle_isReadable(jtk_PathHandle_t* handle);

/**
 * @memberof PathHandle
 */
bool jtk_PathHandle_setReadable(jtk_PathHandle_t* handle, bool readable);

/* Size */

int64_t jtk_PathHandle_getSize(jtk_PathHandle_t* handle);

/* Symbolic Link */

bool jtk_PathHandle_isSymbolicLink(jtk_PathHandle_t* handle);

/* Writable */

/**
 * @memberof PathHandle
 */
bool jtk_PathHandle_isWritable(jtk_PathHandle_t* path);

/**
 * @memberof PathHandle
 */
bool jtk_PathHandle_setWritable(jtk_PathHandle_t* path, bool writable);

#endif /* JTK_FS_PATH_HANDLE_H */