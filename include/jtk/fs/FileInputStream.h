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

// Monday, May 06, 2019

#ifndef JTK_IO_FILE_INPUT_STREAM_H
#define JTK_IO_FILE_INPUT_STREAM_H

#include <jtk/Configuration.h>
#include <jtk/fs/PathHandle.h>
#include <jtk/io/InputStream.h>

/*******************************************************************************
 * FileInputStream                                                             *
 *******************************************************************************/

#define JTK_FILE_INPUT_STREAM_FLAG_REACHED_EOF (1 << 0)
#define JTK_FILE_INPUT_STREAM_FLAG_EXTERNAL_HANDLE (1 << 1)

/**
 * @class FileInputStream
 * @ingroup jtk_io
 * @author Samuel Rowe
 * @since JTK 1.1
 */
struct jtk_FileInputStream_t {
    jtk_InputStream_t* m_inputStream;
    jtk_PathHandle_t* m_handle;
    uint32_t m_flags;
};

/**
 * @memberof FileInputStream
 */
typedef struct jtk_FileInputStream_t jtk_FileInputStream_t;

// Constructor

/**
 * @memberof FileInputStream
 */
jtk_FileInputStream_t* jtk_FileInputStream_newFromString(const uint8_t* path);

/**
 * @memberof FileInputStream
 */
jtk_FileInputStream_t* jtk_FileInputStream_newFromPath(jtk_Path_t* path);

// Destructor

/**
 * @memberof FileInputStream
 */
void jtk_FileInputStream_delete(jtk_FileInputStream_t* stream);

// Available

/**
 * @memberof FileInputStream
 */
int32_t jtk_FileInputStream_getAvailable(jtk_FileInputStream_t* stream);

/**
 * @memberof FileInputStream
 */
bool jtk_FileInputStream_isAvailable(jtk_FileInputStream_t* stream);

// Close

/**
 * @memberof FileInputStream
 */
void jtk_FileInputStream_close(jtk_FileInputStream_t* stream);

// Read

/**
 * @memberof FileInputStream
 */
int32_t jtk_FileInputStream_read(jtk_FileInputStream_t* stream);

/**
 * @memberof FileInputStream
 */
int32_t jtk_FileInputStream_readBytes(jtk_FileInputStream_t* stream,
    uint8_t* buffer, int32_t size);

/**
 * @memberof FileInputStream
 */
int32_t jtk_FileInputStream_readBytesEx(jtk_FileInputStream_t* stream,
    uint8_t* buffer, int32_t size, int32_t startIndex, int32_t stopIndex);

// Skip

/**
 * @memberof FileInputStream
 */
int64_t jtk_FileInputStream_skip(jtk_FileInputStream_t* stream, int64_t count);

#endif /* JTK_IO_FILE_INPUT_STREAM_H */