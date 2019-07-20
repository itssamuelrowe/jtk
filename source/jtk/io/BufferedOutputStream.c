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

// Sunday, July 07, 2019

#include <jtk/io/BufferedOutputStream.h>
#include <jtk/collection/array/Arrays.h>

/*******************************************************************************
 * BufferedOutputStream                                                        *
 *******************************************************************************/

// Constructor

#define JTK_BUFFERED_OUTPUT_STREAM_DEFAULT_CAPACITY 1024

#define jtk_BufferedOutputStream_recordCacheHit(stream) stream->m_cacheHits++
#define jtk_BufferedOutputStream_recordCacheMiss(stream) stream->m_cacheMisses++

jtk_BufferedOutputStream_t* jtk_BufferedOutputStream_new(
    jtk_BufferedOutputStream_t* targetOutputStream) {
    jtk_Assert_assertObject(targetOutputStream, "The specified target output stream is null.");
    
    return jtk_BufferedOutputStream_newEx(targetOutputStream,
        JTK_BUFFERED_OUTPUT_STREAM_DEFAULT_CAPACITY);
}

jtk_BufferedOutputStream_t* jtk_BufferedOutputStream_newEx(
    jtk_BufferedOutputStream_t* targetOutputStream, int32_t capacity) {
    jtk_BufferedOutputStream_t* stream = jtk_Memory_allocate(jtk_BufferedOutputStream_t, 1);
    stream->m_outputStream = jtk_OutputStream_new(
        jtk_BufferedOutputStream_delete,
        jtk_BufferedOutputStream_close,
        jtk_BufferedOutputStream_flush,
        jtk_BufferedOutputStream_write,
        jtk_BufferedOutputStream_writeBytes,
        jtk_BufferedOutputStream_writeBytesEx,
        stream
    );
    stream->m_targetOutputStream = targetOutputStream;
    stream->m_buffer = jtk_Memory_allocate(uint8_t, capacity);
    stream->m_size = 0;
    stream->m_capacity = capacity;
    stream->m_startIndex = -1;
    stream->m_stopIndex = -1;
    stream->m_cacheHits = 0;
    stream->m_cacheMisses = 0;
    
    return stream;
}

// Destructor

void jtk_BufferedOutputStream_delete(jtk_BufferedOutputStream_t* stream) {
    jtk_Assert_assertObject(stream, "The specified buffered output stream is null.");

    /* Destroy the target output stream. */
    jtk_OutputStream_destroy(stream->m_targetOutputStream);
    /* Delete the output stream corresponding to the buffered output stream.
     * The subtle difference between delete and destroy should be noted here.
     */
    jtk_OutputStream_delete(stream->m_outputStream);
    /* Deallocate the internal buffer. */
    jtk_Memory_deallocate(stream->m_buffer);
    /* Deallocate the buffered output stream. */
    jtk_Memory_deallocate(stream);
}

// Close

void jtk_BufferedOutputStream_close(jtk_BufferedOutputStream_t* stream) {
    jtk_Assert_assertObject(stream, "The specified buffered output stream is null.");
    
    jtk_OutputStream_close(stream->m_targetOutputStream);
}

// Flush

void jtk_BufferedOutputStream_flush0(jtk_BufferedOutputStream_t* stream) {
    if (stream->m_size > 0) {
        jtk_OutputStream_write(stream->m_targetOutputStream, stream->m_buffer, 0,
            stream->m_size);
        stream->m_size = 0;
        jtk_BufferedOutputStream_recordCacheMiss(stream);
    }
}

void jtk_BufferedOutputStream_flush(jtk_BufferedOutputStream_t* stream) {
    jtk_Assert_assertObject(stream, "The specified buffered output stream is null.");
    
    jtk_BufferedOutputStream_flush0(stream);
    jtk_OutputStream_flush(stream->m_targetOutputStream);
}

// Write

void jtk_BufferedOutputStream_write(jtk_BufferedOutputStream_t* stream,
    uint8_t byte) {
    jtk_Assert_assertObject(stream, "The specified buffered output stream is null.");
    
    if (stream->m_size >= stream->m_capacity) {
        jtk_BufferedOutputStream_flush0(stream);
    }
    stream->m_buffer[stream->m_size++] = byte;
}

void jtk_BufferedOutputStream_writeBytes(jtk_BufferedOutputStream_t* stream,
    uint8_t* bytes, int32_t size) {
    jtk_Assert_assertObject(stream, "The specified buffered output stream is null.");
    
    jtk_BufferedOutputStream_writeBytesEx(stream, bytes, size, 0, size);
}

void jtk_BufferedOutputStream_writeBytesEx(jtk_BufferedOutputStream_t* stream,
    uint8_t* bytes, int32_t size, int32_t startIndex, int32_t stopIndex) {
    jtk_Assert_assertObject(stream, "The specified buffered output stream is null.");
    
    /* Flush the buffer to the target output stream, when one of the following
     * conditions is true.
     *    - The internal buffer is full.
     *    - The size of the specified data is greater than the internal buffer.
     *    - The specified data cannot be copied to the internal buffer without
     *      overwriting other bytes.
     */
    bool oversized = (stream->m_capacity < size);
    if (oversized || (stream->m_size >= stream->m_capacity) ||
        ((stream->m_capacity - stream->m_size) < size)) {
        jtk_BufferedOutputStream_flush0(stream);
    }
    
    /* Write the data directly to the target output stream when it exceeds the
     * capacity of the internal buffer. In all other cases, the data is copied
     * to the internal buffer.
     */
    if (oversized) {
        jtk_OutputStream_writeBytesEx(stream->m_targetOutputStream, bytes, size,
            startIndex, stopIndex);
        jtk_BufferedOutputStream_recordCacheMiss(stream);
    }
    else {
        jtk_Arrays_copyEx_b(stream->m_buffer, stream->m_capacity, stream->m_size,
            bytes, size, startIndex, stopIndex - startIndex);
        jtk_BufferedOutputStream_recordCacheHit(stream);
    }
}