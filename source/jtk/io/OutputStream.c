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

// Friday, July 05, 2019

#include <jtk/io/OutputStream.h>

/*******************************************************************************
 * OutputStream                                                                *
 *******************************************************************************/

// Constructor

jtk_OutputStream_t* jtk_OutputStream_new(
    jtk_OutputStream_DeleteFunction_t delete0,
    jtk_OutputStream_CloseFunction_t close,
    jtk_OutputStream_FlushFunction_t flush,
    jtk_OutputStream_WriteFunction_t write,
    jtk_OutputStream_WriteBytesFunction_t writeBytes,
    jtk_OutputStream_WriteBytesExFunction_t writeBytesEx,
    void* implementation) {
    jtk_OutputStream_t* stream = jtk_Memory_allocate(jtk_OutputStream_t, 1);
    stream->m_implementation = implementation;
    stream->m_delete = delete0;
    stream->m_close = close;
    stream->m_flush = flush;
    stream->m_write = write;
    stream->m_writeBytes = writeBytes;
    stream->m_writeBytesEx = writeBytesEx;
    
    return stream;
}

// Destructor

void jtk_OutputStream_delete(jtk_OutputStream_t* stream) {
    jtk_Assert_assertObject(stream, "The specified output stream is null.");
    
    jtk_Memory_deallocate(stream);
}

/* Destroy */

/**
 * The jtk_OutputStream_destroy() function triggers the destruction of the chain.
 * It does not actually delete the object. It is left to the implementation to
 * delete itself and destroy the source input stream.
 */
void jtk_InputStream_destroy(jtk_OutputStream_t* stream) {
    jtk_Assert_assertObject(stream, "The specified output stream is null.");

    stream->m_delete(stream->m_implementation);
}

/* Close */

void jtk_OutputStream_close(jtk_OutputStream_t* stream) {
    jtk_Assert_assertObject(stream, "The specified output stream is null.");

    stream->m_close(stream->m_implementation);
}

/* Write */

void jtk_OutputStream_write(jtk_OutputStream_t* stream, uint8_t data) {
    jtk_Assert_assertObject(stream, "The specified output stream is null.");

    stream->m_write(stream->m_implementation, data);
}

void jtk_OutputStream_writeBytes(jtk_OutputStream_t* stream, uint8_t* data,
    int32_t size) {
    jtk_Assert_assertObject(stream, "The specified output stream is null.");


    if (stream->m_writeBytes != NULL) {
        stream->m_writeBytes(stream->m_implementation, data, size);
    }
    else {
        jtk_OutputStream_writeBytesEx(stream, data, size, 0, size);
    }
}

void jtk_OutputStream_writeBytesEx(jtk_OutputStream_t* stream, uint8_t* bytes,
    int32_t size, int32_t startIndex, int32_t stopIndex) {
    jtk_Assert_assertObject(stream, "The specified output stream is null.");

    if (stream->m_writeBytesEx != NULL) {
        stream->m_writeBytesEx(stream->m_implementation, bytes, size, startIndex,
            stopIndex);
    }
    else {
        int32_t i;
        for (i = startIndex; i < stopIndex; i++) {
            uint8_t byte = bytes[i];
            stream->m_write(stream->m_implementation, byte);
        }
    }
}