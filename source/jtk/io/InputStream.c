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

// Saturday, May 04, 2019

#include <jtk/io/InputStream.h>

/*******************************************************************************
 * InputStream                                                                 *
 *******************************************************************************/

/* Constructor */

jtk_InputStream_t* jtk_InputStream_new(
    jtk_InputStream_ReadFunction_t read,
    jtk_InputStream_ReadBytesFunction_t readBytes,
    jtk_InputStream_ReadBytesExFunction_t readBytesEx,
    jtk_InputStream_SkipFunction_t skip,
    jtk_InputStream_GetAvailableFunction_t getAvailable,
    jtk_InputStream_IsAvailableFunction_t isAvailable,
    jtk_InputStream_DeleteFunction_t delete0,
    jtk_InputStream_CloseFunction_t close,
    void* implementation) {
    jtk_InputStream_t* stream = jtk_Memory_allocate(jtk_InputStream_t, 1);
    stream->m_read = read;
    stream->m_readBytes = readBytes;
    stream->m_readBytesEx = readBytesEx;
    stream->m_skip = skip;
    stream->m_getAvailable = getAvailable;
    stream->m_isAvailable = isAvailable;
    stream->m_delete = delete0;
    stream->m_close = close;
    stream->m_implementation = implementation;

    return stream;
}

/* Destructor */

void jtk_InputStream_delete(jtk_InputStream_t* stream) {
    jtk_Assert_assertObject(stream, "The specified input stream is null.");

    jtk_Memory_deallocate(stream);
}

/* Available */

int32_t jtk_InputStream_getAvailable(jtk_InputStream_t* stream) {
    jtk_Assert_assertObject(stream, "The specified input stream is null.");

    return stream->m_getAvailable(stream->m_implementation);
}

bool jtk_InputStream_isAvailable(jtk_InputStream_t* stream) {
    jtk_Assert_assertObject(stream, "The specified input stream is null.");
    
    return stream->m_isAvailable(stream->m_implementation);
}

/* Destroy */

/**
 * The jtk_InputStream_destroy() function triggers the destruction of the chain.
 * It does not actually delete the object. It is left to the implementation to
 * delete itself and destroy the source input stream.
 */
void jtk_InputStream_destroy(jtk_InputStream_t* stream) {
    jtk_Assert_assertObject(stream, "The specified input stream is null.");

    stream->m_delete(stream->m_implementation);
}

/* Close */

void jtk_InputStream_close(jtk_InputStream_t* stream) {
    jtk_Assert_assertObject(stream, "The specified input stream is null.");

    stream->m_close(stream->m_implementation);
}

/* Read */

int32_t jtk_InputStream_read(jtk_InputStream_t* stream) {
    jtk_Assert_assertObject(stream, "The specified input stream is null.");

    return stream->m_read(stream->m_implementation);
}

int32_t jtk_InputStream_readBytes(jtk_InputStream_t* stream, uint8_t* bytes,
    int32_t size) {
    jtk_Assert_assertObject(stream, "The specified input stream is null.");

    int32_t result;
    if (stream->m_readBytes != NULL) {
        result = stream->m_readBytes(stream->m_implementation, bytes, size);
    }
    else {
        result = jtk_InputStream_readBytesEx(stream, bytes, size, 0, size);
    }
    return result;
}

int32_t jtk_InputStream_readBytesEx(jtk_InputStream_t* stream, uint8_t* bytes,
    int32_t size, int32_t startIndex, int32_t stopIndex) {
    jtk_Assert_assertObject(stream, "The specified input stream is null.");

    int32_t result = -1;
    if (stream->m_readBytesEx != NULL) {
        result = stream->m_readBytesEx(stream->m_implementation, bytes, size, startIndex, stopIndex);
    }
    else {
        int32_t i;
        for (i = startIndex; i < stopIndex; i++) {
            int32_t c = stream->m_read(stream->m_implementation);
            if (c >= 0) {
                bytes[i] = (uint8_t)c;
            }
            else {
                break;
            }
        }
        result = i - startIndex;
    }
    return result;
}

/* Skip */

#define JTK_INPUT_STREAM_SKIP_BUFFER_SIZE 128

int64_t jtk_InputStream_skip(jtk_InputStream_t* stream, int64_t count) {
    jtk_Assert_assertObject(stream, "The specified input stream is null.");

    int64_t result = 0;
    if (stream->m_skip != NULL) {
        result = stream->m_skip(stream->m_implementation, count);
    }
    else {
        if (count > 0) {
            uint8_t buffer[JTK_INPUT_STREAM_SKIP_BUFFER_SIZE];
            int64_t remaining = count;
            while (remaining > 0) {
                int32_t read = stream->m_readBytes(stream->m_implementation, buffer, JTK_INPUT_STREAM_SKIP_BUFFER_SIZE);
                if (read < 0) {
                    break;
                }
                remaining -= read;
            }
            result = count - remaining;
        }
    }
    return result;
}