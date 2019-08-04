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

// Monday, May 13, 2019

#ifndef JTK_CORE_SYSTEM_H
#define JTK_CORE_SYSTEM_H

#include <jtk/Configuration.h>
#include <jtk/core/Error.h>
#include <jtk/core/ErrorFlag.h>

/*******************************************************************************
 * System                                                                      *
 *******************************************************************************/

/**
 * @memberof System
 */
typedef void (*jtk_ErrorHandlerFunction_t)(jtk_Error_t error, uint32_t flags);

/**
 * @class System
 * @ingroup jtk_core
 * @author Samuel Rowe
 * @since JTK 1.1
 */
struct jtk_System_t {
    jtk_Error_t m_error;
    uint32_t m_errorFlags;
    jtk_ErrorHandlerFunction_t m_errorHandler;
};

typedef struct jtk_System_t jtk_System_t;

// Constructor

jtk_System_t* jtk_System_new();

// Destructor

void jtk_System_delete(jtk_System_t* system);

// Error

jtk_Error_t jtk_System_getError(jtk_System_t* system);

void jtk_System_setError(jtk_System_t* system, jtk_Error_t error);

void jtk_System_setErrorEx(jtk_System_t* system, jtk_Error_t error, uint32_t errorFlags);

// Error Flags

void jtk_System_setErrorFlags(jtk_System_t* system, uint32_t errorFlags);

uint32_t jtk_System_getErrorFlags(jtk_System_t* system);

// Initialize

void jtk_System_initialize();

// Instance

void jtk_System_getInstance();

// Shutdown

void jtk_System_shutdown();

#endif /* JTK_CORE_SYSTEM_H */