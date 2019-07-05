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

// Tuesday, July 31, 2018

#ifndef JTK_IO_OUTPUT_STREAM_H
#define JTK_IO_OUTPUT_STREAM_H

/*******************************************************************************
 * OutputStream                                                                *
 *******************************************************************************/

typedef void (jtk_OutputStream_DeleteFunction_t)(void* implementation);
typedef void (jtk_OutputStream_CloseFunction_t)(void* implementation);
typedef void (jtk_OutputStream_FlushFunction_t)(void* implementation);
typedef void (jtk_OutputStream_WriteFunction_t)(void* implementation, uint8_t byte);
typedef void (jtk_OutputStream_WriteBytesFunction_t)(void* implementation, uint8_t* data, int32_t size);
typedef void (jtk_OutputStream_WriteBytesExFunction_t)(void* implementation, uint8_t* data, int32_t size, int32_t startIndex, int32_t stopIndex);

/**
 * A stream represents a sequence of bytes flowing in a particular direction,
 * that is, either as input stream or output stream. A stream is considered as
 * an output stream if you are writing bytes to the stream. Similarly, a stream
 * is considered as an input stream if you are reading bytes from the stream.
 * In either case, a stream is abstract in nature and may be associated with
 * files, sockets, strings, arrays, etc.
 *
 * @class OutputStream
 * @ingroup jtk_io
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.1
 */
struct jtk_OutputStream_t {
    jtk_OutputStream_DeleteFunction_t m_delete;
    jtk_OutputStream_CloseFunction_t m_close;
    jtk_OutputStream_FlushFunction_t m_flush;
    jtk_OutputStream_WriteFunction_t m_write;
    jtk_OutputStream_WriteBytesFunction_t m_writeBytes;
    jtk_OutputStream_WriteBytesExFunction_t m_writeBytesEx;
    void* m_implementation;
};

/**
 * @memberof OutputStream
 */
typedef struct jtk_OutputStream_t jtk_OutputStream_t;
 
/* Constructor */

/**
 * @memberof OutputStream
 */
jtk_OutputStream_t* jtk_OutputStream_new(
    jtk_OutputStream_DeleteFunction_t delete0,
    jtk_OutputStream_CloseFunction_t close,
    jtk_OutputStream_FlushFunction_t flush,
    jtk_OutputStream_WriteFunction_t write,
    jtk_OutputStream_WriteBytesFunction_t writeBytes,
    jtk_OutputStream_WriteBytesExFunction_t writeBytesEx,
    void* implementation);

/* Destructor */

/**
 * @memberof OutputStream
 */
void jtk_OutputStream_delete(jtk_OutputStream_t* stream);

// Close

/**
 * @memberof OutputStream
 */
void jtk_OutputStream_close(jtk_OutputStream_t* stream);

// Destroy

/**
 * @memberof OutputStream
 */
void jtk_OutputStream_destroy(jtk_OutputStream_t* stream);

// Flush

/**
 * @memberof OutputStream
 */
void jtk_OutputStream_flush(jtk_OutputStream_t* stream);

// Write

/**
 * @memberof OutputStream
 */
void jtk_OutputStream_write(jtk_OutputStream_t* stream, uint8_t data);

/**
 * @memberof OutputStream
 */
void jtk_OutputStream_writeBytes(jtk_OutputStream_t* stream, uint8_t* data,
    int32_t size);

/**
 * @memberof OutputStream
 */
void jtk_OutputStream_writeBytesEx(jtk_OutputStream_t* stream, uint8_t* data,
    int32_t size, int32_t startIndex, int32_t stopIndex);
 
#endif /* JTK_IO_OUTPUT_STREAM_H */