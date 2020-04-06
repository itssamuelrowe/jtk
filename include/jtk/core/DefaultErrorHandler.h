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

// Saturday, May 25, 2019

#ifndef JTK_CORE_DEFAULT_ERROR_HANDLER_H
#define JTK_CORE_DEFAULT_ERROR_HANDLER_H

#include <jtk/Configuration.h>
#include <jtk/core/Error.h>

/*******************************************************************************
 * DefaultErrorHandler                                                         *
 *******************************************************************************/

/**
 * @since JTK 1.1
 */
void jtk_DefaultErrorHandler_handleError(jtk_Error_t error, int32_t flags);

#endif /* JTK_CORE_DEFAULT_ERROR_HANDLER_H */