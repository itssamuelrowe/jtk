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

// Sunday, August 04, 2019

#ifndef JTK_FS_FILE_OPEN_MODE_H
#define JTK_FS_FILE_OPEN_MODE_H

/*******************************************************************************
 * FileOpenMode                                                                *
 *******************************************************************************/

/**
 * The enumeration of modes you can open a file with.
 *
 * A file can be opened for a specific purpose, this is known as file open mode.
 * For example, a file opened for writing cannot be read from. You cannot change
 * the mode after you open it, unless you close and open it again. However, you
 * can combine modes to both read and write from a file when opening it.
 *
 * @class FileOpenMode
 * @ingroup jtk_fs
 * @author Samuel Rowe
 * @since JTK 1.1
 */
enum jtk_FileOpenMode_t {
    JTK_FILE_OPEN_MODE_CREATE = (1 << 0),
    JTK_FILE_OPEN_MODE_READ = (1 << 1),

    /**
     * The file is opened with the cursor at the end of the file. After each
     * write, the cursor is updated to the end of the file. This occurs even if
     * another process has written to the file after the current process
     * previously issued a write.
     */
    JTK_FILE_OPEN_MODE_APPEND = (1 << 2),
    JTK_FILE_OPEN_MODE_TRUNCATE = (1 << 3),
    JTK_FILE_OPEN_MODE_SYNCHRONOUS = (1 << 4),

    /**
     * This flags prepares the system to generate a signal whenever the file
     * becomes readable or writable. It should be noted that asynchronous input
     * output is simulated by JTK, which means asynchronous operations should
     * be run on a looper thread.
     *
     * As of JTK 1.1, asynchronous file input/output is not supported.
     */
    JTK_FILE_OPEN_MODE_ASYNCHRONOUS = (1 << 5),
};

typedef enum jtk_FileOpenMode_t jtk_FileOpenMode_t;

#endif /* JTK_FS_FILE_OPEN_MODE_H */