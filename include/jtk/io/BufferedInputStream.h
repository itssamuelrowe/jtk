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

#ifndef JTK_IO_BUFFERED_INPUT_STREAM_H
#define JTK_IO_BUFFERED_INPUT_STREAM_H

#include <jtk/Configuration.h>
#include <jtk/io/InputStream.h>

/*******************************************************************************
 * BufferedInputStream                                                         *
 *******************************************************************************/

/**
 * The cache hits are low and the cache misses are high when the input is small.
 * This behaviour inverses when the input is large, i.e., the cache hits are high
 * and the cache misses are low.
 *
 * @class BufferedInputStream
 * @ingroup jtk_io
 * @author Samuel Rowe
 * @since JTK 1.1
 */
struct jtk_BufferedInputStream_t {
    jtk_InputStream_t* m_inputStream;
    jtk_InputStream_t* m_sourceInputStream;
    uint8_t* m_buffer;
    int32_t m_size;
    int32_t m_capacity;
    int32_t m_startIndex;
    int32_t m_stopIndex;
    int32_t m_cacheHits;
    int32_t m_cacheMisses;
};

/**
 * @memberof BufferedInputStream
 */
typedef struct jtk_BufferedInputStream_t jtk_BufferedInputStream_t;

// Constructor

jtk_BufferedInputStream_t* jtk_BufferedInputStream_new(jtk_InputStream_t* sourceInputStream);

jtk_BufferedInputStream_t* jtk_BufferedInputStream_newEx(jtk_InputStream_t* sourceInputStream, int32_t capacity);

// Destructor

void jtk_BufferedInputStream_delete(jtk_BufferedInputStream_t* stream);

/* Available */

int32_t jtk_BufferedInputStream_getAvailable(jtk_BufferedInputStream_t* stream);

bool jtk_BufferedInputStream_isAvailable(jtk_BufferedInputStream_t* stream);

/* Close */

void jtk_BufferedInputStream_close(jtk_BufferedInputStream_t* stream);

/* Read */

int32_t jtk_BufferedInputStream_read(jtk_BufferedInputStream_t* stream);

int32_t jtk_BufferedInputStream_readBytes(jtk_BufferedInputStream_t* stream, uint8_t* bytes, int32_t size);

int32_t jtk_BufferedInputStream_readBytesEx(jtk_BufferedInputStream_t* stream, uint8_t* bytes, int32_t size, int32_t index, int32_t limit);

/* Skip */

int64_t jtk_BufferedInputStream_skip(jtk_BufferedInputStream_t* stream, int64_t count);

#endif /* JTK_IO_BUFFERED_INPUT_STREAM_H */