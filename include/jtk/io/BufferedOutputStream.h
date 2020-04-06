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

// Sunday, July 07, 2019

#ifndef JTK_IO_BUFFERED_OUTPUT_STREAM_H
#define JTK_IO_BUFFERED_OUTPUT_STREAM_H

/*******************************************************************************
 * BufferedOutputStream                                                        *
 *******************************************************************************/

/**
 * The cache hits are low and the cache misses are high when the input is small.
 * This behaviour inverses when the input is large, i.e., the cache hits are high
 * and the cache misses are low.
 *
 * @class BufferedOutputStream
 * @ingroup jtk_io
 * @author Samuel Rowe
 * @since JTK 1.1
 */
struct jtk_BufferedOutputStream_t {
    jtk_BufferedOutputStream_t* m_outputStream;
    jtk_BufferedOutputStream_t* m_targetOutputStream;
    uint8_t* m_buffer;
    int32_t m_size;
    int32_t m_capacity;
    int32_t m_cacheHits;
    int32_t m_cacheMisses;
};

/**
 * @memberof BufferedOutputStream
 */
typedef struct jtk_BufferedOutputStream_t jtk_BufferedOutputStream_t;

// Constructor

/**
 * @memberof BufferedOutputStream
 */
jtk_BufferedOutputStream_t* jtk_BufferedOutputStream_new(
    jtk_BufferedOutputStream_t* targetOutputStream);

/**
 * @memberof BufferedOutputStream
 */
jtk_BufferedOutputStream_t* jtk_BufferedOutputStream_newEx(
    jtk_BufferedOutputStream_t* targetOutputStream, int32_t capacity);

// Destructor

/**
 * @memberof BufferedOutputStream
 */
void jtk_BufferedOutputStream_delete(jtk_BufferedOutputStream_t* stream);


// Close

/**
 * @memberof BufferedOutputStream
 */
void jtk_BufferedOutputStream_close(jtk_BufferedOutputStream_t* stream);

// Flush

/**
 * @memberof BufferedOutputStream
 */
void jtk_BufferedOutputStream_flush(jtk_BufferedOutputStream_t* stream);

// Write

/**
 * @memberof BufferedOutputStream
 */
void jtk_BufferedOutputStream_write(jtk_BufferedOutputStream_t* stream,
    uint8_t byte);

/**
 * @memberof BufferedOutputStream
 */
void jtk_BufferedOutputStream_writeBytes(jtk_BufferedOutputStream_t* stream,
    uint8_t* bytes, int32_t size);

/**
 * @memberof BufferedOutputStream
 */
void jtk_BufferedOutputStream_writeBytesEx(jtk_BufferedOutputStream_t* stream,
    uint8_t* bytes, int32_t size, int32_t startIndex, int32_t stopIndex);


#endif /* JTK_IO_BUFFERED_OUTPUT_STREAM_H */