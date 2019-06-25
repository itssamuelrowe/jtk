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

#include <jtk/log/Logger.h>

/*******************************************************************************
 * Logger                                                                      *
 *******************************************************************************/

// Constructor

jtk_Logger_t* jtk_Logger_new(jtk_Logger_LogFunction_t log) {
    jtk_LogRecordFactory_t* logRecordFactory = jtk_LogRecordFactory_getInstance();
    return jtk_Logger_newEx(NULL, logRecordFactory, log);
}

jtk_Logger_t* jtk_Logger_newEx(jtk_String_t* name,
    jtk_LogRecordFactory_t* logRecordFactory, jtk_Logger_LogFunction_t log) {
    jtk_Logger_t* logger = jtk_Memory_allocate(jtk_Logger_t, 1);
    logger->m_name = jtk_String_new(name);
    logger->m_userData = NULL;
    logger->m_level = JTK_LOG_LEVEL_ALL;
    logger->m_filters = jtk_ArrayList_new();
    logger->m_log = log;
    logger->m_logRecordFactory = logRecordFactory;
    // logger->m_records = jtk_DoublyLinkedList_new();
    // logger->m_keepHistory = true;

    return logger;
}

// Destructor

void jtk_Logger_delete(jtk_Logger_t* logger) {
    jtk_Assert_assertObject(logger, "The specified logger is null.");

    // jtk_Iterator_t* iterator = jtk_DoublyLinkedList_getIterator(logger->m_records);
    // while (jtk_Iterator_hasNext(iterator)) {
    //     jtk_LogRecord_t* record = (jtk_LogRecord_t*)jtk_Iterator_getNext(iterator);
    //     jtk_LogRecordFactory_destroyLogRecord(logger->m_logRecordFactory, record);
    // }
    // jtk_Iterator_delete(iterator);

    jtk_String_delete(logger->m_name);
    jtk_Memory_deallocate(logger);
}

// Log

void jtk_Logger_publish(jtk_Logger_t* logger, jtk_LogLevel_t level,
    const uint8_t* tag, const uint8_t* format, jtk_VariableArguments_t arguments) {
    bool filtered = false;
    
    int32_t capacity = 300;
    uint8_t* buffer = jtk_Memory_allocate(uint8_t, capacity);
    int32_t length = vsnprintf(buffer, capacity, format, arguments);

    jtk_String_t* message = jtk_String_newEx(buffer, length);
    int64_t time = 0; // TODO: Get the current time
    int64_t threadIdentifier = 0; // TODO: Get the thread identifier

    jtk_LogRecord_t* record = jtk_LogRecordFactory_createLogRecord(
            logger->m_logRecordFactory, logger, level, tag, message, threadIdentifier,
            time);
    
    // if (logger->m_keepRecords) {
        // TODO: Implement a circular buffer that automatically removes records.
        // jtk_DoublyLinkedList_addLast(logger->m_records, record);
    // }
    
    jtk_Iterator_t* iterator = jtk_DoublyLinkedList_getIterator(logger->m_filters);
    while (jtk_Iterator_hasNext(iterator)) {
        jtk_LogFilter_t* filter = (jtk_LogFilter_t*)jtk_Iterator_getNext(iterator);
        if (!jtk_LogFilter_apply(filter, record)) {
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

    /* Destroy the previously allocated temporary buffer. */
    jtk_Memory_deallocate(buffer);
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

    jtk_Logger_publish(logger, level, tag, format, arguments);

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

    jtk_Logger_publish(logger, JTK_LOG_LEVEL_FINEST, tag, format, arguments);

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

    jtk_Logger_publish(logger, JTK_LOG_LEVEL_FINER, tag, format, arguments);

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

    jtk_Logger_publish(logger, JTK_LOG_LEVEL_FINE, tag, format, arguments);

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

    jtk_Logger_publish(logger, JTK_LOG_LEVEL_DEBUG, tag, format, arguments);

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

    jtk_Logger_publish(logger, JTK_LOG_LEVEL_CONFIGURATION, tag, format, arguments);

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

    jtk_Logger_publish(logger, JTK_LOG_LEVEL_INFORMATION, tag, format, arguments);

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

    jtk_Logger_publish(logger, JTK_LOG_LEVEL_WARNING, tag, format, arguments);

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

    jtk_Logger_publish(logger, JTK_LOG_LEVEL_SEVERE, tag, format, arguments);

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

    jtk_Logger_publish(logger, JTK_LOG_LEVEL_ERROR, tag, format, arguments);

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