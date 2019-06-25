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

// Sunday, March 24, 2019

#ifndef JTK_LOG_LOG_FILTER_H
#define JTK_LOG_LOG_FILTER_H

#include <jtk/Configuration.h>
#include <jtk/log/LogRecord.h>

/*******************************************************************************
 * LogFilter                                                                   *
 *******************************************************************************/

// Forward Reference

/**
 * @memberof LogFilter
 */
typedef struct jtk_LogFilter_t jtk_LogFilter_t;

// Apply Function

/**
 * @memberof LogFilter
 */
typedef bool (*jtk_LogFilter_ApplyFunction_t)(jtk_LogFilter_t* filter,
    jtk_LogRecord_t* record);

/**
 * @class LogFilter
 * @ingroup jtk_log
 * @author Samuel Rowe
 * @since jtk 2.0
 */
struct jtk_LogFilter_t {
    jtk_LogFilter_ApplyFunction_t m_apply;
    void* m_userData;
};

// Constructor

/**
 * @memberof LogFilter
 */
jtk_LogFilter_t* jtk_LogFilter_new(jtk_LogFilter_ApplyFunction_t apply);

/**
 * @memberof LogFilter
 */
jtk_LogFilter_t* jtk_LogFilter_newEx(jtk_LogFilter_ApplyFunction_t apply,
    void* userData);

// Destructor

/**
 * @memberof LogFilter
 */
void jtk_LogFilter_delete(jtk_LogFilter_t* filter);

// User Data

/**
 * @memberof LogFilter
 */
void* jtk_LogFilter_getUserData(jtk_LogFilter_t* filter);

/**
 * @memberof LogFilter
 */
void jtk_LogFilter_setUserData(jtk_LogFilter_t* filter, void* userData);

#endif /* JTK_LOG_LOG_FILTER_H */