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

#ifndef JTK_LOG_LOGGER_H
#define JTK_LOG_LOGGER_H

#include <jtk/Configuration.h>
#include <jtk/log/LogLevel.h>
#include <jtk/log/LogFilter.h>
#include <jtk/log/LogRecordFactory.h>
#include <jtk/collection/list/ArrayList.h>
#include <jtk/core/VariableArguments.h>

/*******************************************************************************
 * Logger                                                                      *
 *******************************************************************************/

#define jtk_Logger_finest jtk_Logger_logFinest
#define jtk_Logger_finer jtk_Logger_logFiner
#define jtk_Logger_fine jtk_Logger_logFine
#define jtk_Logger_debug jtk_Logger_logDebug
#define jtk_Logger_configuration jtk_Logger_logConfiguration
#define jtk_Logger_information jtk_Logger_logInformation
#define jtk_Logger_info jtk_Logger_logInformation
#define jtk_Logger_warning jtk_Logger_logWarning
#define jtk_Logger_severe jtk_Logger_logSevere
#define jtk_Logger_error jtk_Logger_logError

// Forward Reference

/**
 * @memberof Logger
 */
typedef struct jtk_Logger_t jtk_Logger_t;

// Log Function

/**
 * @memberof Logger
 */
typedef void (*jtk_Logger_LogFunction_t)(jtk_Logger_t* logger, jtk_LogRecord_t* record);

/**
 * @class Logger
 * @ingroup jtk_log
 * @author Samuel Rowe
 * @since 2.0
 */
struct jtk_Logger_t {
    jtk_String_t* m_name;
    void* m_userData;
    jtk_LogLevel_t m_level;
    jtk_ArrayList_t* m_filters;
    jtk_Logger_LogFunction_t m_log;
    // jtk_LogRecordFactory_t* m_logRecordFactory;
    // jtk_DoublyLinkedList_t* m_records;
    // bool m_keepHistory;
};

// Constructor

/**
 * @memberof Logger
 */
jtk_Logger_t* jtk_Logger_new(jtk_Logger_LogFunction_t log);

/**
 * @memberof Logger
 */
jtk_Logger_t* jtk_Logger_newEx(jtk_String_t* name, jtk_Logger_LogFunction_t log);

// Destructor

/**
 * @memberof Logger
 */
void jtk_Logger_delete(jtk_Logger_t* logger);

// Log

/**
 * @memberof Logger
 */
void jtk_Logger_log(jtk_Logger_t* logger, jtk_LogLevel_t level, const uint8_t* tag, const uint8_t* format,
    ...);

/**
 * @memberof Logger
 */
void jtk_Logger_logFinest(jtk_Logger_t* logger, const uint8_t* tag, const uint8_t* format, ...);

/**
 * @memberof Logger
 */
void jtk_Logger_logFiner(jtk_Logger_t* logger, const uint8_t* tag, const uint8_t* format, ...);

/**
 * @memberof Logger
 */
void jtk_Logger_logFine(jtk_Logger_t* logger, const uint8_t* tag, const uint8_t* format, ...);

/**
 * @memberof Logger
 */
void jtk_Logger_logDebug(jtk_Logger_t* logger, const uint8_t* tag, const uint8_t* format, ...);

/**
 * @memberof Logger
 */
void jtk_Logger_logConfiguration(jtk_Logger_t* logger, const uint8_t* tag, const uint8_t* format, ...);

/**
 * @memberof Logger
 */
void jtk_Logger_logInformation(jtk_Logger_t* logger, const uint8_t* tag, const uint8_t* format, ...);

/**
 * @memberof Logger
 */
void jtk_Logger_logWarning(jtk_Logger_t* logger, const uint8_t* tag, const uint8_t* format, ...);

/**
 * @memberof Logger
 */
void jtk_Logger_logSevere(jtk_Logger_t* logger, const uint8_t* tag, const uint8_t* format, ...);

/**
 * @memberof Logger
 */
void jtk_Logger_logError(jtk_Logger_t* logger, const uint8_t* tag, const uint8_t* format, ...);

// Log Level

/**
 * @memberof Logger
 */
void jtk_Logger_setLevel(jtk_Logger_t* logger, jtk_LogLevel_t level);

/**
 * @memberof Logger
 */
jtk_LogLevel_t jtk_Logger_getLevel(jtk_Logger_t* logger);

// Log Record

jtk_LogRecord_t* jtk_Logger_createLogRecord(jtk_Logger_t* logger, jtk_LogLevel_t level,
    jtk_String_t* tag, jtk_String_t* message, int64_t threadIdentifier, int64_t time);

void jtk_Logger_destroyLogRecord(jtk_Logger_t* logger, jtk_LogRecord_t* record);

// Keep Records

/**
 * @memberof Logger
 */
// void jtk_Logger_setKeepHistory(jtk_Logger_t* logger, bool keepHistory);

// bool jtk_Logger_keepsHistory(jtk_Logger_t* logger);

#endif /* JTK_LOG_LOGGER_H */
