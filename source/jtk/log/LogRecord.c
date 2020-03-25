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

// Saturday, April 04, 2019

#include <jtk/log/LogRecord.h>

/*******************************************************************************
 * LogRecord                                                                   *
 *******************************************************************************/

// Constructor

jtk_LogRecord_t* jtk_LogRecord_new(int64_t identifier, const uint8_t* tag,
    int32_t tagSize, const uint8_t* message, int32_t messageSize,
    jtk_LogLevel_t level, int64_t threadIdentifier, int64_t time) {
    jtk_LogRecord_t* record = jtk_Memory_allocate(jtk_LogRecord_t, 1);
    record->m_identifier = identifier;
    record->m_tag = jtk_CString_make(tag, &tagSize);
    record->m_tagSize = tagSize;
    record->m_message = jtk_CString_make(message, &messageSize);
    record->m_messageSize = messageSize;
    record->m_level = level;
    record->m_threadIdentifier = threadIdentifier;
    record->m_time = time;
    record->m_filtered = false;

    return record;
}

// Destructor

jtk_LogRecord_t* jtk_LogRecord_delete(jtk_LogRecord_t* record) {
    jtk_Assert_assertObject(record, "The specified log record is null.");
    
    jtk_CString_delete(record->m_message);
    jtk_CString_delete(record->m_tag);
    jtk_Memory_deallocate(record);
}

// Filtered

void jtk_LogRecord_setFiltered(jtk_LogRecord_t* record, bool filtered) {
    jtk_Assert_assertObject(record, "The specified log record is null.");
    
    record->m_filtered = filtered;
}

bool jtk_LogRecord_isFiltered(jtk_LogRecord_t* record) {
    jtk_Assert_assertObject(record, "The specified log record is null.");
    
    return record->m_filtered;
}

// Identifier

int64_t jtk_LogRecord_getIdentifier(jtk_LogRecord_t* record) {
    jtk_Assert_assertObject(record, "The specified log record is null.");
    
    return record->m_identifier;
}

// Level

jtk_LogLevel_t jtk_LogRecord_getLevel(jtk_LogRecord_t* record) {
    jtk_Assert_assertObject(record, "The specified log record is null.");
    
    return record->m_level;
}

// Message

uint8_t* jtk_LogRecord_getMessage(jtk_LogRecord_t* record) {
    jtk_Assert_assertObject(record, "The specified log record is null.");
    
    return record->m_message;
}

// Tag

uint8_t* jtk_LogRecord_getTag(jtk_LogRecord_t* record) {
    jtk_Assert_assertObject(record, "The specified log record is null.");
    
    return record->m_tag;
}

// Thread Identifier

int64_t jtk_LogRecord_getThreadIdentifier(jtk_LogRecord_t* record) {
    jtk_Assert_assertObject(record, "The specified log record is null.");
    
    return record->m_threadIdentifier;
}

// Time

int64_t jtk_LogRecord_getTime(jtk_LogRecord_t* record) {
    jtk_Assert_assertObject(record, "The specified log record is null.");
    
    return record->m_time;
}
