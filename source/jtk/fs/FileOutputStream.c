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

// Monday, July 08, 2019

#include <jtk/core/Error.h>
#include <jtk/core/System.h>
#include <jtk/fs/FileOutputStream.h>

/*******************************************************************************
 * FileOutputStreamFlag                                                        *
 *******************************************************************************/

bool jtk_FileOutputStreamFlag_isExternalHandle(uint32_t flags) {
    return (flags & JTK_FILE_OUTPUT_STREAM_FLAG_EXTERNAL_HANDLE) != 0;
}

/*******************************************************************************
 * FileOutputStream                                                            *
 *******************************************************************************/

// Constructor

jtk_FileOutputStream_t* jtk_FileOutputStream_new0() {
    jtk_FileOutputStream_t* stream = jtk_Memory_allocate(jtk_FileOutputStream_t, 1);
    stream->m_outputStream = jtk_OutputStream_new(
        jtk_FileOutputStream_delete,
        jtk_FileOutputStream_close,
        jtk_FileOutputStream_flush,
        jtk_FileOutputStream_write,
        jtk_FileOutputStream_writeBytes,
        jtk_FileOutputStream_writeBytesEx,
        stream
    );
    stream->m_flags = 0;

    return stream;
}

jtk_FileOutputStream_t* jtk_FileOutputStream_newFromPath(jtk_Path_t* path) {
    jtk_Assert_assertObject(path, "The specified path is null.");

    jtk_FileOutputStream_t* stream = jtk_FileOutputStream_new0();
    stream->m_handle = jtk_PathHandle_newFromPath(path);

    return stream;
}

jtk_FileOutputStream_t* jtk_FileOutputStream_newFromHandle(jtk_PathHandle_t* handle) {
    jtk_Assert_assertObject(handle, "The specified path handle is null.");

    /* It should be noted that the write functions make sure that the handle is
     * open. Thus, it is assumed to be safe to use externally opened path handles.
     */
    jtk_FileOutputStream_t* stream = jtk_FileOutputStream_new0();
    stream->m_handle = handle;
    stream->m_flags = JTK_FILE_INPUT_STREAM_FLAG_EXTERNAL_HANDLE;

    return stream;
}

void jtk_FileOutputStream_delete(jtk_FileOutputStream_t* stream) {
    jtk_Assert_assertObject(stream, "The specified file output stream is null.");

    /* Close the file handle, if not closed, and destory it. */
    if (!jtk_FileOutputStreamFlag_isExternalHandle(stream->m_flags) &&
        (stream->m_handle != NULL)) {
        jtk_PathHandle_delete(stream->m_handle);
    }

    /* Delete the output stream corresponding to the file output stream.
     * The subtle difference between delete and destroy should be noted here.
     */
    jtk_OutputStream_delete(stream->m_outputStream);

    /* Deallocate the file output stream. */
    jtk_Memory_deallocate(stream);
}

// Close

void jtk_FileOutputStream_close(jtk_FileOutputStream_t* stream) {
    jtk_Assert_assertObject(stream, "The specified file output stream is null.");

    jtk_PathHandle_close(stream->m_handle);
}

// Flush

bool jtk_FileOutputStream_flush(jtk_FileOutputStream_t* stream) {
    jtk_Assert_assertObject(stream, "The specified file output stream is null.");

    bool result = false;
    if (stream->m_handle != NULL) {
        jtk_Error_t error = JTK_ERROR_NONE;
        jtk_NativeFileHandle_flush(stream->m_handle->m_descriptor, &error);
        if (error != JTK_ERROR_NONE) {
            jtk_System_t* system = jtk_System_getInstance();
            jtk_System_setErrorEx(system, error, JTK_ERROR_FLAG_SOURCE_NATIVE);
        }
        else {
            result = true;
        }
    }
    return result;
}

// Write

int32_t jtk_FileOutputStream_write(jtk_FileOutputStream_t* stream, uint8_t byte) {
    jtk_Assert_assertObject(stream, "The specified file output stream is null.");

    uint8_t buffer[] = { byte };
    return jtk_FileInputStream_writeBytesEx(stream, buffer, 1, 0, 1);
}

int32_t jtk_FileOutputStream_writeBytes(jtk_FileOutputStream_t* stream, uint8_t* bytes,
    int32_t size) {
    jtk_Assert_assertObject(stream, "The specified file output stream is null.");
    jtk_Assert_assertObject(bytes, "The specified buffer is null.");
    jtk_Assert_assertTrue(size > 0, "The specified buffer size is invalid.");

    return jtk_FileOutputStream_writeBytesEx(stream, bytes, size, 0, size);
}

int32_t jtk_FileOutputStream_writeBytesEx(jtk_FileOutputStream_t* stream,
    uint8_t* bytes, int32_t size, int32_t startIndex, int32_t stopIndex) {
    jtk_Assert_assertObject(stream, "The specified file output stream is null.");
    jtk_Assert_assertObject(bytes, "The specified buffer is null.");
    jtk_Assert_assertTrue(size > 0, "The specified buffer size is invalid.");
    jtk_Assert_assertTrue((startIndex >= 0) && (startIndex <= stopIndex), "The specified range is invalid.");

    jtk_Error_t error = JTK_ERROR_INVALID_PATH_HANDLE;
    int32_t written = -1;
    if (stream->m_handle != NULL) {
        error = JTK_ERROR_NONE;
        written = jtk_NativeFileHandle_writeBytes(stream->m_handle->m_descriptor,
            bytes, size, startIndex, stopIndex, &error);
    }

    if (error != JTK_ERROR_NONE) {
        jtk_System_t* system = jtk_System_getInstance();
        jtk_System_setErrorEx(system, error, JTK_ERROR_FLAG_SOURCE_NATIVE);
    }

    return written;
}