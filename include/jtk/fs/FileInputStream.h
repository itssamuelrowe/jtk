// Monday, May 06, 2019

#ifndef JTK_IO_FILE_INPUT_STREAM_H
#define JTK_IO_FILE_INPUT_STREAM_H

#include <jtk/fs/PathHandle.h>
#include <jtk/io/InputStream.h>

/*******************************************************************************
 * FileInputStream                                                             *
 *******************************************************************************/

#define JTK_FILE_INPUT_STREAM_FLAG_EXTERNAL_HANDLE (1 << 0)

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

jtk_FileInputStream_t* jtk_FileInputStream_newFromString(const uint8_t* path);

jtk_FileInputStream_t* jtk_FileInputStream_newFromPath(jtk_Path_t* path);

// Destructor

void jtk_FileInputStream_delete(jtk_FileInputStream_t* stream);

// Available

int32_t jtk_FileInputStream_getAvailable(jtk_FileInputStream_t* stream);

// Close

void jtk_FileInputStream_close(jtk_FileInputStream_t* stream);

// Read

int32_t jtk_FileInputStream_read(jtk_FileInputStream_t* stream);

int32_t jtk_FileInputStream_readBytes(jtk_FileInputStream_t* stream,
    uint8_t* buffer, int32_t size);

int32_t jtk_FileInputStream_readBytesEx(jtk_FileInputStream_t* stream,
    uint8_t* buffer, int32_t size, int32_t startIndex, int32_t stopIndex);

// Skip

int64_t jtk_FileInputStream_skip(jtk_FileInputStream_t* stream, int64_t count);

#endif /* JTK_IO_FILE_INPUT_STREAM_H */