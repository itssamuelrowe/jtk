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

#include <jtk/io/BufferedInputStream.h>
#include <jtk/collection/array/Arrays.h>

/*******************************************************************************
 * BufferedInputStream                                                         *
 *******************************************************************************/

// Constructor

#define JTK_BUFFERED_INPUT_STREAM_DEFAULT_CAPACITY 1024

#define jtk_BufferedInputStream_recordCacheHit(stream) stream->m_cacheHits++
#define jtk_BufferedInputStream_recordCacheMiss(stream) stream->m_cacheMisses++

jtk_BufferedInputStream_t* jtk_BufferedInputStream_new(
    jtk_InputStream_t* sourceInputStream) {
    jtk_Assert_assertObject(sourceInputStream, "The specified source input stream is null.");

    return jtk_BufferedInputStream_newEx(sourceInputStream, JTK_BUFFERED_INPUT_STREAM_DEFAULT_CAPACITY);
}

jtk_BufferedInputStream_t* jtk_BufferedInputStream_newEx(
    jtk_InputStream_t* sourceInputStream, int32_t capacity) {
    jtk_BufferedInputStream_t* stream = jtk_Memory_allocate(jtk_BufferedInputStream_t, 1);
    stream->m_inputStream = jtk_InputStream_new(
        jtk_BufferedInputStream_read,
        jtk_BufferedInputStream_readBytes,
        jtk_BufferedInputStream_readBytesEx,
        jtk_BufferedInputStream_skip,
        jtk_BufferedInputStream_getAvailable,
        jtk_BufferedInputStream_isAvailable,
        jtk_BufferedInputStream_delete,
        jtk_BufferedInputStream_close,
        stream
    );
    stream->m_sourceInputStream = sourceInputStream;
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

void jtk_BufferedInputStream_delete(jtk_BufferedInputStream_t* stream) {
    jtk_Assert_assertObject(stream, "The specified buffered input stream is null.");

    /* Destroy the source input stream. */
    jtk_InputStream_destroy(stream->m_sourceInputStream);
    /* Delete the input stream corresponding to the buffered input stream.
     * The subtle difference between delete and destroy should be noted here.
     */
    jtk_InputStream_delete(stream->m_inputStream);
    /* Deallocate the internal buffer. */
    jtk_Memory_deallocate(stream->m_buffer);
    /* Deallocate the buffered input stream. */
    jtk_Memory_deallocate(stream);
}

// Available

int32_t jtk_BufferedInputStream_getAvailable(jtk_BufferedInputStream_t* stream) {
    jtk_Assert_assertObject(stream, "The specified buffered input stream is null.");

    return stream->m_size;
}

bool jtk_BufferedInputStream_isAvailable(jtk_BufferedInputStream_t* stream) {
    jtk_Assert_assertObject(stream, "The specified buffered input stream is null.");

    /* The underlying input stream may have already hit end-of-stream. But a few
     * bytes may be in the buffer. Therefore, make sure to test both the buffer
     * and the underlying input stream, in that order.
     */
    return (stream->m_size > 0) || jtk_InputStream_isAvailable(stream->m_sourceInputStream);
}

// Buffer

/* The various range forms the internal buffer indexes take are as follows.
 *    startIndex = stopIndex < capacity
 *        -- This range indicates that the internal buffer is empty.
 *    startIndex < stopIndex < capacity
 *        -- This range indicates that there exists one valid data range,
 *           between startIndex and stopIndex.
 *    stopIndex < startIndex < capacity
 *        -- This range indicates that there exists two valid data ranges,
 *           and are of the form [startIndex, capacity) and [0, stopIndex).
 */

int32_t jtk_BufferedInputStream_bufferWithLimit(jtk_BufferedInputStream_t* stream,
    int32_t limit) {
    int32_t newLimit = limit;
    while (newLimit > 0) {
        int32_t read = jtk_InputStream_readBytesEx(stream->m_sourceInputStream,
            stream->m_buffer, stream->m_capacity, stream->m_stopIndex, newLimit);
        if (read < 0) {
            break;
        }
        stream->m_stopIndex += read;
        stream->m_size += read;
        newLimit -= read;
    }
    return limit - newLimit;
}
#include <stdio.h>
void jtk_BufferedInputStream_buffer(jtk_BufferedInputStream_t* stream) {
    jtk_Assert_assertObject(stream, "The specified buffered input stream is null.");

    /* The stream makes no attempt to read from the source input stream, if the
     * buffer is full. The implementation input stream requires the
     * available data to be read before it attempts to read from the source
     * input stream.
     */
    if (stream->m_size < stream->m_capacity) {
        int32_t read = 0;
        /* If the usage of the buffer is zero, then reset the start and stop
         * indexes to zero. It should be noted that the indexes are not checked
         * because they are possibly stale.
         */
        if (stream->m_size == 0) {
            stream->m_startIndex = 0;
            stream->m_stopIndex = 0;
            /* Keep the start index as it is. Read and update the stop index
             * until the end-of-stream is reached or the buffer is completely
             * filled.
             */
            jtk_BufferedInputStream_bufferWithLimit(stream, stream->m_capacity);
        }
        else if (stream->m_startIndex < stream->m_stopIndex) {
            /* At this point, there are two empty regions in the internal buffer.
             * - The first region starts from 0 and extends to the start index.
             * - The second region starts from the stop index and extends to the
             * the maxium index of the buffer.
             *
             * Therefore, fill the second empty region and update the stop index,
             * if the buffer is empty in the beginning.
             */

            int32_t limit = stream->m_capacity - stream->m_stopIndex;
            int32_t read = 0;
            if (limit > 0) {
                read = jtk_BufferedInputStream_bufferWithLimit(stream, limit);
            }

            /* If the number of bytes read is equal to the limit, the stop index
             * has reached the maximum index. It can be reset to 0 if the start
             * index is greater than 0, i.e., some bytes in the beginning
             * are stale. The actual data buffering task is delegated.
             */
            if ((read == limit) && (stream->m_startIndex > 0)) {
                stream->m_stopIndex = 0;
            }
        }

        /* If the stop index is leser than the start index, there is a free region
         * at the beginning of the buffer. Therefore, make an attempt to fill
         * the buffer.
         */
        if (stream->m_stopIndex < stream->m_startIndex) {
            int32_t limit = stream->m_startIndex - stream->m_stopIndex;
            jtk_BufferedInputStream_bufferWithLimit(stream, limit);
        }
    }
}

// Close

void jtk_BufferedInputStream_close(jtk_BufferedInputStream_t* stream) {
    jtk_Assert_assertObject(stream, "The specified buffered input stream is null.");

    jtk_InputStream_close(stream->m_sourceInputStream);
}

// Empty

bool jtk_BufferedInputStream_isBufferEmpty(jtk_BufferedInputStream_t* stream) {
    jtk_Assert_assertObject(stream, "The specified buffered input stream is null.");

    return stream->m_size == 0;
}

// Full

bool jtk_BufferedInputStream_isBufferFull(jtk_BufferedInputStream_t* stream) {
    jtk_Assert_assertObject(stream, "The specified buffered input stream is null.");

    return stream->m_size == stream->m_capacity;
}

// Read

int32_t jtk_BufferedInputStream_read(jtk_BufferedInputStream_t* stream) {
    jtk_Assert_assertObject(stream, "The specified buffered input stream is null.");

    // printf("(start = %d, stop = %d)\n", stream->m_startIndex, stream->m_stopIndex);

    /* If the buffer is empty, then fill the buffer. */
    if (stream->m_size == 0) {
        jtk_BufferedInputStream_recordCacheMiss(stream);
        jtk_BufferedInputStream_buffer(stream);
    }
    else {
        jtk_BufferedInputStream_recordCacheHit(stream);
    }

    int32_t result = -1;
    /* If the buffer is still empty, then return -1 because the implementation
     * has encountered an end-of-stream. It should be noted that the source
     * input stream may have reached end-of-stream long back.
     */
    if (stream->m_size != 0) {

        result = stream->m_buffer[stream->m_startIndex];
        /* The start index is incremented by 1 if the sum is less than the capacity
         * of the internal buffer. If the new start index is equal to the stop
         * index, then the buffer is empty.
         */
        if ((stream->m_startIndex + 1) < stream->m_capacity) {
            stream->m_startIndex++;
        }
        else {
            /* Otherwise, the start index is reset to 0. If the stop index is
             * at 0, then the buffer is empty.
             */
            stream->m_startIndex = 0;
        }
        stream->m_size--;
    }
    return result;
}

int32_t jtk_BufferedInputStream_readBytes(jtk_BufferedInputStream_t* stream, uint8_t* bytes,
    int32_t size) {
    jtk_Assert_assertObject(stream, "The specified buffered input stream is null.");

    return jtk_InputStream_readBytesEx(stream, bytes, size, 0, size);
}

/* When the internal buffer size is small, this function fails to be efficient.
 * For a larger destination buffer, the data from the source input stream is
 * buffered and then immediately copied into the destination buffer. Further,
 * the source input stream is requested for data multiple times, which results
 * in an inefficient read and delay.
 */
int32_t jtk_BufferedInputStream_readBytesEx(jtk_BufferedInputStream_t* stream,
    uint8_t* bytes, int32_t size, int32_t startIndex, int32_t stopIndex) {
    jtk_Assert_assertObject(stream, "The specified buffered input stream is null.");

    // printf("(start = %d, stop = %d)", stream->m_startIndex, stream->m_stopIndex);

    int32_t limit = stopIndex - startIndex;
    int32_t newLimit = limit;
    while (newLimit > 0) {
        /* If the buffer is empty, then fill the buffer. */
        if (stream->m_size == 0) {
            jtk_BufferedInputStream_recordCacheMiss(stream);
            jtk_BufferedInputStream_buffer(stream);
        }
        else {
            jtk_BufferedInputStream_recordCacheHit(stream);
        }

        /* The number of bytes read in this iteration. */
        int32_t read;

        /* If the buffer is still empty, then return terminate the loop because
         * the implementation has encountered an end-of-stream. It should be
         * noted that the source input stream may have reached end-of-stream
         * long back.
         */
        if (stream->m_size != 0) {

            /* When the start index is lesser than the stop index, the data
             * between these indexes should be read. Otherwise, the data
             * between the start index and the maximum index should be read.
             * If there is a valid data region at the beginning of the buffer,
             * it is read in the next iteration where the start index is updated.
             */
            int32_t upperLimit = (stream->m_startIndex < stream->m_stopIndex)?
                stream->m_stopIndex : stream->m_capacity;
            /* The maximum number of bytes that can be read in this iteration. */
            int32_t readableBytes = upperLimit - stream->m_startIndex;
            /* The number of bytes that should be read in this iteration.
             * Since, data cannot be read beyond the stop index of the destination
             * buffer the number of bytes to be read is limited accordingly.
             */
            read = jtk_Integer_min(readableBytes, stopIndex);
            /* Read the data available beginning at the start index and upper
             * limit, if the data fits into the destination buffer. Otherwise,
             * read the required number of bytes.
             */
            jtk_Arrays_copyEx_b(stream->m_buffer, stream->m_capacity,
                stream->m_startIndex, bytes, size, startIndex, read);
        }
        else {
            /* The implementation has reached the end-of-stream. */
            break;
        }

        /* The start index is incremented by the number of bytes read in this
         * iteration, if the sum is less than the capacity of the internal buffer.
         * If the new start index is equal to the stop index, then the buffer is
         * empty.
         */
        if ((stream->m_startIndex + read) < stream->m_capacity) {
            stream->m_startIndex += read;
        }
        else {
            /* Otherwise, the start index is reset to 0. If the stop index is at
             * 0, then the buffer is empty.
             */
            stream->m_startIndex = 0;
        }

        newLimit -= read;
        stream->m_size -= read;
        /* Update the start index of the destination buffer. */
        startIndex += read;
    }
    return limit - newLimit;
}

// Skip

int64_t jtk_BufferedInputStream_skip(jtk_BufferedInputStream_t* stream, int64_t count) {
    jtk_Assert_assertObject(stream, "The specified buffered input stream is null.");
    jtk_Assert_assertTrue(count > 0, "The specified number of bytes to skip is invalid.");

    /* The total number of bytes to be skipped. */
    int32_t newCount = count;

    /* If the stop index is less than the start index, valid data exists in two
     * regions. The regions are as follows: [startIndex, capacity) and [0, stopIndex).
     * In this section, the first region is handled and the start index is automatically
     * adjusted so the subsequent segments can efficiently handle the second region.
     */
    if (stream->m_stopIndex < stream->m_startIndex) {
        /* The skip count may be higher than the total number of bytes available
         * in the internal buffer. Therefore, limit the count correspondingly.
         */
        int32_t limit = jtk_Integer_min(stream->m_capacity - stream->m_startIndex,
            count);
        /* Increment the start index by the number of bytes to be skipped. This
         * is where the skipping magic happens!
         */
        stream->m_startIndex += limit;
        /* Decrement the usage of the internal buffer. */
        stream->m_size -= limit;
        /* Determine the number of bytes yet to be skipped. */
        newCount -= limit;

        /* The start index is incremented by the number of bytes skipped previously.
         * If the new start index is equal to the capacity, then the start index
         * is reset to 0.
         */
        if (stream->m_startIndex == stream->m_capacity) {
            stream->m_startIndex = 0;
        }
    }

    /* If the start index is less than the stop index, valid data exists. */
    if ((stream->m_startIndex < stream->m_stopIndex) && (newCount > 0)) {
        /* The skip count may be higher than the total number of bytes available
         * in the internal buffer. Therefore, limit the count correspondingly.
         */
        int32_t limit = jtk_Integer_min(stream->m_stopIndex - stream->m_startIndex,
            count);
        /* Increment the start index by the number of bytes to be skipped. This
         * is where the skipping magic happens!
         */
        stream->m_startIndex += limit;
        /* Decrement the usage of the internal buffer. */
        stream->m_size -= limit;
        /* Determine the number of bytes yet to be skipped. */
        newCount -= limit;
    }

    /* Finally, the unbuffered data is required to be skipped. We assume that
     * it would be inefficient to buffer the data from the source input stream
     * and then skip it. Instead we delegate the task to the underlying input
     * stream to skip the remaining bytes. The underlying skip operation is
     * assumed to be efficient.
     */
    newCount -= jtk_InputStream_skip(stream->m_sourceInputStream, newCount);

    return count - newCount;
}