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

// Sunday, May 05, 2019

#include <errno.h>
#include <com/onecube/jtk/support/NativeError.h>

/*******************************************************************************
 * NativeError                                                                 *
 *******************************************************************************/

// Translate

jtk_Error_t jtk_NativeError_translate(int32_t code) {
    jtk_Error_t error = JTK_ERROR_UNKNOWN;
    switch (code) {
        /* stat(), lstat()
         * The currently running process lacks search permission for one of the
         * directory components of path.
         */
        case EACCES: {
            error = JTK_ERROR_UNAUTHORIZED_ACCESS;
            break;
        }

        /* fstat()
         * The file descriptor is invalid.
         */
        case EBADF: {
            error = JTK_ERROR_INVALID_PATH_HANDLE;
            break;
        }

        /* fstat(), lstat(), stat()
         * The specified path or buffer is an invalid pointer.
         */
        case EFAULT: {
            error = JTK_ERROR_INVALID_BUFFER;
            break;
        }

        /* stat() and lstat()
         * The specified path contains too many symbolic links.
         */
        case ELOOP: {
            error = JTK_ERROR_TOO_MANY_SYMBOLIC_LINKS;
            break;
        }

        /* stat() and lstat()
         * The specified path is too long.
         */
        case ENAMETOOLONG: {
            error = JTK_ERROR_VERY_LONG_PATH;
            break;
        }

        /* stat() and lstat()
         * A component in the specified path does not exist.
         */
        case ENOENT: {
            error = JTK_ERROR_INVALID_PATH;
            break;
        }

        /* Insufficient memory available to complete the request.
         */
        case ENOMEM: {
            error = JTK_ERROR_OUT_OF_MEMORY;
            break;
        }

        /* A component in path is not a directory. */
        case ENOTDIR: {
            error = JTK_ERROR_EXPECTED_DIRECTORY;
            break;
        }

        /* A low-level I/O error during an I/O operation. */
        case EIO: {
            error = JTK_ERROR_LOW_LEVEL_IO;
            break;
        }
    }
    return error;
}

jtk_Error_t jtk_NativeError_translateEx(int32_t code, jtk_Error_t* error) {
    jtk_Error_t result = jtk_NativeError_translate(code);
    if (error != NULL) {
        *error = result;
    }
    return result;
}