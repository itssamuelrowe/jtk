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

// Monday, May 27, 2019

#ifndef JTK_IO_INPUT_STREAM_HELPER_H
#define JTK_IO_INPUT_STREAM_HELPER_H

#include <jtk/Configuration.h>
#include <jtk/io/InputStream.h>

/*******************************************************************************
 * InputStreamHelper                                                           *
 *******************************************************************************/

bool jtk_InputStreamHelper_readFully(jtk_InputStream_t* stream, uint8_t* buffer,
    int32_t size);

bool jtk_InputStreamHelper_readFullyEx(jtk_InputStream_t* stream, uint8_t* buffer,
    int32_t size, int32_t index, int32_t limit);

#endif /* JTK_IO_INPUT_STREAM_HELPER_H */