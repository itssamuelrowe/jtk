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

#ifndef JTK_LOG_LOG_RECORD_H
#define JTK_LOG_LOG_RECORD_H

#include <jtk/Configuration.h>
#include <jtk/log/LogLevel.h>

/*******************************************************************************
 * LogRecord                                                                   *
 *******************************************************************************/

/**
 * @class LogRecord
 * @ingroup jtk_log
 * @author Samuel Rowe
 * @since JTK 2.0
 */
struct jtk_LogRecord_t {
    jtk_String_t* m_message;
    jtk_String_t* m_tag;
    jtk_LogLevel_t m_level;
    int64_t m_identifier;
    int64_t m_threadIdentifier;
    int64_t m_time;
    bool m_filtered;
};

/**
 * @memberof LogRecord
 */
typedef struct jtk_LogRecord_t jtk_LogRecord_t;

// Constructor

/**
 * @memberof LogRecord
 */
jtk_LogRecord_t* jtk_LogRecord_new(int64_t identifier, jtk_String_t* tag,
    jtk_String_t* message, jtk_LogLevel_t level, int64_t threadIdentifier,
    int64_t time);

// Destructor

/**
 * @memberof LogRecord
 */
jtk_LogRecord_t* jtk_LogRecord_delete(jtk_LogRecord_t* record);

// Filtered

/**
 * @memberof LogRecord
 */
void jtk_LogRecord_setFiltered(jtk_LogRecord_t* record, bool filtered);

/**
 * @memberof LogRecord
 */
bool jtk_LogRecord_isFiltered(jtk_LogRecord_t* record);

// Identifier

/**
 * @memberof LogRecord
 */
int64_t jtk_LogRecord_getIdentifier(jtk_LogRecord_t* record);

// Level

/**
 * @memberof LogRecord
 */
jtk_LogLevel_t jtk_LogRecord_getLevel(jtk_LogRecord_t* record);

// Message

/**
 * @memberof LogRecord
 */
jtk_String_t* jtk_LogRecord_getMessage(jtk_LogRecord_t* record);

// Tag

/**
 * @memberof LogRecord
 */
jtk_String_t* jtk_LogRecord_getTag(jtk_LogRecord_t* record);

// Thread Identifier

/**
 * @memberof LogRecord
 */
int64_t jtk_LogRecord_getThreadIdentifier(jtk_LogRecord_t* record);

// Time

/**
 * @memberof LogRecord
 */
int64_t jtk_LogRecord_getTime(jtk_LogRecord_t* record);

#endif /* JTK_LOG_LOG_RECORD_H */