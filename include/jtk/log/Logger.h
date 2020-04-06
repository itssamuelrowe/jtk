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

#ifdef JTK_LOGGER_DISABLE
    #define jtk_Logger_finest(logger, format, ...) (0)
    #define jtk_Logger_finer(logger, format, ...) (0)
    #define jtk_Logger_fine(logger, format, ...) (0)
    #define jtk_Logger_debug(logger, format, ...) (0)
    #define jtk_Logger_configuration(logger, format, ...) (0)
    #define jtk_Logger_information(logger, format, ...) (0)
    #define jtk_Logger_info(logger, format, ...) (0)
    #define jtk_Logger_warning(logger, format, ...) (0)
    #define jtk_Logger_severe(logger, format, ...) (0)
    #define jtk_Logger_error(logger, format, ...) (0)
#else
    #define jtk_Logger_finest(logger, format, ...) jtk_Logger_logFinest(logger, "finest", format, ## __VA_ARGS__)
    #define jtk_Logger_finer(logger, format, ...) jtk_Logger_logFiner(logger, "finer", format, ## __VA_ARGS__)
    #define jtk_Logger_fine(logger, format, ...) jtk_Logger_logFine(logger, "fine", format, ## __VA_ARGS__)
    #define jtk_Logger_debug(logger, format, ...) jtk_Logger_logDebug(logger, "debug", format, ## __VA_ARGS__)
    #define jtk_Logger_configuration(logger, format, ...) jtk_Logger_logConfiguration(logger, "config", format, ## __VA_ARGS__)
    #define jtk_Logger_information(logger, format, ...) jtk_Logger_logInformation(logger, "info", format, ## __VA_ARGS__)
    #define jtk_Logger_info(logger, format, ...) jtk_Logger_logInformation(logger, "info", format, ## __VA_ARGS__)
    #define jtk_Logger_warning(logger, format, ...) jtk_Logger_logWarning(logger, "warning", format, ## __VA_ARGS__)
    #define jtk_Logger_severe(logger, format, ...) jtk_Logger_logSevere(logger, "severe", format, ## __VA_ARGS__)
    #define jtk_Logger_error(logger, format, ...) jtk_Logger_logError(logger, "error", format, ## __VA_ARGS__)
#endif

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
    uint8_t* m_name;
    int32_t m_nameSize;
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
jtk_Logger_t* jtk_Logger_newEx(const uint8_t* name, int32_t nameSize, jtk_Logger_LogFunction_t log);

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
    const uint8_t* tag, int32_t tagSize, const uint8_t* message, int32_t messageSize,
    int64_t threadIdentifier, int64_t time);

void jtk_Logger_destroyLogRecord(jtk_Logger_t* logger, jtk_LogRecord_t* record);

// Keep Records

/**
 * @memberof Logger
 */
// void jtk_Logger_setKeepHistory(jtk_Logger_t* logger, bool keepHistory);

// bool jtk_Logger_keepsHistory(jtk_Logger_t* logger);

#endif /* JTK_LOG_LOGGER_H */
