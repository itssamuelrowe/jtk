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

// Sunday, May 05, 2019

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#include <com/onecube/jtk/fs/NativeFileHandle.h>

/*******************************************************************************
 * NativeFileHandle                                                            *
 *******************************************************************************/

// Close

void jtk_NativeFileHandle_close(int64_t handle, jtk_Error_t* error) {
    int64_t result = close(handle);

    if (result < 0) {
        jtk_NativeError_translateEx(errno, error);
    }
}

// Flush

bool jtk_NativeFileHandle_flush(int64_t handle, jtk_Error_t* error) {
    bool failed = fsync(handle) < 0;
    if (failed) {
        jtk_NativeError_translateEx(errno, error);
    }
    return !failed;
}

// Directory

bool jtk_NativeFileHandle_isDirectory(int32_t descriptor, jtk_Error_t* error) {
    struct stat buffer;
    int32_t result = fstat(descriptor, &buffer);

    bool directory = false;
    if (result != 0) {
        jtk_NativeError_translateEx(errno, error);
    }
    else {
        directory = S_ISDIR(buffer.st_mode);
    }
    return directory;
}

// Open

int64_t jtk_NativeFileHandle_open(const uint8_t* path, jtk_Error_t* error) {
    jtk_Assert_assertObject(path, "The specified path is null.");

    int64_t handle = open(path, O_RDONLY | O_APPEND);

    if (handle < 0) {
        jtk_NativeError_translateEx(errno, error);
    }

    return handle;
}

// Read

int32_t jtk_NativeFileHandle_readBytes(int64_t handle, uint8_t* buffer,
    int32_t size, int32_t startIndex, int32_t stopIndex, jtk_Error_t* error) {

    uint8_t* destination = buffer + startIndex;
    int32_t count = stopIndex - startIndex;
    int32_t result = read(handle, destination, count);

    if (result < 0) {
        jtk_NativeError_translateEx(errno, error);
    }

    return (result == 0)? -1 : ((result < 0)? -2 : result);
}

// Regular File

bool jtk_NativeFileHandle_isRegularFile(int32_t descriptor, jtk_Error_t* error) {
    struct stat buffer;
    int32_t result = fstat(descriptor, &buffer);

    bool file = false;
    if (result != 0) {
        jtk_NativeError_translateEx(errno, error);
    }
    else {
        file = S_ISREG(buffer.st_mode);
    }
    return file;
}

// Skip

int64_t jtk_NativeFileHandle_skip(int64_t handle, int64_t count) {
    // TODO
    return 0;
}

// Write

int64_t jtk_NativeFileHandle_writeBytesEx(int64_t handle, uint8_t* bytes,
    int32_t size, int32_t startIndex, int32_t stopIndex, jtk_Error_t* error) {
    jtk_Assert_assertObject(bytes, "The specified buffer is null.");
    jtk_Assert_assertObject(error, "The specified error is null.");
    jtk_Assert_assertTrue((startIndex >= 0) && (stopIndex <= size), "The specified range is invalid.");

    int32_t result = write(handle, bytes + startIndex, stopIndex - startIndex);
    if (result < 0) {
        jtk_NativeError_translateEx(errno, error);
    }
    return result;
}