// Tuesday, July 31, 2018

#ifndef JTK_IO_INPUT_STREAM_H
#define JTK_IO_INPUT_STREAM_H

#include <jtk/Configuration.h>

/*******************************************************************************
 * InputStream                                                                 *
 *******************************************************************************/

typedef int32_t (*jtk_InputStream_ReadFunction_t)(void* implementation);
typedef int32_t (*jtk_InputStream_ReadBytesFunction_t)(void* implementation, uint8_t* bytes, int32_t size);
typedef int32_t (*jtk_InputStream_ReadBytesExFunction_t)(void* implementation, uint8_t* bytes, int32_t size, int32_t index, int32_t limit);
typedef int64_t (*jtk_InputStream_SkipFunction_t)(void* implementation, int64_t count);
typedef int32_t (*jtk_InputStream_GetAvailableFunction_t)(void* implementation);
typedef void (*jtk_InputStream_DeleteFunction_t)(void* implementation);
typedef void (*jtk_InputStream_CloseFunction_t)(void* implementation);

/**
 * A stream represents a sequence of bytes flowing in a particular direction,
 * that is, either as input stream or output stream. A stream is considered as
 * an output stream if you are writing bytes to the stream. Similarly, a stream
 * is considered as an input stream if you are reading bytes from the stream.
 * In either case, streams are abstract in nature and may be associated with
 * files, sockets, strings, arrays, etc.
 *
 * The various input stream implementations support decoration pattern via
 * the chaining pattern. To understand the concepts of this pattern, assume two
 * different input stream implementations, j1 and j2. Suppose the stream j1 has
 * to be decorated by the stream j2, we require the implementation of j1 to
 * expose a raw input stream i1. This enables the stream j2 to interface the source
 * input stream to read data. Thus, multiple input stream implementations can be
 * chained and decorated.
 *
 * The `jtk_InputStream_t` structure declares function pointers that are required
 * to be "implemented" by an input stream variant.
 *
 * It should be noted that, when the head raw input stream is destroyed it
 * it triggers the destruction of the chain. The subsequent input streams in
 * the chain are destroyed recursively. Each input stream (raw and implementation)
 * is destroyed in the following order: the raw input stream is first destroyed,
 * followed by its implementation. Further, when an input stream is attached
 * to a chain, its destruction is handled by the head input stream, which has
 * to be manually deleted.
 *
 * @class InputStream
 * @ingroup jtk_io
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.1
 */
struct jtk_InputStream_t {
    jtk_InputStream_ReadFunction_t m_read;
    jtk_InputStream_ReadBytesFunction_t m_readBytes;
    jtk_InputStream_ReadBytesExFunction_t m_readBytesEx;
    jtk_InputStream_SkipFunction_t m_skip;
    jtk_InputStream_GetAvailableFunction_t m_getAvailable;
    jtk_InputStream_DeleteFunction_t m_delete;
    jtk_InputStream_CloseFunction_t m_close;
    void* m_implementation;
};

/**
 * @memberof InputStream
 */
typedef struct jtk_InputStream_t jtk_InputStream_t;
 
/* Constructor */

jtk_InputStream_t* jtk_InputStream_new(
    jtk_InputStream_ReadFunction_t read,
    jtk_InputStream_ReadBytesFunction_t readBytes,
    jtk_InputStream_ReadBytesExFunction_t readBytesEx,
    jtk_InputStream_SkipFunction_t skip,
    jtk_InputStream_GetAvailableFunction_t getAvailable,
    jtk_InputStream_DeleteFunction_t delete0,
    jtk_InputStream_CloseFunction_t close,
    void* implementation);

/* Destructor */

/**
 * @memberof 
 */
void jtk_InputStream_delete(jtk_InputStream_t* stream);

/* Available */

int32_t jtk_InputStream_getAvailable(jtk_InputStream_t* stream);

/* Destroy */

void jtk_InputStream_destroy(jtk_InputStream_t* stream);

/* Close */

void jtk_InputStream_close(jtk_InputStream_t* stream);

/* Read */

int32_t jtk_InputStream_read(jtk_InputStream_t* stream);

int32_t jtk_InputStream_readBytes(jtk_InputStream_t* stream, uint8_t* bytes, int32_t size);

int32_t jtk_InputStream_readBytesEx(jtk_InputStream_t* stream, uint8_t* bytes, int32_t size, int32_t index, int32_t limit);

/* Skip */

int64_t jtk_InputStream_skip(jtk_InputStream_t* stream, int64_t count);

#endif /* JTK_IO_INPUT_STREAM_H */