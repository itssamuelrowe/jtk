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

// Monday, May 13, 2013

#include <jtk/core/System.h>

/*******************************************************************************
 * System                                                                      *
 *******************************************************************************/

// Constructor

jtk_System_t* jtk_System_new() {
    jtk_System_t* system = jtk_Memory_allocate(jtk_System_t, 1);
    system->m_error = JTK_ERROR_NONE;
    system->m_errorFlags = JTK_ERROR_FLAG_DEFAULT;
    system->m_errorHandler = NULL;

    return system;
}

// Destructor

void jtk_System_delete(jtk_System_t* system) {
    jtk_Assert_assertObject(system, "The specified system is null.");

    jtk_Memory_deallocate(system);
}

// Error

jtk_Error_t jtk_System_getError(jtk_System_t* system) {
    jtk_Assert_assertObject(system, "The specified system is null.");

    return system->m_error;
}

void jtk_System_reportError(jtk_System_t* system) {
    jtk_Assert_assertObject(system, "The specified system is null.");

    if (system->m_errorHandler != NULL) {
        system->m_errorHandler(system->m_error, system->m_errorFlags);
    }
    else {
        jtk_DefaultErrorHandler_handleError(system->m_error, system->m_errorFlags);
    }
}

void jtk_System_setError(jtk_System_t* system, jtk_Error_t error) {
    jtk_Assert_assertObject(system, "The specified system is null.");

    system->m_error = error;

    if (error != JTK_ERROR_NONE) {
        jtk_System_reportError(system);
    }
}

void jtk_System_setErrorEx(jtk_System_t* system, jtk_Error_t error,
    uint32_t errorFlags) {
    jtk_Assert_assertObject(system, "The specified system is null.");

    system->m_error = error;
    system->m_errorFlags = errorFlags;

    if (error != JTK_ERROR_NONE) {
        jtk_System_reportError(system);
    }
}

// Error Flags

void jtk_System_setErrorFlags(jtk_System_t* system, uint32_t errorFlags) {
    jtk_Assert_assertObject(system, "The specified system is null.");

    system->m_errorFlags = errorFlags;
}

uint32_t jtk_System_getErrorFlags(jtk_System_t* system) {
    jtk_Assert_assertObject(system, "The specified system is null.");

    return system->m_errorFlags;
}

// Initialize

jtk_System_t* s_instance;

void jtk_System_initialize() {
    if (s_instance == NULL) {
        /* If jtk_System_new() triggers an error before the system is initialized,
         * an assertion failure occurs. Because jtk_System_getInstance() returns
         * null, which is passed to jtk_System_setError(). When assertions are
         * disabled, the behaviour is undefined.
         */
        s_instance = jtk_System_new();
    }
}

// Instance

jtk_System_t* jtk_System_getInstance() {
    return s_instance;
}

// Shutdown

void jtk_System_shutdown() {
    if (s_instance != NULL) {
        jtk_System_delete(s_instance);
    }
}