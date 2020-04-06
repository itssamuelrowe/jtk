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

// Monday, May 06, 2019

#include <com/onecube/jtk/fs/NativeFileHandle.h>
#include <jtk/core/CString.h>
#include <jtk/core/Error.h>
#include <jtk/core/System.h>
#include <jtk/fs/Path.h>
#include <jtk/fs/PathHandle.h>
#include <jtk/collection/array/Arrays.h>

/*******************************************************************************
 * PathHandle                                                                  *
 *******************************************************************************/

jtk_PathHandle_t* jtk_PathHandle_newFromString(const uint8_t* path) {
    jtk_Assert_assertObject(path, "The specified path is null.");

    jtk_Error_t error = JTK_ERROR_NONE;
    int64_t descriptor = jtk_NativeFileHandle_open(path, &error);

    jtk_PathHandle_t* handle = NULL;
    if (error != JTK_ERROR_NONE) {
        jtk_System_t* system = jtk_System_getInstance();
        jtk_System_setErrorEx(system, error, JTK_ERROR_FLAG_SOURCE_NATIVE);
    }
    else {
        handle = jtk_Memory_allocate(jtk_PathHandle_t, 1);
        handle->m_path = jtk_Path_newFromString(path);
        handle->m_descriptor = descriptor;
    }

    return handle;
}

jtk_PathHandle_t* jtk_PathHandle_newFromStringEx(const uint8_t* path, int32_t size) {
    jtk_Assert_assertObject(path, "The specified path is null.");

    jtk_Error_t error = JTK_ERROR_NONE;
    int64_t descriptor = jtk_NativeFileHandle_open(path, &error);

    jtk_PathHandle_t* handle = NULL;
    if (error != JTK_ERROR_NONE) {
        jtk_System_t* system = jtk_System_getInstance();
        jtk_System_setErrorEx(system, error, JTK_ERROR_FLAG_SOURCE_NATIVE);
    }
    else {
        handle = jtk_Memory_allocate(jtk_PathHandle_t, 1);
        handle->m_path = jtk_Path_newFromStringEx(path, size);
        handle->m_descriptor = descriptor;
    }

    return handle;
}

jtk_PathHandle_t* jtk_PathHandle_newFromPath(jtk_Path_t* path) {
    jtk_Assert_assertObject(path, "The specified path is null.");

    return jtk_PathHandle_newFromStringEx(path->m_value, path->m_valueSize);
}

jtk_PathHandle_t* jtk_PathHandle_forDirectoryEx(const uint8_t* path, int32_t size) {
    jtk_Assert_assertObject(path, "The specified path is null.");

    jtk_Error_t error = JTK_ERROR_NONE;
    int64_t descriptor = jtk_NativeFileHandle_openDirectory(path, &error);

    jtk_PathHandle_t* handle = NULL;
    if (error != JTK_ERROR_NONE) {
        jtk_System_t* system = jtk_System_getInstance();
        jtk_System_setErrorEx(system, error, JTK_ERROR_FLAG_SOURCE_NATIVE);
    }
    else {
        handle = jtk_Memory_allocate(jtk_PathHandle_t, 1);
        handle->m_path = jtk_Path_newFromStringEx(path, size);
        handle->m_descriptor = descriptor;
    }

    return handle;
}

jtk_PathHandle_t* jtk_PathHandle_forDirectory(jtk_Path_t* path) {
    jtk_Assert_assertObject(path, "The specified path is null.");

    return jtk_PathHandle_forDirectoryEx(path->m_value, path->m_valueSize);
}

// Destructor

void jtk_PathHandle_delete(jtk_PathHandle_t* handle) {
    jtk_Assert_assertObject(handle, "The specified path handle is null.");

    if (handle->m_descriptor >= 0) {
        jtk_NativeFileHandle_close(handle->m_descriptor, NULL);
    }

    jtk_Path_delete(handle->m_path);

    jtk_Memory_deallocate(handle);
}

// Close

void jtk_PathHandle_close(jtk_PathHandle_t* handle) {
    jtk_Assert_assertObject(handle, "The specified path handle is null.");

    if (handle->m_descriptor >= 0) {
        jtk_Error_t error = JTK_ERROR_NONE;
        jtk_NativeFileHandle_close(handle->m_descriptor, &error);
        if (error != JTK_ERROR_NONE) {
            jtk_System_t* system = jtk_System_getInstance();
            jtk_System_setErrorEx(system, error, JTK_ERROR_FLAG_SOURCE_NATIVE);
        }
        handle->m_descriptor = -1;
    }
}

// Directory

bool jtk_PathHandle_isDirectory(jtk_PathHandle_t* handle) {
    jtk_Assert_assertObject(handle, "The specified path handle is null.");

    jtk_System_t* system = jtk_System_getInstance();
    bool result = false;
    if (handle->m_descriptor >= 0) {
        jtk_Error_t error = JTK_ERROR_NONE;
        result = jtk_NativeFileHandle_isDirectory(handle->m_descriptor, &error);
        if (error != JTK_ERROR_NONE) {
            jtk_System_setErrorEx(system, error, JTK_ERROR_FLAG_SOURCE_NATIVE);
        }
    }
    else {
        jtk_System_setErrorEx(system, JTK_ERROR_INVALID_PATH_HANDLE, JTK_ERROR_FLAG_SOURCE_LIBRARY);
    }
    return result;
}

// Regular File

bool jtk_PathHandle_isRegularFile(jtk_PathHandle_t* handle) {
    jtk_Assert_assertObject(handle, "The specified path handle is null.");

    jtk_System_t* system = jtk_System_getInstance();
    bool result = false;
    if (handle->m_descriptor >= 0) {
        jtk_Error_t error = JTK_ERROR_NONE;
        result = jtk_NativeFileHandle_isRegularFile(handle->m_descriptor, &error);
        if (error != JTK_ERROR_NONE) {
            jtk_System_setErrorEx(system, error, JTK_ERROR_FLAG_SOURCE_NATIVE);
        }
    }
    else {
        jtk_System_setErrorEx(system, JTK_ERROR_INVALID_PATH_HANDLE, JTK_ERROR_FLAG_SOURCE_LIBRARY);
    }
    return result;
}