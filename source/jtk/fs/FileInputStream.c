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

// Sunday, May 05, 2019

#include <jtk/fs/FileInputStream.h>
#include <jtk/core/Error.h>
#include <jtk/core/System.h>

/*******************************************************************************
 * FileInputStreamFlag                                                         *
 *******************************************************************************/

bool jtk_FileInputStreamFlag_isExternalHandle(uint32_t flags) {
    return (flags & JTK_FILE_INPUT_STREAM_FLAG_EXTERNAL_HANDLE) != 0;
}

bool jtk_FileInputStreamFlag_hasReachedEOF(uint32_t flags) {
    return (flags & JTK_FILE_INPUT_STREAM_FLAG_REACHED_EOF) != 0;
}

/*******************************************************************************
 * FileInputStream                                                             *
 *******************************************************************************/

// Constructor

jtk_FileInputStream_t* jtk_FileInputStream_new0() {
    jtk_FileInputStream_t* stream = jtk_Memory_allocate(jtk_FileInputStream_t, 1);
    stream->m_inputStream = jtk_InputStream_new(
        jtk_FileInputStream_read,
        jtk_FileInputStream_readBytes,
        jtk_FileInputStream_readBytesEx,
        jtk_FileInputStream_skip,
        jtk_FileInputStream_getAvailable,
        jtk_FileInputStream_isAvailable,
        jtk_FileInputStream_delete,
        jtk_FileInputStream_close,
        stream
    );
    stream->m_flags = 0;

    return stream;
}

jtk_FileInputStream_t* jtk_FileInputStream_newFromString(const uint8_t* path) {
    jtk_Assert_assertObject(path, "The specified path is null.");

    jtk_FileInputStream_t* stream = jtk_FileInputStream_new0();
    stream->m_handle = jtk_PathHandle_newFromString(path);

    return stream;
}

jtk_FileInputStream_t* jtk_FileInputStream_newFromPath(jtk_Path_t* path) {
    jtk_Assert_assertObject(path, "The specified path is null.");

    jtk_FileInputStream_t* stream = jtk_FileInputStream_new0();
    stream->m_handle = jtk_PathHandle_newFromPath(path);

    return stream;
}

jtk_FileInputStream_t* jtk_FileInputStream_newFromHandle(jtk_PathHandle_t* handle) {
    jtk_Assert_assertObject(handle, "The specified path handle is null.");

    /* It should be noted that the read functions make sure that the handle is
     * open. Thus, it is assumed to be safe to use externally opened path handles.
     */
    jtk_FileInputStream_t* stream = jtk_FileInputStream_new0();
    stream->m_handle = handle;
    stream->m_flags = JTK_FILE_INPUT_STREAM_FLAG_EXTERNAL_HANDLE;

    return stream;
}

// Destructor
#include <stdio.h>
void jtk_FileInputStream_delete(jtk_FileInputStream_t* stream) {
    jtk_Assert_assertObject(stream, "The specified file input stream is null.");

    /* Close the file handle, if not closed, and destory it. */
    if (!jtk_FileInputStreamFlag_isExternalHandle(stream->m_flags) && (stream->m_handle != NULL)) {
        jtk_PathHandle_delete(stream->m_handle);
    }

    /* Delete the input stream corresponding to the file input stream.
     * The subtle difference between delete and destroy should be noted here.
     */
    jtk_InputStream_delete(stream->m_inputStream);

    /* Deallocate the file input stream. */
    jtk_Memory_deallocate(stream);
}

// Close

void jtk_FileInputStream_close(jtk_FileInputStream_t* stream) {
    jtk_Assert_assertObject(stream, "The specified file input stream is null.");

    jtk_PathHandle_close(stream->m_handle);
}

// Available

int32_t jtk_FileInputStream_getAvailable(jtk_FileInputStream_t* stream) {
    jtk_Assert_assertObject(stream, "The specified file input stream is null.");

    return 0;
}

bool jtk_FileInputStream_isAvailable(jtk_FileInputStream_t* stream) {
    jtk_Assert_assertObject(stream, "The specified file input stream is null.");

    return !jtk_FileInputStreamFlag_hasReachedEOF(stream->m_flags);
}

// Read

int32_t jtk_FileInputStream_read(jtk_FileInputStream_t* stream) {
    jtk_Assert_assertObject(stream, "The specified file input stream is null.");

    uint8_t buffer[1];
    int32_t result = jtk_FileInputStream_readBytesEx(stream, buffer, 1, 0, 1);

    return (result < 0)? -1 : buffer[0];
}

int32_t jtk_FileInputStream_readBytes(jtk_FileInputStream_t* stream,
    uint8_t* buffer, int32_t size) {
    jtk_Assert_assertObject(stream, "The specified file input stream is null.");
    jtk_Assert_assertObject(buffer, "The specified buffer is null.");
    jtk_Assert_assertTrue(size > 0, "The specified buffer size is invalid.");

    return jtk_FileInputStream_readBytesEx(stream, buffer, size, 0, size);
}

int32_t jtk_FileInputStream_readBytesEx(jtk_FileInputStream_t* stream,
    uint8_t* buffer, int32_t size, int32_t startIndex, int32_t stopIndex) {
    jtk_Assert_assertObject(stream, "The specified file input stream is null.");

    int32_t read = 0;
    if (!jtk_FileInputStreamFlag_hasReachedEOF(stream->m_flags)) {
        jtk_Error_t error = JTK_ERROR_INVALID_PATH_HANDLE;
        if (stream->m_handle != NULL) {
            error = JTK_ERROR_NONE;
            read = jtk_NativeFileHandle_readBytes(stream->m_handle->m_descriptor, buffer, size,
                startIndex, stopIndex, &error);

            if (read == 0) {
                stream->m_flags |= JTK_FILE_INPUT_STREAM_FLAG_REACHED_EOF;
            }
        }

        if (error != JTK_ERROR_NONE) {
            jtk_System_t* system = jtk_System_getInstance();
            jtk_System_setErrorEx(system, error, JTK_ERROR_FLAG_SOURCE_NATIVE);
            read = -1;
        }
    }

    return read;
}

// Skip

int64_t jtk_FileInputStream_skip(jtk_FileInputStream_t* stream, int64_t count) {
    jtk_Assert_assertObject(stream, "The specified file input stream is null.");
    jtk_Assert_assertTrue(count > 0, "The specified number of bytes to skip is invalid.");

    return jtk_NativeFileHandle_skip(stream->m_handle->m_descriptor, count);
}