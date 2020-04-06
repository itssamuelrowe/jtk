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

// Monday, May 06, 2019

#ifndef COM_ONECUBE_JTK_FS_NATIVE_FILE_HANDLE_H
#define COM_ONECUBE_JTK_FS_NATIVE_FILE_HANDLE_H

#include <jtk/Configuration.h>
#include <jtk/core/Error.h>

/*******************************************************************************
 * NativeFileHandle                                                            *
 *******************************************************************************/

// Open

int64_t jtk_NativeFileHandle_open(const uint8_t* path, jtk_Error_t* error);

int64_t jtk_NativeFileHandle_openDirectory(const uint8_t* path, jtk_Error_t* error);

// Read

int32_t jtk_NativeFileHandle_readBytes(int64_t handle, uint8_t* buffer,
    int32_t size, int32_t startIndex, int32_t stopIndex, jtk_Error_t* error);

#endif /* COM_ONECUBE_JTK_FS_NATIVE_FILE_HANDLE_H */