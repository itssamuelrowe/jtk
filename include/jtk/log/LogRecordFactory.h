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

// Monday, March 25, 2019

#ifndef JTK_LOG_LOG_RECORD_FACTORY_H
#define JTK_LOG_LOG_RECORD_FACTORY_H

/*******************************************************************************
 * LogRecordFactory                                                            *
 *******************************************************************************/

/**
 * @memberof LogRecordFactory
 */
typedef struct jtk_LogRecordFactory_t jtk_LogRecordFactory_t;

typedef void (*jtk_LogRecordFactory_CreateLogRecordFunction_t)(jtk_LogRecordFactory_t* factory);

/**
 * @class LogRecordFactory
 * @ingroup jtk_log
 * @author Samuel Rowe
 * @since JTK 1.1
 */
struct jtk_LogRecordFactory_t {
    jtk_LogRecordFactory_CreateLogRecordFunction_t m_createLogRecord;
    void* m_userData;
};

// Constructor

/**
 * @memberof LogRecordFactory
 */
jtk_LogRecordFactory_t* jtk_LogRecordFactory_new(
    jtk_LogRecordFactory_CreateLogRecordFunction_t createLogRecord,
    void* userData);

// Destructor

/**
 * @memberof LogRecordFactory
 */
void jtk_LogRecordFactory_delete(jtk_LogRecordFactory_t* factory);

// User Data

/**
 * @memberof LogRecordFactory
 */
void* jtk_LogRecordFactory_getUserData(jtk_LogRecordFactory_t* factory);

/**
 * @memberof LogRecordFactory
 */
void jtk_LogRecordFactory_setUserData(jtk_LogRecordFactory_t* factory, void* userData);

#endif /* JTK_LOG_LOG_RECORD_FACTORY_H */