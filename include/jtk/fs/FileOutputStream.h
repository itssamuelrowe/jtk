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

#ifndef JTK_FS_FILE_OUTPUT_STREAM_H
#define JTK_FS_FILE_OUTPUT_STREAM_H

#include <jtk/Configuration.h>
#include <jtk/fs/PathHandle.h>
#include <jtk/io/OutputStream.h>

/*******************************************************************************
 * FileOutputStream                                                            *
 *******************************************************************************/

#define JTK_FILE_OUTPUT_STREAM_FLAG_EXTERNAL_HANDLE (1 << 0)

/**
 * @class FileOutputStream
 * @author Samuel Rowe
 * @since JTK 1.1
 * @ingroup jtk_fs
 */
struct jtk_FileOutputStream_t {
    jtk_OutputStream_t* m_outputStream;
    jtk_PathHandle_t* m_handle;
    uint32_t m_flags;
};

/**
 * @memberof FileOutputStream
 */
typedef struct jtk_FileOutputStream_t jtk_FileOutputStream_t;

// Constructor

/**
 * @memberof FileOutputStream
 */
jtk_FileOutputStream_t* jtk_FileOutputStream_newFromString(const uint8_t* path);

/**
 * @memberof FileOutputStream
 */
jtk_FileOutputStream_t* jtk_FileOutputStream_newFromPath(jtk_Path_t* path);

// Destructor

/**
 * @memberof FileOutputStream
 */
void jtk_FileOutputStream_delete(jtk_FileOutputStream_t* stream);

// Close

/**
 * @memberof FileOutputStream
 */
bool jtk_FileOutputStream_close(jtk_FileOutputStream_t* stream);

// Flush

/**
 * @memberof FileOutputStream
 */
bool jtk_FileOutputStream_flush(jtk_FileOutputStream_t* stream);

// Write

/**
 * @memberof FileOutputStream
 */
int32_t jtk_FileOutputStream_write(jtk_FileOutputStream_t* stream, uint8_t byte);

/**
 * @memberof FileOutputStream
 */
int32_t jtk_FileOutputStream_writeBytes(jtk_FileOutputStream_t* stream,
    uint8_t* bytes, int32_t size);

/**
 * @memberof FileOutputStream
 */
int32_t jtk_FileOutputStream_writeBytesEx(jtk_FileOutputStream_t* stream,
    uint8_t* bytes, int32_t size, int32_t startIndex, int32_t stopIndex);

#endif /* JTK_FS_FILE_OUTPUT_STREAM_H */