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

#include <jtk/core/CString.h>
#include <jtk/log/Logger.h>

bool jtk_LogFilter_apply(jtk_LogFilter_t* filter, jtk_Logger_t* logger,
    jtk_LogRecord_t* record) {
    return (int32_t)record->m_level <= (int32_t)logger->m_level;
}

jtk_LogRecordFactory_t* jtk_LogRecordFactory_getInstance() {
    jtk_LogRecordFactory_t* factory = jtk_Memory_allocate(jtk_LogRecordFactory_t, 1);
    factory->m_userData = NULL;
    factory->m_createLogRecord = NULL;
    
    return factory;
}

/*******************************************************************************
 * Logger                                                                      *
 *******************************************************************************/

// Constructor

jtk_Logger_t* jtk_Logger_new(jtk_Logger_LogFunction_t log) {
    return jtk_Logger_newEx(NULL, -1, log);
}

jtk_Logger_t* jtk_Logger_newEx(const uint8_t* name, int32_t nameSize, jtk_Logger_LogFunction_t log) {
    jtk_Logger_t* logger = jtk_Memory_allocate(jtk_Logger_t, 1);
    if (name == NULL) {
        logger->m_name = jtk_CString_newEx("Unknown", 7);
        logger->m_nameSize = 7;
    }
    else {
        logger->m_name = jtk_CString_make(name, &nameSize);
        logger->m_nameSize = nameSize;
    }
    logger->m_userData = NULL;
    logger->m_level = JTK_LOG_LEVEL_ALL;
    logger->m_filters = jtk_ArrayList_new();
    logger->m_log = log;
    // logger->m_records = jtk_DoublyLinkedList_new();
    // logger->m_keepHistory = true;

    return logger;
}

// Destructor

void jtk_Logger_delete(jtk_Logger_t* logger) {
    jtk_Assert_assertObject(logger, "The specified logger is null.");

    // jtk_Iterator_t* iterator = jtk_ArrayList_getIterator(logger->m_records);
    // while (jtk_Iterator_hasNext(iterator)) {
    //     jtk_LogRecord_t* record = (jtk_LogRecord_t*)jtk_Iterator_getNext(iterator);
    //     jtk_LogRecordFactory_destroyLogRecord(logger->m_logRecordFactory, record);
    // }
    // jtk_Iterator_delete(iterator);
    
    jtk_ArrayList_delete(logger->m_filters);
    jtk_CString_delete(logger->m_name);
    jtk_Memory_deallocate(logger);
}

// Filter

bool jtk_Logger_filter(jtk_Logger_t* logger, jtk_LogRecord_t* record) {
    return (int32_t)record->m_level >= (int32_t)logger->m_level;
}

// Log

void jtk_Logger_publish(jtk_Logger_t* logger, jtk_LogLevel_t level,
    const uint8_t* tag, int32_t tagSize, const uint8_t* format,
    int32_t formatSize, jtk_VariableArguments_t arguments) {
    bool filtered = false;
    
    int32_t capacity = 300;
    uint8_t* message = jtk_Memory_allocate(uint8_t, capacity);
    int32_t messageSize = vsnprintf(message, capacity, format, arguments);

    int64_t time = 0; // TODO: Get the current time
    int64_t threadIdentifier = 0; // TODO: Get the thread identifier

    jtk_LogRecord_t* record = jtk_Logger_createLogRecord(logger, level,
        tag, tagSize, message, messageSize, threadIdentifier, time);
    
    /* Destroy the previously allocated temporary buffer. */
    jtk_CString_delete(message);
    
    // if (logger->m_keepRecords) {
        // TODO: Implement a circular buffer that automatically removes records.
        // jtk_DoublyLinkedList_addLast(logger->m_records, record);
    // }
    
    /* The default filter is always active. This behaviour can be overriden
     * with a custom filter.
     *
     * The filter returns true if the record should be retained. However, the
     * "filtered" flag indicates if the record should be discarded. Therefore,
     * negate the result of the filter.
     */
    filtered = !jtk_Logger_filter(logger, record);

    jtk_Iterator_t* iterator = jtk_ArrayList_getIterator(logger->m_filters);
    while (jtk_Iterator_hasNext(iterator)) {
        jtk_LogFilter_t* filter = (jtk_LogFilter_t*)jtk_Iterator_getNext(iterator);
        if (!jtk_LogFilter_apply(filter, logger, record)) {
            filtered = true;
            break;
        }
    }
    jtk_Iterator_delete(iterator);
    
    jtk_LogRecord_setFiltered(record, filtered);

    /* Previously, the logger prevented filtered logs from being delegated to
     * the log recorder. As of now, the logger delegates the logs after
     * marking the record as filtered. It is left to the recorder to keep
     * or discard the record.
     */
    // if (!filtered) {
        /* The logger is abstract and may record the log in any destination,
         * such as file, console, or network, considered apprioriate by the
         * user. Therefore, delegate the actual recording operation to the
         * user specified log recorder.
         */
        logger->m_log(logger, record);
    // }

    jtk_Logger_destroyLogRecord(logger, record);
}

void jtk_Logger_log(jtk_Logger_t* logger, jtk_LogLevel_t level, const uint8_t* tag,
    const uint8_t* format, ...) {
    jtk_Assert_assertObject(logger, "The specified logger is null.");
    jtk_Assert_assertObject(tag, "The specified tag is null.");
    jtk_Assert_assertObject(format, "The specified format is null.");

    /* The variable arguments passed to this function. */
    jtk_VariableArguments_t arguments;

    /* Initialize the variable arguments. */
    jtk_VariableArguments_start(arguments, format);

    jtk_Logger_publish(logger, level, tag, -1, format, -1, arguments);

    /* Destroy resources allocated to initialize the variable arguments. */
    jtk_VariableArguments_end(arguments);
}

void jtk_Logger_logFinest(jtk_Logger_t* logger, const uint8_t* tag,
    const uint8_t* format, ...) {
    jtk_Assert_assertObject(logger, "The specified logger is null.");
    jtk_Assert_assertObject(tag, "The specified tag is null.");
    jtk_Assert_assertObject(format, "The specified format is null.");

    /* The variable arguments passed to this function. */
    jtk_VariableArguments_t arguments;

    /* Initialize the variable arguments. */
    jtk_VariableArguments_start(arguments, format);

    jtk_Logger_publish(logger, JTK_LOG_LEVEL_FINEST, tag, -1, format, -1, arguments);

    /* Destroy resources allocated to initialize the variable arguments. */
    jtk_VariableArguments_end(arguments);
}

void jtk_Logger_logFiner(jtk_Logger_t* logger, const uint8_t* tag,
    const uint8_t* format, ...) {
    jtk_Assert_assertObject(logger, "The specified logger is null.");
    jtk_Assert_assertObject(tag, "The specified tag is null.");
    jtk_Assert_assertObject(format, "The specified format is null.");

    /* The variable arguments passed to this function. */
    jtk_VariableArguments_t arguments;

    /* Initialize the variable arguments. */
    jtk_VariableArguments_start(arguments, format);

    jtk_Logger_publish(logger, JTK_LOG_LEVEL_FINER, tag, -1, format, -1, arguments);

    /* Destroy resources allocated to initialize the variable arguments. */
    jtk_VariableArguments_end(arguments);
}

void jtk_Logger_logFine(jtk_Logger_t* logger, const uint8_t* tag,
    const uint8_t* format, ...) {
    jtk_Assert_assertObject(logger, "The specified logger is null.");
    jtk_Assert_assertObject(tag, "The specified tag is null.");
    jtk_Assert_assertObject(format, "The specified format is null.");

    /* The variable arguments passed to this function. */
    jtk_VariableArguments_t arguments;

    /* Initialize the variable arguments. */
    jtk_VariableArguments_start(arguments, format);

    jtk_Logger_publish(logger, JTK_LOG_LEVEL_FINE, tag, -1, format, -1, arguments);

    /* Destroy resources allocated to initialize the variable arguments. */
    jtk_VariableArguments_end(arguments);
}

void jtk_Logger_logDebug(jtk_Logger_t* logger, const uint8_t* tag,
    const uint8_t* format, ...) {
    jtk_Assert_assertObject(logger, "The specified logger is null.");
    jtk_Assert_assertObject(tag, "The specified tag is null.");
    jtk_Assert_assertObject(format, "The specified format is null.");

    /* The variable arguments passed to this function. */
    jtk_VariableArguments_t arguments;

    /* Initialize the variable arguments. */
    jtk_VariableArguments_start(arguments, format);

    jtk_Logger_publish(logger, JTK_LOG_LEVEL_DEBUG, tag, -1, format, -1, arguments);

    /* Destroy resources allocated to initialize the variable arguments. */
    jtk_VariableArguments_end(arguments);
}

void jtk_Logger_logConfiguration(jtk_Logger_t* logger, const uint8_t* tag,
    const uint8_t* format, ...) {
    jtk_Assert_assertObject(logger, "The specified logger is null.");
    jtk_Assert_assertObject(tag, "The specified tag is null.");
    jtk_Assert_assertObject(format, "The specified format is null.");

    /* The variable arguments passed to this function. */
    jtk_VariableArguments_t arguments;

    /* Initialize the variable arguments. */
    jtk_VariableArguments_start(arguments, format);

    jtk_Logger_publish(logger, JTK_LOG_LEVEL_CONFIGURATION, tag, -1, format, -1, arguments);

    /* Destroy resources allocated to initialize the variable arguments. */
    jtk_VariableArguments_end(arguments);
}

void jtk_Logger_logInformation(jtk_Logger_t* logger, const uint8_t* tag,
    const uint8_t* format, ...) {
    jtk_Assert_assertObject(logger, "The specified logger is null.");
    jtk_Assert_assertObject(tag, "The specified tag is null.");
    jtk_Assert_assertObject(format, "The specified format is null.");

    /* The variable arguments passed to this function. */
    jtk_VariableArguments_t arguments;

    /* Initialize the variable arguments. */
    jtk_VariableArguments_start(arguments, format);

    jtk_Logger_publish(logger, JTK_LOG_LEVEL_INFORMATION, tag, -1, format, -1, arguments);

    /* Destroy resources allocated to initialize the variable arguments. */
    jtk_VariableArguments_end(arguments);
}

void jtk_Logger_logWarning(jtk_Logger_t* logger, const uint8_t* tag,
    const uint8_t* format, ...) {
    jtk_Assert_assertObject(logger, "The specified logger is null.");
    jtk_Assert_assertObject(tag, "The specified tag is null.");
    jtk_Assert_assertObject(format, "The specified format is null.");

    /* The variable arguments passed to this function. */
    jtk_VariableArguments_t arguments;

    /* Initialize the variable arguments. */
    jtk_VariableArguments_start(arguments, format);

    jtk_Logger_publish(logger, JTK_LOG_LEVEL_WARNING, tag, -1, format, -1, arguments);

    /* Destroy resources allocated to initialize the variable arguments. */
    jtk_VariableArguments_end(arguments);
}

void jtk_Logger_logSevere(jtk_Logger_t* logger, const uint8_t* tag,
    const uint8_t* format, ...) {
    jtk_Assert_assertObject(logger, "The specified logger is null.");
    jtk_Assert_assertObject(tag, "The specified tag is null.");
    jtk_Assert_assertObject(format, "The specified format is null.");

    /* The variable arguments passed to this function. */
    jtk_VariableArguments_t arguments;

    /* Initialize the variable arguments. */
    jtk_VariableArguments_start(arguments, format);

    jtk_Logger_publish(logger, JTK_LOG_LEVEL_SEVERE, tag, -1, format, -1, arguments);

    /* Destroy resources allocated to initialize the variable arguments. */
    jtk_VariableArguments_end(arguments);
}

void jtk_Logger_logError(jtk_Logger_t* logger, const uint8_t* tag,
    const uint8_t* format, ...) {
    jtk_Assert_assertObject(logger, "The specified logger is null.");
    jtk_Assert_assertObject(tag, "The specified tag is null.");
    jtk_Assert_assertObject(format, "The specified format is null.");

    /* The variable arguments passed to this function. */
    jtk_VariableArguments_t arguments;

    /* Initialize the variable arguments. */
    jtk_VariableArguments_start(arguments, format);

    jtk_Logger_publish(logger, JTK_LOG_LEVEL_ERROR, tag, -1, format, -1, arguments);

    /* Destroy resources allocated to initialize the variable arguments. */
    jtk_VariableArguments_end(arguments);
}

// Log Level

void jtk_Logger_setLevel(jtk_Logger_t* logger, jtk_LogLevel_t level) {
    jtk_Assert_assertObject(logger, "The specified logger is null.");

    logger->m_level = level;
}

jtk_LogLevel_t jtk_Logger_getLevel(jtk_Logger_t* logger) {
    jtk_Assert_assertObject(logger, "The specified logger is null.");

    return logger->m_level;
}

// Log Record

jtk_LogRecord_t* jtk_Logger_createLogRecord(jtk_Logger_t* logger, jtk_LogLevel_t level,
    const uint8_t* tag, int32_t tagSize, const uint8_t* message, int32_t messageSize,
    int64_t threadIdentifier, int64_t time) {
    jtk_LogRecord_t* result = jtk_LogRecord_new(1, tag, tagSize, message,
        messageSize, level, threadIdentifier, time);
    
    return result;
}

void jtk_Logger_destroyLogRecord(jtk_Logger_t* logger, jtk_LogRecord_t* record) {
    jtk_LogRecord_delete(record);
}