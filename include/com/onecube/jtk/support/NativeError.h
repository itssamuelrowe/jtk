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

#ifndef COM_ONECUBE_JTK_SUPPORT_NATIVE_ERROR_H
#define COM_ONECUBE_JTK_SUPPORT_NATIVE_ERROR_H

#include <jtk/Configuration.h>
#include <jtk/core/Error.h>

/*******************************************************************************
 * NativeError                                                                 *
 *******************************************************************************/

// Translate

jtk_Error_t jtk_NativeError_translate(int32_t code);
jtk_Error_t jtk_NativeError_translateEx(int32_t code, jtk_Error_t* error);

#endif /* COM_ONECUBE_JTK_SUPPORT_NATIVE_ERROR_H */