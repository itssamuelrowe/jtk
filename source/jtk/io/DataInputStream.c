// Monday, March 25, 2019

#include <jtk/core/Double.h>
#include <jtk/core/Float.h>
#include <jtk/core/Error.h>
#include <jtk/core/System.h>
#include <jtk/io/DataInputStream.h>

/*******************************************************************************
 * DataInputStream                                                             *
 *******************************************************************************/

/* Constructor */

jtk_DataInputStream_t* jtk_DataInputStream_new(jtk_InputStream_t* sourceInputStream) {
    jtk_Assert_assertObject(sourceInputStream, "The specified source input stream is null.");

    jtk_DataInputStream_t* stream = jtk_Memory_allocate(jtk_DataInputStream_t, 1);
    stream->m_inputStream = jtk_InputStream_new(
        jtk_DataInputStream_read,
        jtk_DataInputStream_readBytes,
        jtk_DataInputStream_readBytesEx,
        jtk_DataInputStream_skip,
        jtk_DataInputStream_getAvailable,
        jtk_DataInputStream_delete,
        jtk_DataInputStream_close,
        stream
    );
    stream->m_sourceInputStream = sourceInputStream;

    return stream;
}

/* Destructor */

void jtk_DataInputStream_delete(jtk_DataInputStream_t* stream) {
    jtk_Assert_assertObject(stream, "The specified buffered input stream is null.");

    /* Destroy the source input stream. */
    jtk_InputStream_destroy(stream->m_sourceInputStream);
    /* Delete the input stream corresponding to the buffered input stream.
     * The subtle difference between delete and destroy should be noted here.
     */
    jtk_InputStream_delete(stream->m_inputStream);
    /* Deallocate the buffered input stream. */
    jtk_Memory_deallocate(stream);
}

/* Available */

int32_t jtk_DataInputStream_getAvailable(jtk_DataInputStream_t* stream) {
    jtk_Assert_assertObject(stream, "The specified buffered input stream is null.");

    return jtk_InputStream_getAvailable(stream->m_sourceInputStream);
}

/* Close */

void jtk_DataInputStream_close(jtk_DataInputStream_t* stream) {
    jtk_Assert_assertObject(stream, "The specified buffered input stream is null.");

    jtk_InputStream_close(stream->m_sourceInputStream);
}

/* Read */

int32_t jtk_DataInputStream_read(jtk_DataInputStream_t* stream) {
    jtk_Assert_assertObject(stream, "The specified buffered input stream is null.");

    return jtk_InputStream_read(stream->m_sourceInputStream);
}

int32_t jtk_DataInputStream_readBytes(jtk_DataInputStream_t* stream, uint8_t* buffer, int32_t size) {
    jtk_Assert_assertObject(stream, "The specified buffered input stream is null.");

    return jtk_InputStream_readBytes(stream->m_sourceInputStream, buffer, size);
}

int32_t jtk_DataInputStream_readBytesEx(jtk_DataInputStream_t* stream,
    uint8_t* buffer, int32_t size, int32_t index, int32_t limit) {
    jtk_Assert_assertObject(stream, "The specified buffered input stream is null.");

    return jtk_InputStream_readBytesEx(stream->m_sourceInputStream, buffer, size, index, limit);
}

/* Read Data */

bool jtk_DataInputStream_readBoolean(jtk_DataInputStream_t* stream) {
    jtk_Assert_assertObject(stream, "The specified buffered input stream is null.");

    int32_t c = jtk_InputStream_read(stream->m_sourceInputStream);
    if (c < 0) {
        jtk_System_t* system = jtk_System_getInstance();
        jtk_System_setErrorEx(system, JTK_ERROR_END_OF_STREAM,
            JTK_ERROR_FLAG_SOURCE_LIBRARY);
    }
    return c != 0;
}

int8_t jtk_DataInputStream_readByte(jtk_DataInputStream_t* stream) {
    jtk_Assert_assertObject(stream, "The specified buffered input stream is null.");

    int32_t c = jtk_InputStream_read(stream->m_sourceInputStream);
    if (c < 0) {
        jtk_System_t* system = jtk_System_getInstance();
        jtk_System_setErrorEx(system, JTK_ERROR_END_OF_STREAM,
            JTK_ERROR_FLAG_SOURCE_LIBRARY);
    }
    return (int8_t)c;
}

int16_t jtk_DataInputStream_readShort(jtk_DataInputStream_t* stream) {
    jtk_Assert_assertObject(stream, "The specified buffered input stream is null.");

    int16_t result = -1;
    int32_t c1 = jtk_InputStream_read(stream->m_sourceInputStream);
    int32_t c2 = jtk_InputStream_read(stream->m_sourceInputStream);
    if ((c1 | c2) < 0) {
        jtk_System_t* system = jtk_System_getInstance();
        jtk_System_setErrorEx(system, JTK_ERROR_END_OF_STREAM,
            JTK_ERROR_FLAG_SOURCE_LIBRARY);
    }
    else {
        // result = (int16_t)((c1 << 8) | (c2 << 0));
        result = (int16_t)((c1 << 8) | c2);
    }
    return result;
}

/* NOTE: A faster implementation of this function would be to use a temporary
 * buffer. This avoids reading four times. Unfortunately, using a temporary buffer
 * comes with its own set of problems. For one, the jtk_InputStream_readBytes()
 * function does not gurantee to read four bytes at once. Checking for this
 * would lead to complex code.
 */
int32_t jtk_DataInputStream_readInteger(jtk_DataInputStream_t* stream) {
    jtk_Assert_assertObject(stream, "The specified buffered input stream is null.");

    int32_t result = -1;
    int32_t c1 = jtk_InputStream_read(stream->m_sourceInputStream);
    int32_t c2 = jtk_InputStream_read(stream->m_sourceInputStream);
    int32_t c3 = jtk_InputStream_read(stream->m_sourceInputStream);
    int32_t c4 = jtk_InputStream_read(stream->m_sourceInputStream);
    if ((c1 | c2 | c3 | c4) < result) {
        jtk_System_t* system = jtk_System_getInstance();
        jtk_System_setErrorEx(system, JTK_ERROR_END_OF_STREAM,
            JTK_ERROR_FLAG_SOURCE_LIBRARY);
    }
    else {
        // result = ((c1 << 24) | (c2 << 16) | (c3 << 8) | (c4 << 0));
        result = ((c1 << 24) | (c2 << 16) | (c3 << 8) | c4);
    }
    return result;
}

int64_t jtk_DataInputStream_readLong(jtk_DataInputStream_t* stream) {
    jtk_Assert_assertObject(stream, "The specified buffered input stream is null.");

    uint8_t buffer[8];
    bool success = jtk_InputStreamHelper_readFully(stream->m_sourceInputStream,
        buffer, 8);
    int64_t result = -1;
    if (success) {
        /*
        result = ((uint64_t)buffer[0] << 56) |
                 ((uint64_t)(buffer[1] & 0xFF) << 48) |
                 ((uint64_t)(buffer[2] & 0xFF) << 40) |
                 ((uint64_t)(buffer[3] & 0xFF) << 32) |
                 ((uint64_t)(buffer[4] & 0xFF) << 24) |
                 ((uint64_t)(buffer[5] & 0xFF) << 16) |
                 ((uint64_t)(buffer[6] & 0xFF) << 8) |
                 ((uint64_t)(buffer[7] & 0xFF) << 0);
        */
        result = ((uint64_t)buffer[0] << 56) |
                 ((uint64_t)(buffer[1] & 0xFF) << 48) |
                 ((uint64_t)(buffer[2] & 0xFF) << 40) |
                 ((uint64_t)(buffer[3] & 0xFF) << 32) |
                 ((uint64_t)(buffer[4] & 0xFF) << 24) |
                 ((uint64_t)(buffer[5] & 0xFF) << 16) |
                 ((uint64_t)(buffer[6] & 0xFF) << 8) |
                 ((uint64_t)(buffer[7] & 0xFF));
    }
    return result;
}

float jtk_DataInputStream_readFloat(jtk_DataInputStream_t* stream) {
    jtk_Assert_assertObject(stream, "The specified buffered input stream is null.");

    int32_t result = -1;
    int32_t c1 = jtk_InputStream_read(stream->m_sourceInputStream);
    int32_t c2 = jtk_InputStream_read(stream->m_sourceInputStream);
    int32_t c3 = jtk_InputStream_read(stream->m_sourceInputStream);
    int32_t c4 = jtk_InputStream_read(stream->m_sourceInputStream);
    if ((c1 | c2 | c3 | c4) < result) {
        jtk_System_t* system = jtk_System_getInstance();
        jtk_System_setErrorEx(system, JTK_ERROR_END_OF_STREAM,
            JTK_ERROR_FLAG_SOURCE_LIBRARY);
    }
    else {
        // result = ((c1 << 24) | (c2 << 16) | (c3 << 8) | (c4 << 0));
        result = ((c1 << 24) | (c2 << 16) | (c3 << 8) | c4);
    }
    return jtk_Float_pack(result);
}

double jtk_DataInputStream_readDouble(jtk_DataInputStream_t* stream) {
    jtk_Assert_assertObject(stream, "The specified buffered input stream is null.");

    uint8_t buffer[8];
    bool success = jtk_InputStreamHelper_readFully(stream->m_sourceInputStream,
        buffer, 8);
    int64_t result = -1;
    if (success) {
        /*
        result = ((uint64_t)buffer[0] << 56) |
                 ((uint64_t)(buffer[1] & 0xFF) << 48) |
                 ((uint64_t)(buffer[2] & 0xFF) << 40) |
                 ((uint64_t)(buffer[3] & 0xFF) << 32) |
                 ((uint64_t)(buffer[4] & 0xFF) << 24) |
                 ((uint64_t)(buffer[5] & 0xFF) << 16) |
                 ((uint64_t)(buffer[6] & 0xFF) << 8) |
                 ((uint64_t)(buffer[7] & 0xFF) << 0);
        */
        result = ((uint64_t)buffer[0] << 56) |
                 ((uint64_t)(buffer[1] & 0xFF) << 48) |
                 ((uint64_t)(buffer[2] & 0xFF) << 40) |
                 ((uint64_t)(buffer[3] & 0xFF) << 32) |
                 ((uint64_t)(buffer[4] & 0xFF) << 24) |
                 ((uint64_t)(buffer[5] & 0xFF) << 16) |
                 ((uint64_t)(buffer[6] & 0xFF) << 8) |
                 ((uint64_t)(buffer[7] & 0xFF));
    }
    return jtk_Double_pack(result);
}

/* Skip */

int64_t jtk_DataInputStream_skip(jtk_DataInputStream_t* stream, int64_t count) {
    jtk_Assert_assertObject(stream, "The specified input stream is null.");

    return jtk_InputStream_skip(stream->m_sourceInputStream, count);
}
